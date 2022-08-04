#include "dx11hook.h"
#include <Windows.h>
#include <d3d11.h>
#include <D3D11Shader.h>
#include <D3Dcompiler.h>
#include <mutex>
#include <thread>
#include "Detours/detours.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3dcompiler.lib")
#ifdef _WIN64
#pragma comment(lib, "detours64.lib")
#else
#pragma comment(lib, "detours32.lib")
#endif
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"
#include "../log.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


/*
you can look up Vtable funtions by add  /d1 reportSingleClassLayoutIDXGISwapChain to VS->C/C++>commandline
IDXGISwapChain  VTable
1> 0	| &IUnknown::QueryInterface
1> 1	| &IUnknown::AddRef
1> 2	| &IUnknown::Release
1> 3	| &IDXGIObject::SetPrivateData
1> 4	| &IDXGIObject::SetPrivateDataInterface
1> 5	| &IDXGIObject::GetPrivateData
1> 6	| &IDXGIObject::GetParent
1> 7	| &IDXGIDeviceSubObject::GetDevice
1> 8	| &IDXGISwapChain::Present
1> 9	| &IDXGISwapChain::GetBuffer
1>10	| &IDXGISwapChain::SetFullscreenState
1>11	| &IDXGISwapChain::GetFullscreenState
1>12	| &IDXGISwapChain::GetDesc
1>13	| &IDXGISwapChain::ResizeBuffers
1>14	| &IDXGISwapChain::ResizeTarget
1>15	| &IDXGISwapChain::GetContainingOutput
1>16	| &IDXGISwapChain::GetFrameStatistics
1>17	| &IDXGISwapChain::GetLastPresentCount
*/


namespace Dx11Hook {


typedef HRESULT(__stdcall* D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
D3D11PresentHook g_phookD3D11Present = nullptr;

typedef HRESULT(__stdcall* D3D11ResizeBufferHook) (IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
D3D11ResizeBufferHook g_presizeBufferHook = nullptr;

DWORD_PTR* g_pSwapChainVtable = nullptr;
ID3D11Device* g_pDevice = nullptr;
ID3D11DeviceContext* g_pContext = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
bool g_init = false;
WNDPROC g_hGameWindowProc;
Dx11Hook::ConfigData g_configData;


LRESULT CALLBACK hookWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CallWindowProc((WNDPROC)ImGui_ImplWin32_WndProcHandler, hWnd, uMsg, wParam, lParam);

    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse || io.WantCaptureKeyboard)
    {
        return true;
    }

    return CallWindowProc(g_hGameWindowProc, hWnd, uMsg, wParam, lParam);
}

HRESULT WINAPI hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, [&]()
    {
        ID3D11Device* oldDevice = g_pDevice;
        ID3D11DeviceContext* oldContext = g_pContext;

        if (FAILED(pSwapChain->GetDevice(__uuidof(g_pDevice), (void**)&g_pDevice)))
        {
            LOG_INFO("hookD3DPresent failed, GetDevice failed.\n");
            return;
        }

        g_pDevice->GetImmediateContext(&g_pContext);

        ID3D11Texture2D* pRenderTargetTexture = NULL;
        pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pRenderTargetTexture);
        if (pRenderTargetTexture)
        {
            if (FAILED(g_pDevice->CreateRenderTargetView(pRenderTargetTexture, NULL, &g_pRenderTargetView)))
            {
                LOG_INFO("hookD3DPresent failed, CreateRenderTargetView failed.\n");
                pRenderTargetTexture->Release();
                return;
            }
 
            pRenderTargetTexture->Release();
        }
        else
        {
            LOG_INFO("hookD3DPresent failed, pRenderTargetTexture == nullptr.\n");
            return;
        }

        HWND hGameWindow = (HWND)g_configData.gameWindow;
        if (hGameWindow == nullptr)
        {
            LOG_INFO("hookD3DPresent failed, hGameWindow == nullptr.\n");
            return;
        }

        g_hGameWindowProc = (WNDPROC)SetWindowLongPtr(hGameWindow, GWLP_WNDPROC, (LONG_PTR)hookWndProc);
        if (g_hGameWindowProc == nullptr)
        {
            LOG_INFO("hookD3DPresent failed, g_hGameWindowProc == nullptr.\n");
            return;
        }

        // init imgui
        ImGui::CreateContext();
        if (!ImGui_ImplWin32_Init(hGameWindow) || !ImGui_ImplDX11_Init(g_pDevice, g_pContext))
        {
            LOG_INFO("hookD3DPresent failed, imgui init failed.\n");
            return;
        }

        // release old object
        oldDevice->Release();
        oldContext->Release();
        g_init = true;

        LOG_INFO("hookD3DPresent success, pSwapChain         {}\n", (void*)pSwapChain);
        LOG_INFO("hookD3DPresent success, g_pDevice          {}\n", (void*)g_pDevice);
        LOG_INFO("hookD3DPresent success, g_pContext         {}\n", (void*)g_pContext);
    });

    if (!g_init)
    {
        return g_phookD3D11Present(pSwapChain, SyncInterval, Flags);
    }

    // must call before drawing
    g_pContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

    // custom rendering ---------------------------------------------

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (g_configData.renderFun)
    {
        g_configData.renderFun();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return g_phookD3D11Present(pSwapChain, SyncInterval, Flags);
}

HRESULT WINAPI hookD3D11ResizeBuffer(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    if (g_pDevice == nullptr)
    {
        return g_presizeBufferHook(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
    }

    LOG_INFO("hookD3D11ResizeBufferm, window will resize,Width{}, Height:{}.\n", Width, Height);
    if (g_pRenderTargetView)
    {
        g_pRenderTargetView->Release();
        g_pRenderTargetView = nullptr;
    }

    HRESULT hr = g_presizeBufferHook(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

    ID3D11Texture2D* pRenderTargetTexture = NULL;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pRenderTargetTexture);
    if (pRenderTargetTexture)
    {
        g_pDevice->CreateRenderTargetView(pRenderTargetTexture, NULL, &g_pRenderTargetView);
        pRenderTargetTexture->Release();
    }

    return hr;
}

LRESULT WINAPI wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool shutdown()
{
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    g_pSwapChain->Release();
    g_pRenderTargetView->Release();

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)g_pSwapChainVtable[8], hookD3D11Present);
    DetourDetach(&(PVOID&)g_pSwapChainVtable[13], hookD3D11ResizeBuffer);
    DetourTransactionCommit();
    return true;
}

bool threadStart(const ConfigData& config)
{
    if (config.gameWindow == nullptr)
    {
        LOG_INFO("start hook failed, config.gameWindow == NULL\n");
        return false;
    }

    g_configData = config;

    WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, wndProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
    RegisterClassExA(&wc);

    HWND hWnd = CreateWindowA(wc.lpszClassName, NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);

    D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
    D3D_FEATURE_LEVEL obtainedLevel;
    ID3D11Device* d3dDevice = nullptr;
    ID3D11DeviceContext* d3dContext = nullptr;

    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(scd));
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 1;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

    scd.BufferDesc.Width = 1;
    scd.BufferDesc.Height = 1;
    scd.BufferDesc.RefreshRate.Numerator = 0;
    scd.BufferDesc.RefreshRate.Denominator = 1;

    UINT createFlags = 0;
#ifdef _DEBUG
    createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    if (FAILED(D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        createFlags,
        requestedLevels,
        sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
        D3D11_SDK_VERSION,
        &scd,
        &g_pSwapChain,
        &g_pDevice,
        &obtainedLevel,
        &g_pContext)))
    {
        LOG_INFO("start hook failed, D3D11CreateDeviceAndSwapChain failed.\n");
        return false;
    }

    g_pSwapChainVtable = (DWORD_PTR*)g_pSwapChain;
    g_pSwapChainVtable = (DWORD_PTR*)g_pSwapChainVtable[0];
    g_phookD3D11Present = (D3D11PresentHook)g_pSwapChainVtable[8];
    g_presizeBufferHook = (D3D11ResizeBufferHook)g_pSwapChainVtable[13];
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)g_phookD3D11Present, hookD3D11Present);
    DetourAttach(&(PVOID&)g_presizeBufferHook, hookD3D11ResizeBuffer);
    DetourTransactionCommit();

    LOG_INFO("BaseAddr:              {}\n", (void*)GetModuleHandle(NULL));
    LOG_INFO("SwapChain:             {}\n", (void*)g_pSwapChain);
    LOG_INFO("SwapChainVtable:       {}\n", (void*)g_pSwapChainVtable);
    LOG_INFO("Device:                {}\n", (void*)g_pDevice);
    LOG_INFO("DeviceContext:         {}\n", (void*)g_pContext);
    LOG_INFO("D3D11Present:          {}\n", (void*)g_phookD3D11Present);

    while (true)
    {
        Sleep(10);
    }

    // When the target process exits, all resources will be released, so there is no need to release resources.
    // The code here is just a hint, and the code never be called here
    shutdown();
}

void start(const ConfigData& config)
{
    std::thread thr(&threadStart, config);
    thr.detach();
}

}