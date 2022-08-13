#include "render_manager.h"
#include "r3/imgui/imgui.h"
#include "r3/imgui/imgui_impl_win32.h"
#include "r3/imgui/imgui_impl_dx11.h"
#pragma comment(lib, "d3d11.lib")



RenderManager::RenderManager()
    : m_d3dDevice(nullptr)
    , m_d3dDeviceContext(nullptr)
    , m_swapChain(nullptr)
    , m_mainRenderTargetView(nullptr)
{
}

RenderManager::~RenderManager()
{

}

bool RenderManager::init(const RenderConfig& config)
{
    m_config = config;
    if (!createDeviceD3D())
    {
        cleanupDeviceD3D();
        return false;
    }

    if (!initImgui())
    {
        return false;
    }

    return true;
}

bool RenderManager::render()
{
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
    m_d3dDeviceContext->ClearRenderTargetView(m_mainRenderTargetView, m_config.clearColor.data());
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    m_swapChain->Present(1, 0); // Present with vsync
    //g_pSwapChain->Present(0, 0); // Present without vsync

    return true;
}

bool RenderManager::shutdown()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    cleanupDeviceD3D();
    return true;
}

void RenderManager::resize(std::uint32_t w, std::uint32_t h)
{
    if (m_swapChain)
    {
		cleanupRenderTarget();
		m_swapChain->ResizeBuffers(0, w, h, DXGI_FORMAT_UNKNOWN, 0);
		createRenderTarget();
    }
}

bool RenderManager::initImgui()
{
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
    sd.OutputWindow = (HWND)m_config.hwnd;
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
    if (pBackBuffer)
    {
		m_d3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_mainRenderTargetView);
		pBackBuffer->Release();
    }
}

void RenderManager::cleanupRenderTarget()
{
    if (m_mainRenderTargetView) { m_mainRenderTargetView->Release(); m_mainRenderTargetView = nullptr; }
}

void RenderManager::drawStrokeText(float x, float y, std::uint32_t color, std::string_view str)
{
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y - 1), color, str.data());
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y + 1), color, str.data());
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x - 1, y), color, str.data());
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1, y), color, str.data());
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), color, str.data());
}

void RenderManager::drawNewText(float x, float y, std::uint32_t color, std::string_view str)
{
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), color, str.data());
}

void RenderManager::drawRect(float x1, float y1, float x2, float y2, std::uint32_t color, float thickness)
{
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x1, y1), ImVec2(x2, y2), color, 0, 0, thickness);
}

void RenderManager::drawFilledRect(float x1, float y1, float x2, float y2, std::uint32_t color)
{
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), color, 0, 0);
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

