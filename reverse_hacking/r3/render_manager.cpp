#include "render_manager.h"
#include "r3/imgui/imgui.h"
#include "r3/imgui/imgui_impl_win32.h"
#include "r3/imgui/imgui_impl_dx11.h"
#pragma comment(lib, "d3d11.lib")


static constexpr const wchar_t* s_className = L"zq";


// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT WINAPI RenderManager::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    RenderManager* pThis = nullptr;
    if (msg == WM_NCCREATE) 
    {
        pThis = static_cast<RenderManager*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
        SetLastError(0);
        if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
        {
            if (GetLastError() != 0)
            {
                return FALSE;
            }
        }
    }
    else 
    {
        pThis = reinterpret_cast<RenderManager*>( GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    switch (msg)
    {
    case WM_SIZE:
        if (pThis->m_d3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            pThis->cleanupRenderTarget();
            pThis->m_swapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            pThis->createRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

RenderManager::RenderManager()
    : m_instance(nullptr)
    , m_hWnd(nullptr)
    , m_d3dDevice(nullptr)
    , m_d3dDeviceContext(nullptr)
    , m_swapChain(nullptr)
    , m_mainRenderTargetView(nullptr)
{
    m_clearColor[0] = m_clearColor[1] = m_clearColor[2] = m_clearColor[3] = 0.0f;
}

RenderManager::~RenderManager()
{

}

bool RenderManager::init(const RenderConfig& config)
{
    m_config = config;

    m_instance = GetModuleHandle(NULL);

    int w = m_config.w;
    int h = m_config.h;
    std::wstring windowName = m_config.windowName;

    if (m_config.isTransparent)
    {
        // wc.hbrBackground 0: 窗口背景色为黑色
        // wc.hbrBackground (HBRUSH)COLOR_WINDOW: 窗口背景色为默认的窗口的青色
        // wc.hbrBackground (HBRUSH)CreateSolidBrush(RGB(0, 0, 0)): 创建一个黑色的画刷
        // wc.hbrBackground (HBRUSH)GetStockObject(NULL_BRUSH)
        WNDCLASSEX wc{ 0 };
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = wndProc;
        wc.hInstance = m_instance;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
        wc.lpszClassName = s_className;
        ::RegisterClassEx(&wc);

        // dwStyle设置为WS_OVERLAPPEDWINDOW这个参数时，才可以使用CW_USEDEFAULT这个宏，否则的话，全部默认是0
        // window style: WS_OVERLAPPEDWINDOW: 重叠窗口，一般默认为这个，包含了标题，最小化等
        // window style: WS_POPUP: 可以认为就是无边框，无最小化等，只包含一个客户区
        // window style ex: WS_EX_LAYERED: 测试发现即使设置了WS_OVERLAPPEDWINDOW，这个值的效果也相当于是WS_POPUP
        // window style ex: WS_EX_TOPMOST: 永远保持窗口在顶层
        // window style ex: WS_EX_TRANSPARENT: 这个和WS_EX_LAYERED组合就可以实现点击到本窗口下面的窗口, 再配合WS_EX_TOPMOST
        // 即可实现点击窗口后，下层的窗口响应点击事件，同时本窗口依然在顶层
        m_hWnd = CreateWindowEx(
            WS_EX_TOPMOST | WS_EX_LAYERED,//WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
            wc.lpszClassName,                       // name of the window class
            windowName.c_str(),                  // title of the window
            WS_POPUP,                           //WS_POPUP,  WS_OVERLAPPEDWINDOW ,window style
            CW_USEDEFAULT,                          // x-position of the window
            CW_USEDEFAULT,                          // y-position of the window
            w,                                    // width of the window
            h,                                    // height of the window
            NULL,                                   // we have no parent window, NULL
            NULL,                                   // we aren't using menus, NULL
            wc.hInstance,                               // application handle
            this);                               // pass pointer to current object

        // 设置窗口透明，这里和创建窗口	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));有关
        // 相当于背景色是黑色，然后设置黑色将全部透明
        m_clearColor[0] = m_clearColor[1] = m_clearColor[2] = m_clearColor[3] = 0.0f;
        ::SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), 255, LWA_COLORKEY);
    }
    else
    {
        WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, wndProc, 0L, 0L, m_instance, NULL, NULL, NULL, NULL, s_className, NULL};
        ::RegisterClassEx(&wc);
        m_hWnd = ::CreateWindow(wc.lpszClassName, windowName.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL, wc.hInstance, this);
    }

    if (m_hWnd == nullptr)
    {
        ::UnregisterClass(s_className, m_instance);
        return false;
    }

    // Initialize Direct3D
    if (!createDeviceD3D())
    {
        cleanupDeviceD3D();
        ::UnregisterClass(s_className, m_instance);
        return false;
    }

    if (!initImgui())
    {
        return false;
    }

    ::ShowWindow(m_hWnd, SW_SHOWDEFAULT);
    ::UpdateWindow(m_hWnd);

    return true;
}

bool RenderManager::render()
{
    // Poll and handle messages (inputs, window resize, etc.)
    // See the WndProc() function below for our to dispatch events to the Win32 backend.
    MSG msg;
    while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
        if (msg.message == WM_QUIT)
        {
            //m_running = false;
        }
    }
    //if (!m_running)
    //{
    //    break;
    //}

    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (m_config.customDraw)
    {
        m_config.customDraw();
    }

    // Rendering
    ImGui::Render();
    m_d3dDeviceContext->OMSetRenderTargets(1, &m_mainRenderTargetView, NULL);
    m_d3dDeviceContext->ClearRenderTargetView(m_mainRenderTargetView, m_clearColor);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    m_swapChain->Present(1, 0); // Present with vsync
    //g_pSwapChain->Present(0, 0); // Present without vsync

    return true;
}

bool RenderManager::shutdown()
{
    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    cleanupDeviceD3D();
    ::DestroyWindow(m_hWnd);
    ::UnregisterClass(s_className, m_instance);

    return true;
}

bool RenderManager::initImgui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(m_hWnd);
    ImGui_ImplDX11_Init(m_d3dDevice, m_d3dDeviceContext);

    return true;
}

bool RenderManager::createDeviceD3D()
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = m_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(
        NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION,
        &sd, &m_swapChain, &m_d3dDevice, &featureLevel, &m_d3dDeviceContext) != S_OK)
    {
        return false;
    }

    createRenderTarget();
    return true;
}

void RenderManager::cleanupDeviceD3D()
{
    cleanupRenderTarget();
    if (m_swapChain) { m_swapChain->Release(); m_swapChain = nullptr; }
    if (m_d3dDeviceContext) { m_d3dDeviceContext->Release(); m_d3dDeviceContext = nullptr; }
    if (m_d3dDevice) { m_d3dDevice->Release(); m_d3dDevice = nullptr; }
}

void RenderManager::createRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    m_swapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    m_d3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_mainRenderTargetView);
    pBackBuffer->Release();
}

void RenderManager::cleanupRenderTarget()
{
    if (m_mainRenderTargetView) { m_mainRenderTargetView->Release(); m_mainRenderTargetView = nullptr; }
}

void RenderManager::drawStrokeText(float x, float y, std::uint32_t color, const char* str)
{
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y - 1), color, str);
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y + 1), color, str);
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x - 1, y), color, str);
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1, y), color, str);
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), color, str);
}

void RenderManager::drawNewText(float x, float y, std::uint32_t color, const char* str)
{
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), color, str);
}

void RenderManager::drawRect(float x, float y, float w, float h, std::uint32_t color, float thickness)
{
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0, thickness);
}

void RenderManager::drawFilledRect(float x, float y, float w, float h, std::uint32_t color)
{
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}

void RenderManager::drawCircleFilled(float x, float y, float radius, std::uint32_t color, int segments)
{
    ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, color, segments);
}

void RenderManager::drawCircle(float x, float y, float radius, std::uint32_t color, int segments)
{
    ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(x, y), radius, color, segments);
}

void RenderManager::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, std::uint32_t color, float thickne)
{
    ImGui::GetBackgroundDrawList()->AddTriangle(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), color, thickne);
}

void RenderManager::drawTriangleFilled(float x1, float y1, float x2, float y2, float x3, float y3, std::uint32_t color)
{
    ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), color);
}

void RenderManager::drawLine(float x1, float y1, float x2, float y2, std::uint32_t color, float thickness)
{
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), color, thickness);
}

