#pragma once


#include <windows.h>
#include <d3d11.h>
#include <string>
#include <functional>


struct RenderConfig
{
	std::function<void(void)> customDraw;
	int w = 800;
	int h = 600;
	bool isTransparent = true;
	std::wstring windowName;
};

class RenderManager
{
public:

    RenderManager();
    ~RenderManager();
	
	bool init(const RenderConfig& config);
	bool render();
	bool shutdown();

	void drawStrokeText(float x, float y, std::uint32_t color, const char* str);
	void drawNewText(float x, float y, std::uint32_t color, const char* str);
	void drawRect(float x, float y, float w, float h, std::uint32_t color, float thickness = 1.0f);
	void drawFilledRect(float x, float y, float w, float h, std::uint32_t color);
	void drawCircleFilled(float x, float y, float radius, std::uint32_t color, int segments = 0);
	void drawCircle(float x, float y, float radius, std::uint32_t color, int segments = 0);
	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, std::uint32_t color, float thickne = 1.0f);
	void drawTriangleFilled(float x1, float y1, float x2, float y2, float x3, float y3, std::uint32_t color);
	void drawLine(float x1, float y1, float x2, float y2, std::uint32_t color, float thickness = 1.0f);

private:

	static LRESULT WINAPI wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool initImgui();
	bool createDeviceD3D();
    void cleanupDeviceD3D();
    void createRenderTarget();
    void cleanupRenderTarget();

private:
	HMODULE m_instance;
	HWND m_hWnd;
	ID3D11Device* m_d3dDevice;
	ID3D11DeviceContext* m_d3dDeviceContext;
    IDXGISwapChain* m_swapChain;
	ID3D11RenderTargetView* m_mainRenderTargetView;

	float m_clearColor[4];
	RenderConfig m_config;
};

