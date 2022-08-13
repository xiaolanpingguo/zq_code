#pragma once


#include <windows.h>
#include <d3d11.h>
#include <string>
#include <string_view>
#include <functional>
#include <array>


struct RenderConfig
{
	std::function<void(void)> customDraw;
	std::array<float,4> clearColor;
	void* hwnd;
};

class RenderManager
{
public:

    RenderManager();
    ~RenderManager();
	
	bool init(const RenderConfig& config);
	bool render();
	bool shutdown();

	void drawStrokeText(float x, float y, std::uint32_t color, std::string_view str);
	void drawNewText(float x, float y, std::uint32_t color, std::string_view str);
	void drawRect(float x1, float y1, float x2, float y2, std::uint32_t color, float thickness = 1.0f);
	void drawFilledRect(float x1, float y1, float x2, float y2, std::uint32_t color);
	void drawCircleFilled(float x, float y, float radius, std::uint32_t color, int segments = 0);
	void drawCircle(float x, float y, float radius, std::uint32_t color, int segments = 0);
	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, std::uint32_t color, float thickne = 1.0f);
	void drawTriangleFilled(float x1, float y1, float x2, float y2, float x3, float y3, std::uint32_t color);
	void drawLine(float x1, float y1, float x2, float y2, std::uint32_t color, float thickness = 1.0f);

	void resize(std::uint32_t w, std::uint32_t h);
private:

	bool initImgui();
	bool createDeviceD3D();
    void cleanupDeviceD3D();
    void createRenderTarget();
    void cleanupRenderTarget();

private:
	ID3D11Device* m_d3dDevice;
	ID3D11DeviceContext* m_d3dDeviceContext;
    IDXGISwapChain* m_swapChain;
	ID3D11RenderTargetView* m_mainRenderTargetView;

	RenderConfig m_config;
};

