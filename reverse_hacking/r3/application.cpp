#include "application.h"
#include "r3/render_manager.h"
#include "r3/imgui/imgui_impl_win32.h"


static constexpr const wchar_t* g_className = L"zq";
static std::array<float, 4> g_clearColor;


// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT WINAPI Application::_wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    Application* pThis = nullptr;
    if (msg == WM_NCCREATE) 
    {
        pThis = static_cast<Application*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
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
        pThis = reinterpret_cast<Application*>( GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    switch (msg)
    {
    case WM_SIZE:
        if (pThis->m_renderManager != nullptr && wParam != SIZE_MINIMIZED)
        {
            pThis->m_renderManager->resize((std::uint32_t)LOWORD(lParam), (std::uint32_t)HIWORD(lParam));
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

    if (pThis && pThis->wndProc(hWnd, msg, wParam, lParam))
    {
        return true;
    }
    else
    {
        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

Application::Application()
    : m_instance(nullptr)
    , m_hWnd(nullptr)
    , m_running(false)
    , m_renderManager(new RenderManager())
{
}

Application::~Application()
{
    delete m_renderManager;
}

bool Application::init()
{
    m_config = getApplicationConfig();
    m_instance = GetModuleHandle(NULL);

    if (!createWindow())
    {
        return false;
    }

    if (!initImgui())
    {
        return false;
    }

    if (!m_renderManager->init(RenderConfig{m_config.customDraw, g_clearColor, m_hWnd }))
    {
        return false;
    }

    ::ShowWindow(m_hWnd, SW_SHOWDEFAULT);
    ::UpdateWindow(m_hWnd);

    m_running = true;
    return true;
}

bool Application::createWindow()
{
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
		wc.lpfnWndProc = _wndProc;
		wc.hInstance = m_instance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		wc.lpszClassName = g_className;
		::RegisterClassEx(&wc);

		// dwStyle设置为WS_OVERLAPPEDWINDOW这个参数时，才可以使用CW_USEDEFAULT这个宏，否则的话，全部默认是0
		// window style: WS_OVERLAPPEDWINDOW: 重叠窗口，一般默认为这个，包含了标题，最小化等
		// window style: WS_POPUP: 可以认为就是无边框，无最小化等，只包含一个客户区
		// window style ex: WS_EX_LAYERED: 测试发现即使设置了WS_OVERLAPPEDWINDOW，这个值的效果也相当于是WS_POPUP
		// window style ex: WS_EX_TOPMOST: 永远保持窗口在顶层
		// window style ex: WS_EX_TRANSPARENT: 这个和WS_EX_LAYERED组合就可以实现点击到本窗口下面的窗口, 再配合WS_EX_TOPMOST
		// 即可实现点击窗口后，下层的窗口响应点击事件，同时本窗口依然在顶层
		m_hWnd = CreateWindowEx(
            WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, //WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT
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
        g_clearColor[0] = g_clearColor[1] = g_clearColor[2] = g_clearColor[3] = 0.0f;
		::SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), 255, LWA_COLORKEY);
	}
	else
	{
		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, _wndProc, 0L, 0L, m_instance, NULL, NULL, NULL, NULL, g_className, NULL };
		::RegisterClassEx(&wc);
		m_hWnd = ::CreateWindow(wc.lpszClassName, windowName.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL, wc.hInstance, this);
	}

	if (m_hWnd == nullptr)
	{
		::UnregisterClass(g_className, m_instance);
		return false;
	}

    return true;
}

void Application::run()
{
    while (m_running)
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
                m_running = false;
            }
        }

        if (!m_running)
        {
            break;
        }

        // update your custom stuffs
        update();

        if (m_running)
        {
            m_renderManager->render();
        }
    }

    shutdown();
}

void Application::stop()
{
    m_running = false;
}

void Application::shutdown()
{
    m_renderManager->shutdown();
    ::DestroyWindow(m_hWnd);
    ::UnregisterClass(g_className, m_instance);
}

bool Application::initImgui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyh.ttc", 20.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
	IM_ASSERT(font != nullptr);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(m_hWnd);

    return true;
}

