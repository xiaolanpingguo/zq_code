#include <windows.h>
#include <iostream>

#define _CLIENT_W 640
#define _CLIENT_H 480

HWND g_hwnd[4];

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
	case WM_COMMAND:
		{
			//wParam
			//高字：如果是控件那么就是控件事件，如果是快捷键那么就是1，如果是菜单那么就是0
			//低字：控件、快捷键、菜单的ID
			//lParam
			//如果是控件那么就是控件的窗口句柄，如果是快捷键、菜单那么就是0

			//下面的表达式为真就意味着有按钮被按下了
			if (HIWORD(wParam) == BN_CLICKED)
			{
				switch (LOWORD(wParam))
				{
				case 100:
					MessageBoxA(hwnd, "按钮1被按下", 0, 0);
					break;
				case 101:
					MessageBoxA(hwnd, "按钮2被按下", 0, 0);
					break;
				case 102:
					{
						static bool b = true;
						b = !b;

						if (!b)
						{
							//显示或隐藏窗口
							ShowWindow(g_hwnd[1], SW_HIDE);

							//屏蔽输入或激活输入窗口
							EnableWindow(g_hwnd[2], FALSE);
						}
						else
						{
							//显示或隐藏窗口
							ShowWindow(g_hwnd[1], SW_SHOW);

							//屏蔽输入或激活输入窗口
							EnableWindow(g_hwnd[2], TRUE);
						}

						break;
					}
				}
			}

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

	//凡是创建控件窗口，它必须设置为子窗口，不能是从
	//属窗口，如果是从属窗口根本无法响应WM_COMMAND消
	//息，Windows里面的这些控件的本质都是窗口，创建
	//这些控件其实就是创建子窗口，只不过用特殊的窗口
	//类别结构体来创建，至于创建的时候要填写什么字符
	//串，可以通过在MSDN中通过CreateWindow来查看，注
	//意所有的控件上面都会发送一些事情，这些事情往往
	//是用户对控件进行输入操作触发的，我们可以在这些
	//控件的父窗口的WM_COMMAND消息里面响应这些事件，
	//比如在按钮中最常用的事件就是BN_CLICKED，这表示
	//按钮上面发生了点击事件

	//创建按钮
	g_hwnd[1] = CreateWindowA(
		"button", //创建按钮必须用"button"
		"按钮1", //窗口标题栏文字
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, //窗口风格|按钮风格
		0, //窗口左上角x坐标
		0, //窗口左上角y坐标
		100, //窗口宽
		60, //窗口高
		g_hwnd[0], //父窗口，一般来说填写桌面窗口
		(HMENU)100, //如果是子窗口则此处填写一个整数表示其ID号，子窗口是不能有菜单的
		wc.hInstance, //应用程序实例句柄
		0); //保留参数

	g_hwnd[2] = CreateWindowA(
		"button", //创建按钮必须用"button"
		"按钮2", //窗口标题栏文字
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, //窗口风格|按钮风格
		0, //窗口左上角x坐标
		80, //窗口左上角y坐标
		100, //窗口宽
		60, //窗口高
		g_hwnd[0], //父窗口，一般来说填写桌面窗口
		(HMENU)101,
		wc.hInstance, //应用程序实例句柄
		0); //保留参数

	g_hwnd[3] = CreateWindowA(
		"button", //创建按钮必须用"button"
		"按钮3", //窗口标题栏文字
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, //窗口风格|按钮风格
		0, //窗口左上角x坐标
		160, //窗口左上角y坐标
		100, //窗口宽
		60, //窗口高
		g_hwnd[0], //父窗口，一般来说填写桌面窗口
		(HMENU)102,
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