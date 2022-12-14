#include <windows.h>
#include "resource.h"

#define _CLIENT_W 640
#define _CLIENT_H 480

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

			//HIWORD部分
			//1）如果这个命令来自于一个控件，那么这个部分就是这个控件的事件消息（是一个整数，表示这个控件上面发生的事件），比如一个按钮被按下这个地方就是BN_CLICKED
			//2）如果这个命令来自于一个快捷键，那么这个部分为1
			//3）如果这个命令来自于一个菜单，那么这个部分为0

			//LOWORD部分
			//发出该命令的控件、快捷键、菜单项的ID号（在resource.h中）

			//lParam
			//如果这个命令来自于一个控件，则这个参数就是这个控件的窗口句柄
			//如果这个命令来自于一个快捷键或一个菜单，那么这个部分为0

			if (HIWORD(wParam) == 0)
			{
				switch (LOWORD(wParam))
				{
				case ID_40001:
					{
						MessageBoxA(hwnd, "按下了ABC", 0, 0);
						break;
					}
				case ID_40002:
					{
						PostQuitMessage(0);
						break;
					}
				case ID_40003:
					{
						MessageBoxA(hwnd, "按下了123", 0, 0);
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

	//此处将菜单的宏定义ID填入到MAKEINTRESOURCE中
	//用于初始化菜单
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

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
		TRUE); //有菜单

	HWND hwnd = CreateWindowA(
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

	//可以得到客户区的尺寸
	RECT r; //矩形结构体：左上角（left，top），右下角（right，bottom）
	GetClientRect(hwnd, &r);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}