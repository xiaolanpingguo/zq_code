#include <iostream>
#include "Main.h"
#include "Game.h"

#define _SLEEP_TIME 33

BOOL g_Active = TRUE;
HWND g_hWnd = 0;

LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_ACTIVATEAPP:
		{
			g_Active = (BOOL)wParam;
			return 0;
		}
	case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
				PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	//填充一个窗口类别结构体
	WNDCLASS wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "G03113121004";

	//注册窗口类别结构体
	RegisterClass(&wc);

	//计算窗口应在的位置
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	RECT r = {(sw - _CLIENT_W) / 2, (sh - _CLIENT_H) / 2, r.left + _CLIENT_W, r.top + _CLIENT_H};
	AdjustWindowRect(&r, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	//创建窗口
	g_hWnd = CreateWindow(
		wc.lpszClassName,
		"初始化DirectDraw",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		r.left,
		r.top,
		r.right - r.left,
		r.bottom - r.top,
		HWND_DESKTOP,
		0,
		wc.hInstance,
		0);

	Init(); //初始化

	//显示窗口
	ShowWindow(g_hWnd, nCmdShow);

	//更新窗口
	UpdateWindow(g_hWnd);

	//消息循环
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (g_Active)
		{
			int bt = GetTickCount();
			Run(); //运行
			int at = GetTickCount() - bt;
			Sleep(at < _SLEEP_TIME ? _SLEEP_TIME - at : 1);
		}
		else
			WaitMessage();
	}

	End(); //结束

	//注销窗口类别结构体
	UnregisterClass(wc.lpszClassName, wc.hInstance);

	//返回退出值给操作系统
	return (int)msg.wParam;
}

//DirectX组件
//1)DirectGraphics
//{
//	a)DirectDraw：二维图形绘制
//	b)Direct3D：三维图形绘制
//}
//2)DirectSound：低级音频
//3)DirectMusic：高级音频
//4)DirectInput：输入
//5)DirectPlay：网络
//6)DirectShow：流媒体

//DirectDraw到目前为止发展到7.0，我们安装的DirectSDK
//是9.0，注意DirectDraw的文档是在DirectSDK7.0开发包中的


DEFINE_GUID( IID_IDirectDraw7,                  0x15e65ec0,0x3b9c,0x11d2,0xb9,0x2f,0x00,0x60,0x97,0x97,0xea,0x5b );