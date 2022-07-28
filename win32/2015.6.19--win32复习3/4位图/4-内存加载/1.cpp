#include <windows.h>
#include <iostream>

#pragma comment(lib, "Msimg32.lib") //设置链接Msimg32.lib库，因为TransparentBlt的定义在这个库中

#define _CLIENT_W 800
#define _CLIENT_H 600

//允许从内存中创建位图
//HBITMAP CreateDIBitmap(
//						HDC hdc,
//					   CONST BITMAPINFOHEADER *lpbmih,
//					   DWORD fdwInit,
//					   CONST VOID *lpbInit,
//					   CONST BITMAPINFO *lpbmi,
//					   UINT fuUsage);

char fd[1440054];
HBITMAP hbmp;
HDC bmpdc;

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
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC dc = BeginPaint(hwnd, &ps); //主设备

			BitBlt(dc, 0, 0, 800, 600, bmpdc, 0, 0, SRCCOPY);

			EndPaint(hwnd, &ps);
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

	//读取位图文件到内存中
	//【文件头】14
	//【信息头】40
	//【颜色数据】??
	FILE* pf = 0;
	fopen_s(&pf, "abc", "rb");
	fread(fd, 1, 1440054, pf);
	fclose(pf);

	//异或还原
	for (int i = 0; i < 1440054; ++i)
	{
		fd[i] = fd[i] ^ 0xa7;
	}

	BITMAPINFOHEADER* pbih = (BITMAPINFOHEADER*)(fd + 14);

	HDC dc = GetDC(hwnd);

	hbmp = CreateDIBitmap(
		dc,
		pbih,
		CBM_INIT,
		fd + 54,
		(BITMAPINFO*)(pbih),
		DIB_RGB_COLORS);

	bmpdc = CreateCompatibleDC(dc);

	DeleteObject(SelectObject(bmpdc, hbmp));

	ReleaseDC(hwnd, dc);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DeleteDC(bmpdc);

	return 1;
}