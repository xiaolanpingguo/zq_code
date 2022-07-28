#include "dx11hook.h"
#include <Windows.h>
#include <d3d11.h>
#include <D3D11Shader.h>
#include <D3Dcompiler.h>
#include <mutex>
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


typedef HRESULT(__stdcall *D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
D3D11PresentHook g_phookD3D11Present = nullptr;

DWORD_PTR* g_pSwapChainVtable = nullptr;
ID3D11Device* g_pDevice = nullptr;
ID3D11DeviceContext* g_pContext = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;

WNDPROC g_hGameWindowProc;

Dx11Hook::ConfigData g_configData;


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
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
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pDevice)) &&
            SUCCEEDED(pSwapChain->GetDevice(__uuidof(g_pDevice), (void**)&g_pDevice)))
        {
            g_pDevice->GetImmediateContext(&g_pContext);
        }

        ID3D11Texture2D* pRenderTargetTexture = NULL;
        if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pRenderTargetTexture)) &&
            SUCCEEDED(g_pDevice->CreateRenderTargetView(pRenderTargetTexture, NULL, &g_pRenderTargetView)))
        {
            pRenderTargetTexture->Release();
        }

        HWND hGameWindow = (HWND)g_configData.gameWindow;
        g_hGameWindowProc = (WNDPROC)SetWindowLongPtr(hGameWindow, GWLP_WNDPROC, (LONG_PTR)hookWndProc);

        // init imgui
        ImGui::CreateContext();
        ImGui_ImplWin32_Init(hGameWindow);
        ImGui_ImplDX11_Init(g_pDevice, g_pContext);
    });

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


LRESULT WINAPI wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

namespace Dx11Hook{

bool start(const ConfigData& config)
{
    if (config.gameWindow == NULL)
    {
        return false;
    }

    g_configData = config;

    HMODULE hDXGIDLL = 0;
    int tryNum = 0;
    do
    {
        if (tryNum >= 15)
        {
            return false;
        }

        hDXGIDLL = GetModuleHandleA("dxgi.dll");
        Sleep(100);
        tryNum++;
    } while (!hDXGIDLL);
    Sleep(100);

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

    IDXGISwapChain* d3dSwapChain = 0;

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
        return false;
    }

    g_pSwapChainVtable = (DWORD_PTR*)g_pSwapChain;
    g_pSwapChainVtable = (DWORD_PTR*)g_pSwapChainVtable[0];

    g_phookD3D11Present = (D3D11PresentHook)g_pSwapChainVtable[8];
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)g_phookD3D11Present, hookD3D11Present);
    DetourTransactionCommit();

    DWORD dwOld;
    VirtualProtect(g_phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &dwOld);

    while (true)
    {
        Sleep(10);
    }

    return true;
}

bool shutdown()
{
    LOG_INFO("dll shutdown\n");

    g_pDevice->Release();
    g_pContext->Release();
    g_pSwapChain->Release();

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)g_pSwapChainVtable[8], hookD3D11Present);
    DetourTransactionCommit();
	return true;
}

}