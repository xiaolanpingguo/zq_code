#include <windows.h>
#include <iostream>

//窗口之间是用树形结构来组织，所以每个窗口都有一个
//父窗口，也可能有子窗口（或者从属窗口，类似子窗口
//但是有区别），一般的窗口都是以桌面窗口为父窗口的

#define _CLIENT_W 640
#define _CLIENT_H 480

HWND g_hwnd[4]; //所有窗口

LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg, //消息值
							WPARAM wParam, //消息的附加参数1
							LPARAM lParam) //消息的附加参数2
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_CLOSE:
		{
			//如果是主窗口发生了WM_CLOSE消息，那么
			//就用DefWindowProc来处理这个消息，将导
			//致WM_DESTROY被产生
			if (hwnd == g_hwnd[0] || hwnd == g_hwnd[3])
				break;

			//如果是其它窗口那么什么都不做
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
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "123abc";

	RegisterClass(&wc);

	//可以根据客户区大小来计算窗口大小
	int sw = GetSystemMetrics(SM_CXSCREEN); //得到桌面的宽
	int sh = GetSystemMetrics(SM_CYSCREEN); //得到桌面的高
	RECT cr //cr得到客户区的位置、尺寸
		=
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		(sw - _CLIENT_W) / 2 + _CLIENT_W,
		(sh - _CLIENT_H) / 2 + _CLIENT_H
	};
	//根据传入的客户区位置、尺寸来计算窗口应该有的位置、尺寸
	AdjustWindowRect(
		&cr, //客户区矩形，本函数执行完毕之后会填入窗口矩形
		WS_OVERLAPPEDWINDOW, //窗口风格
		FALSE); //有无菜单

	//主窗口
	g_hwnd[0] = CreateWindowA(
		wc.lpszClassName, //使用的窗口类别结构体的名字
		"hello world", //窗口标题栏文字
		WS_OVERLAPPEDWINDOW, //窗口风格
		cr.left, //窗口左上角x坐标
		cr.top, //窗口左上角y坐标
		cr.right - cr.left, //窗口宽
		cr.bottom - cr.top, //窗口高
		HWND_DESKTOP, //父窗口，一般来说填写桌面窗口
		0, //菜单句柄，不用就填写0
		wc.hInstance, //应用程序实例句柄
		0); //保留参数

	//子窗口（要填写WS_CHILD）
	//1）会被父窗口裁剪，就是超过父窗口的边界的部分不被绘制
	//2）跟随父窗口移动
	//3）如果父窗口被销毁，那么子窗口一定是先于父窗口被销毁
	g_hwnd[1] = CreateWindowA(
		wc.lpszClassName, //使用的窗口类别结构体的名字
		"子窗口", //窗口标题栏文字
		WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE, //窗口风格必须有WS_CHILD（子窗口）和WS_VISIBLE（可见）
		0, //窗口左上角x坐标
		0, //窗口左上角y坐标
		300, //窗口宽
		200, //窗口高
		g_hwnd[0], //父窗口
		0, //菜单句柄，不用就填写0
		wc.hInstance, //应用程序实例句柄
		0); //保留参数

	//从属窗口（不要填写WS_CHILD）
	//1）不会被父窗口裁剪
	//2）不跟随父窗口移动
	//3）如果父窗口被销毁，那么子窗口一定是先于父窗口被销毁
	g_hwnd[2] = CreateWindowA(
		wc.lpszClassName, //使用的窗口类别结构体的名字
		"从属窗口", //窗口标题栏文字
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, //窗口风格必须有WS_VISIBLE（可见）
		200, //窗口左上角x坐标
		300, //窗口左上角y坐标
		100, //窗口宽
		150, //窗口高
		g_hwnd[0], //父窗口
		0, //菜单句柄，不用就填写0
		wc.hInstance, //应用程序实例句柄
		0); //保留参数

	g_hwnd[3] = CreateWindowA(
		wc.lpszClassName, //使用的窗口类别结构体的名字
		"子窗口的子窗口", //窗口标题栏文字
		WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE, //窗口风格必须有WS_VISIBLE（可见）
		0, //窗口左上角x坐标
		0, //窗口左上角y坐标
		100, //窗口宽
		150, //窗口高
		g_hwnd[1], //父窗口
		0, //菜单句柄，不用就填写0
		wc.hInstance, //应用程序实例句柄
		0); //保留参数

	ShowWindow(g_hwnd[0], nCmdShow);
	UpdateWindow(g_hwnd[0]);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}