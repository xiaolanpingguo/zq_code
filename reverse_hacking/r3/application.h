#pragma once


#include <windows.h>
#include <string>
#include <functional>


struct ApplicationConfig
{
	std::function<void(void)> customDraw;
	int w = 800;
	int h = 600;
	std::wstring windowName;
	bool isTransparent = true;
};


class RenderManager;
class Application
{
protected:

	Application();
	~Application();

	virtual bool init();
	virtual void run();
	virtual void shutdown();
	virtual ApplicationConfig getApplicationConfig() = 0;
	virtual void update() = 0;
	virtual bool initImgui();

	void stop();
	bool createWindow();

	static LRESULT WINAPI _wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return 0; };

protected:
	HMODULE m_instance;
	HWND m_hWnd;

	bool m_running;
	ApplicationConfig m_config;
	RenderManager* m_renderManager;
};


