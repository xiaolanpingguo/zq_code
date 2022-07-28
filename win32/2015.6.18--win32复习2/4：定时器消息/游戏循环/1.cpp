#include <windows.h>
#include <iostream>

#define _CLIENT_W 640
#define _CLIENT_H 480

int x, y;
bool b = true;
 
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
	case WM_LBUTTONDOWN:
		{
			//输入
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC dc = BeginPaint(hwnd, &ps);

			//输出
			Ellipse(dc, x - 20, y - 20, x + 20, y + 20);

			EndPaint(hwnd, &ps);
			return 0;
		}
	case WM_TIMER:
		{
			//逻辑
			if (b)
			{
				x += 5;
				if (x > _CLIENT_W)
					b = false;
			}
			else
			{
				x -= 5;
				if (x < 0)
					b = true;
			}

			InvalidateRect(hwnd, 0, TRUE);
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

	SetTimer(hwnd, 0, 33, 0); //30帧/秒

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	KillTimer(hwnd, 0);

	return 1;
}