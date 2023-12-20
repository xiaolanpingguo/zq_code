//#include "dllloader.h"
//#include "r3/log.h"

#include <thread>
#include <windows.h>
#include <winternl.h> // hideThread


#define ID_LOAD_BUTTON 1
#define ID_UNLOAD_BUTTON 2


static bool hideThread(HANDLE hThread)
{
    using FnSetInformationThread = NTSTATUS(NTAPI*)(HANDLE, THREADINFOCLASS, PVOID, ULONG);
    const auto NtSetInformationThread{ reinterpret_cast<FnSetInformationThread>(::GetProcAddress(::GetModuleHandle(L"ntdll.dll"), "NtSetInformationThread")) };
    if (NtSetInformationThread == nullptr)
    {
        return false;
    }

    // ThreadHideFromDebugger:0x11 
    // it mean any exceptions skip the debugger and either hit SEH or explode and crash the app
    if (SUCCEEDED(NtSetInformationThread(hThread, (THREADINFOCLASS)0x11, NULL, 0)))
    {
        return true;
    }
    else
    {
        return false;
    }
}



class Application
{
public:
    Application() = default;
    ~Application() = default;
public:
    static void start();

private:
    bool init();
    void run();

    static void appThread();
    static LRESULT WINAPI _wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    void onLoadButtonClick();
    void onUnloadButtonClick();

private:
    int m_height = 400;
    int m_width = 400;
    HWND m_mainWnd = nullptr;
    HWND m_loadButtonWnd = nullptr;
    HWND m_unloadButtonWnd = nullptr;
    RECT m_loadButtonRect;
    RECT m_unloadButtonRect;
};

LRESULT WINAPI Application::_wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Application* app = nullptr;
    if (msg == WM_NCCREATE)
    {
        app = static_cast<Application*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
        SetLastError(0);
        if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(app)))
        {
            if (GetLastError() != 0)
            {
                return FALSE;
            }
        }
    }
    else
    {
        app = reinterpret_cast<Application*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (app && app->wndProc(hWnd, msg, wParam, lParam))
    {
        return true;
    }
    else
    {
        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

LRESULT Application::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    case WM_COMMAND:
    {
        // HIWORD(wParam): msg of this window
        // LOWORD(wParam): ID of this window
        // lParam: HHANDLE of this window
        if (BN_CLICKED == HIWORD(wParam))
        {
            if (LOWORD(wParam) == ID_LOAD_BUTTON)
            {
                onLoadButtonClick();
            }
            else if (LOWORD(wParam) == ID_UNLOAD_BUTTON)
            {
                onUnloadButtonClick();
            }
        }
        return 0;
    }
    case WM_LBUTTONDOWN:
    {
        POINT p = { LOWORD(lParam),HIWORD(lParam) };
        if (PtInRect(&m_loadButtonRect, p))
        {
            SendMessage(m_loadButtonWnd, BM_CLICK, 0, 0);
        }
        if (PtInRect(&m_unloadButtonRect, p))
        {
            SendMessage(m_unloadButtonWnd, BM_CLICK, 0, 0);
        }
        return 0;
    }
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Application::start()
{
    std::thread thr(&appThread);
    HANDLE h = thr.native_handle();
    hideThread(h);
    thr.detach();
}

void Application::appThread()
{
    Application* app = new Application();
    if (!app->init())
    {
        return;
    }

    app->run();
}

bool Application::init()
{
    HINSTANCE ins = GetModuleHandle(nullptr);
    WNDCLASSEXA wc = { sizeof(WNDCLASSEXA), CS_CLASSDC, _wndProc, 0L, 0L, ins, NULL, NULL, NULL, NULL, "main", NULL };
    ::RegisterClassExA(&wc);

    // main window
    m_mainWnd = ::CreateWindowA(wc.lpszClassName, "main", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height, NULL, NULL, ins, this);
    if (m_mainWnd == nullptr)
    {
        return false;
    }

    // load button
    m_loadButtonWnd = ::CreateWindowA("button", "load", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 0, 0, 100, 30, m_mainWnd, (HMENU)ID_LOAD_BUTTON, ins, nullptr);
    if (m_loadButtonWnd == nullptr)
    {
        return false;
    }
    m_loadButtonRect.left = 0;
    m_loadButtonRect.top = 0;
    m_loadButtonRect.right = 100;
    m_loadButtonRect.bottom = 30;

    // unload button
    m_unloadButtonWnd = ::CreateWindowA("button", "unload", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 0, 40, 100, 30, m_mainWnd, (HMENU)ID_UNLOAD_BUTTON, ins, nullptr);
    if (m_unloadButtonWnd == nullptr)
    {
        return false;
    }
    m_unloadButtonRect.left = 0;
    m_unloadButtonRect.top = 40;
    m_unloadButtonRect.right = 100;
    m_unloadButtonRect.bottom = 70;

    ShowWindow(m_mainWnd, SW_SHOW);
    ShowWindow(m_loadButtonWnd, SW_SHOW);
    ShowWindow(m_unloadButtonWnd, SW_SHOW);
    UpdateWindow(m_mainWnd);
    return true;
}

void Application::run()
{
    while (1)
    {
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
            {
                return;
            }
        }
    }
}

void Application::onLoadButtonClick()
{
    OPENFILENAME ofn = { 0 };
    TCHAR strFilename[MAX_PATH] = { 0 };
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = TEXT("*.*");
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = strFilename;
    ofn.nMaxFile = sizeof(strFilename);
    ofn.lpstrInitialDir = TEXT(".");
    ofn.lpstrTitle = TEXT("Open");
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
    if (GetOpenFileName(&ofn))
    {
        HMODULE handle = LoadLibrary(strFilename);
        if (handle)
        {
            MessageBox(NULL, TEXT("load success"), TEXT("notice"), 0);
        }
    }
}

void Application::onUnloadButtonClick()
{
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    DisableThreadLibraryCalls(hModule);
    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
    {
        return FALSE;
    }

    hideThread(hModule);

    Application::start();

    ::CloseHandle(hModule);
    return TRUE;
}

