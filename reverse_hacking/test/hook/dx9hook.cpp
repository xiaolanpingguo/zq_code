#include "dx9hook.h"
#include <Windows.h>
#include <d3d9.h>
#include <mutex>
#include "Detours/detours.h"
#pragma comment(lib, "d3d9.lib")
#ifdef _WIN64
#pragma comment(lib, "detours64.lib")
#else
#pragma comment(lib, "detours32.lib")
#endif
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"
#include "../log.h"


/*
you can look up Vtable funtions by add  /d1 reportSingleClassLayoutIDirect3DDevice9  to VS->C/C++>commandline
IDirect3DDevice9   VTable
1> 0	| &IDirect3DDevice9::QueryInterface
1> 1	| &IDirect3DDevice9::AddRef
1> 2	| &IDirect3DDevice9::Release
1> 3	| &IDirect3DDevice9::TestCooperativeLevel
1> 4	| &IDirect3DDevice9::GetAvailableTextureMem
1> 5	| &IDirect3DDevice9::EvictManagedResources
1> 6	| &IDirect3DDevice9::GetDirect3D
1> 7	| &IDirect3DDevice9::GetDeviceCaps
1> 8	| &IDirect3DDevice9::GetDisplayMode
1> 9	| &IDirect3DDevice9::GetCreationParameters
1>10	| &IDirect3DDevice9::SetCursorProperties
1>11	| &IDirect3DDevice9::SetCursorPosition
1>12	| &IDirect3DDevice9::ShowCursor
1>13	| &IDirect3DDevice9::CreateAdditionalSwapChain
1>14	| &IDirect3DDevice9::GetSwapChain
1>15	| &IDirect3DDevice9::GetNumberOfSwapChains
1>16	| &IDirect3DDevice9::Reset
1>17	| &IDirect3DDevice9::Present
1>18	| &IDirect3DDevice9::GetBackBuffer
1>19	| &IDirect3DDevice9::GetRasterStatus
1>20	| &IDirect3DDevice9::SetDialogBoxMode
1>21	| &IDirect3DDevice9::SetGammaRamp
1>22	| &IDirect3DDevice9::GetGammaRamp
1>23	| &IDirect3DDevice9::CreateTexture
1>24	| &IDirect3DDevice9::CreateVolumeTexture
1>25	| &IDirect3DDevice9::CreateCubeTexture
1>26	| &IDirect3DDevice9::CreateVertexBuffer
1>27	| &IDirect3DDevice9::CreateIndexBuffer
1>28	| &IDirect3DDevice9::CreateRenderTarget
1>29	| &IDirect3DDevice9::CreateDepthStencilSurface
1>30	| &IDirect3DDevice9::UpdateSurface
1>31	| &IDirect3DDevice9::UpdateTexture
1>32	| &IDirect3DDevice9::GetRenderTargetData
1>33	| &IDirect3DDevice9::GetFrontBufferData
1>34	| &IDirect3DDevice9::StretchRect
1>35	| &IDirect3DDevice9::ColorFill
1>36	| &IDirect3DDevice9::CreateOffscreenPlainSurface
1>37	| &IDirect3DDevice9::SetRenderTarget
1>38	| &IDirect3DDevice9::GetRenderTarget
1>39	| &IDirect3DDevice9::SetDepthStencilSurface
1>40	| &IDirect3DDevice9::GetDepthStencilSurface
1>41	| &IDirect3DDevice9::BeginScene
1>42	| &IDirect3DDevice9::EndScene
1>43	| &IDirect3DDevice9::Clear
1>44	| &IDirect3DDevice9::SetTransform
1>45	| &IDirect3DDevice9::GetTransform
1>46	| &IDirect3DDevice9::MultiplyTransform
1>47	| &IDirect3DDevice9::SetViewport
1>48	| &IDirect3DDevice9::GetViewport
1>49	| &IDirect3DDevice9::SetMaterial
1>50	| &IDirect3DDevice9::GetMaterial
1>51	| &IDirect3DDevice9::SetLight
1>52	| &IDirect3DDevice9::GetLight
1>53	| &IDirect3DDevice9::LightEnable
1>54	| &IDirect3DDevice9::GetLightEnable
1>55	| &IDirect3DDevice9::SetClipPlane
1>56	| &IDirect3DDevice9::GetClipPlane
1>57	| &IDirect3DDevice9::SetRenderState
1>58	| &IDirect3DDevice9::GetRenderState
1>59	| &IDirect3DDevice9::CreateStateBlock
1>60	| &IDirect3DDevice9::BeginStateBlock
1>61	| &IDirect3DDevice9::EndStateBlock
1>62	| &IDirect3DDevice9::SetClipStatus
1>63	| &IDirect3DDevice9::GetClipStatus
1>64	| &IDirect3DDevice9::GetTexture
1>65	| &IDirect3DDevice9::SetTexture
1>66	| &IDirect3DDevice9::GetTextureStageState
1>67	| &IDirect3DDevice9::SetTextureStageState
1>68	| &IDirect3DDevice9::GetSamplerState
1>69	| &IDirect3DDevice9::SetSamplerState
1>70	| &IDirect3DDevice9::ValidateDevice
1>71	| &IDirect3DDevice9::SetPaletteEntries
1>72	| &IDirect3DDevice9::GetPaletteEntries
1>73	| &IDirect3DDevice9::SetCurrentTexturePalette
1>74	| &IDirect3DDevice9::GetCurrentTexturePalette
1>75	| &IDirect3DDevice9::SetScissorRect
1>76	| &IDirect3DDevice9::GetScissorRect
1>77	| &IDirect3DDevice9::SetSoftwareVertexProcessing
1>78	| &IDirect3DDevice9::GetSoftwareVertexProcessing
1>79	| &IDirect3DDevice9::SetNPatchMode
1>80	| &IDirect3DDevice9::GetNPatchMode
1>81	| &IDirect3DDevice9::DrawPrimitive
1>82	| &IDirect3DDevice9::DrawIndexedPrimitive
1>83	| &IDirect3DDevice9::DrawPrimitiveUP
1>84	| &IDirect3DDevice9::DrawIndexedPrimitiveUP
1>85	| &IDirect3DDevice9::ProcessVertices
1>86	| &IDirect3DDevice9::CreateVertexDeclaration
1>87	| &IDirect3DDevice9::SetVertexDeclaration
1>88	| &IDirect3DDevice9::GetVertexDeclaration
1>89	| &IDirect3DDevice9::SetFVF
1>90	| &IDirect3DDevice9::GetFVF
1>91	| &IDirect3DDevice9::CreateVertexShader
1>92	| &IDirect3DDevice9::SetVertexShader
1>93	| &IDirect3DDevice9::GetVertexShader
1>94	| &IDirect3DDevice9::SetVertexShaderConstantF
1>95	| &IDirect3DDevice9::GetVertexShaderConstantF
1>96	| &IDirect3DDevice9::SetVertexShaderConstantI
1>97	| &IDirect3DDevice9::GetVertexShaderConstantI
1>98	| &IDirect3DDevice9::SetVertexShaderConstantB
1>99	| &IDirect3DDevice9::GetVertexShaderConstantB
1>100	| &IDirect3DDevice9::SetStreamSource
1>101	| &IDirect3DDevice9::GetStreamSource
1>102	| &IDirect3DDevice9::SetStreamSourceFreq
1>103	| &IDirect3DDevice9::GetStreamSourceFreq
1>104	| &IDirect3DDevice9::SetIndices
1>105	| &IDirect3DDevice9::GetIndices
1>106	| &IDirect3DDevice9::CreatePixelShader
1>107	| &IDirect3DDevice9::SetPixelShader
1>108	| &IDirect3DDevice9::GetPixelShader
1>109	| &IDirect3DDevice9::SetPixelShaderConstantF
1>110	| &IDirect3DDevice9::GetPixelShaderConstantF
1>111	| &IDirect3DDevice9::SetPixelShaderConstantI
1>112	| &IDirect3DDevice9::GetPixelShaderConstantI
1>113	| &IDirect3DDevice9::SetPixelShaderConstantB
1>114	| &IDirect3DDevice9::GetPixelShaderConstantB
1>115	| &IDirect3DDevice9::DrawRectPatch
1>116	| &IDirect3DDevice9::DrawTriPatch
1>117	| &IDirect3DDevice9::DeletePatch
1>118	| &IDirect3DDevice9::CreateQuery
*/


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


namespace Dx9Hook {

typedef HRESULT(__stdcall* D3D9PresentHook) (IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
D3D9PresentHook g_phookD3D9Present = nullptr;

typedef HRESULT(__stdcall* D3D9ResetHook) (IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
D3D9ResetHook g_presetHook = nullptr;

typedef HRESULT(__stdcall* D3D9EndSceneHook)(IDirect3DDevice9* pDevice);
D3D9EndSceneHook g_pendSceneHook = nullptr;

IDirect3D9* g_pD3D = NULL;
IDirect3DDevice9* g_pDevice = NULL;
DWORD_PTR* g_pd3dDeviceVtable = nullptr;
bool g_init = false;
WNDPROC g_hGameWindowProc;
Dx9Hook::ConfigData g_configData;


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

HRESULT WINAPI hookD3D9Present(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, [&]()
    {
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
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        if (!ImGui_ImplWin32_Init(hGameWindow) || !ImGui_ImplDX9_Init(pDevice))
        {
            LOG_INFO("hookD3DPresent failed, imgui init failed.\n");
            return;
        }

        // release old object
        g_pDevice->Release();
        g_pDevice = pDevice;
        g_init = true;
        LOG_INFO("hookD3DPresent success, g_pDevice          {}\n", (void*)g_pDevice);
    });

    if (!g_init)
    {
        return g_phookD3D9Present(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
    }

    // custom rendering ---------------------------------------------

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (g_configData.renderFun)
    {
        g_configData.renderFun();
    }

    ImGui::EndFrame();
    if (g_pDevice->BeginScene() >= 0)
    {
        ImGui::Render();

        DWORD colorwrite, srgbwrite;
        g_pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &colorwrite);
        g_pDevice->GetRenderState(D3DRS_SRGBWRITEENABLE, &srgbwrite);
        g_pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
        g_pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        g_pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, colorwrite);
        g_pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, srgbwrite);
        g_pDevice->EndScene();
    }

    return g_phookD3D9Present(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT WINAPI hookD3D9Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    LOG_INFO("hookD3D9Reset, window will resize,Width{}, Height:{}.\n", pPresentationParameters->BackBufferWidth, pPresentationParameters->BackBufferHeight);
    ::ImGui_ImplDX9_InvalidateDeviceObjects();
    const HRESULT hr = g_presetHook(pDevice, pPresentationParameters);
    if (hr >= 0)
    {
        ::ImGui_ImplDX9_CreateDeviceObjects();
    }

    return hr;
}

HRESULT WINAPI hookD3D9EndScene(IDirect3DDevice9* pDevice)
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, [&]()
    {
        HWND hGameWindow = (HWND)g_configData.gameWindow;
        if (hGameWindow == nullptr)
        {
            LOG_INFO("hookD3D9EndScene failed, hGameWindow == nullptr.\n");
            return;
        }

        g_hGameWindowProc = (WNDPROC)SetWindowLongPtr(hGameWindow, GWLP_WNDPROC, (LONG_PTR)hookWndProc);
        if (g_hGameWindowProc == nullptr)
        {
            LOG_INFO("hookD3D9EndScene failed, g_hGameWindowProc == nullptr.\n");
            return;
        }

        // init imgui
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        if (!ImGui_ImplWin32_Init(hGameWindow) || !ImGui_ImplDX9_Init(pDevice))
        {
            LOG_INFO("hookD3D9EndScene failed, imgui init failed.\n");
            return;
        }

        // release old object
        g_pDevice->Release();
        g_pDevice = pDevice;
        g_init = true;
        LOG_INFO("hookD3D9EndScene success, g_pDevice          {}\n", (void*)g_pDevice);
    });

    if (!g_init)
    {
        return g_pendSceneHook(pDevice);
    }

    // custom rendering ---------------------------------------------

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (g_configData.renderFun)
    {
        g_configData.renderFun();
    }

    ImGui::EndFrame();
    ImGui::Render();

    DWORD colorwrite, srgbwrite;
    g_pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &colorwrite);
    g_pDevice->GetRenderState(D3DRS_SRGBWRITEENABLE, &srgbwrite);
    g_pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
    g_pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    g_pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, colorwrite);
    g_pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, srgbwrite);

    return g_pendSceneHook(pDevice);
}

LRESULT WINAPI wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool shutdown()
{
    LOG_INFO("dll shutdown\n");

    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    g_pD3D->Release();

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    //DetourDetach(&(PVOID&)g_pd3dDeviceVtable[17], hookD3D9Present);
    DetourDetach(&(PVOID&)g_pd3dDeviceVtable[16], hookD3D9Reset);
    DetourDetach(&(PVOID&)g_pd3dDeviceVtable[42], hookD3D9EndScene);
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

    // Create the D3D object.
    if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
    {
        LOG_INFO("start hook failed, Direct3DCreate9 failed\n");
        return false;
    }

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;// Need to use an explicit format with alpha if needing per-pixel alpha composition.
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice)))
    {
        LOG_INFO("start hook failed, CreateDevice failed\n");
        return false;
    }

    // there are two ways draw imgui: hook EndScene and Present
    g_pd3dDeviceVtable = (DWORD_PTR*)g_pDevice;
    g_pd3dDeviceVtable = (DWORD_PTR*)g_pd3dDeviceVtable[0];
    g_phookD3D9Present = (D3D9PresentHook)g_pd3dDeviceVtable[17];
    g_presetHook = (D3D9ResetHook)g_pd3dDeviceVtable[16];
    g_pendSceneHook = (D3D9EndSceneHook)g_pd3dDeviceVtable[42];
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    //DetourAttach(&(PVOID&)g_phookD3D9Present, hookD3D9Present);
    DetourAttach(&(PVOID&)g_presetHook, hookD3D9Reset);
    DetourAttach(&(PVOID&)g_pendSceneHook, hookD3D9EndScene);
    DetourTransactionCommit();

    LOG_INFO("BaseAddr:              {}\n", (void*)GetModuleHandle(NULL));
    LOG_INFO("Device:                {}\n", (void*)g_pDevice);
    LOG_INFO("g_pd3dDeviceVtable:    {}\n", (void*)g_pd3dDeviceVtable);
    LOG_INFO("g_phookD3D9Present:    {}\n", (void*)g_phookD3D9Present);
    LOG_INFO("g_presetHook:          {}\n", (void*)g_presetHook);
    LOG_INFO("g_pendSceneHook:       {}\n", (void*)g_pendSceneHook);

    while (true)
    {
        Sleep(10);
    }

    // When the target process exits, all resources will be released, so there is no need to release resources.
    // The code here is just a hint, and the code never be called here
    shutdown();

    return true;
}

void start(const ConfigData& config)
{
    std::thread thr(&threadStart, config);
    thr.detach();
}

}