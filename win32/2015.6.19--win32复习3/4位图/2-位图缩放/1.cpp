#include <windows.h>
#include <iostream>

#pragma comment(lib, "Msimg32.lib") //设置链接Msimg32.lib库，因为TransparentBlt的定义在这个库中

#define _CLIENT_W 800
#define _CLIENT_H 600

//位图的使用
//1）通过LoadImage加载位图
//2）创建兼容设备，将新位图选入设备，注意保存老位图
//3）通过BitBlt等还是从选入了新位图的设备中拷贝颜色数据到主设备（BeginPaint、GetDC得到的设备）
//4）当不使用位图了，那么位图设备和位图都要释放

HBITMAP hbmp[2];
HDC bmpdc[2];

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

			//设置缩放的模式
			SetStretchBltMode(dc, HALFTONE);

			//带缩放功能的绘制
			StretchBlt(
				dc, //目标设备
				0, 0, 400, 300, //目标矩形
				bmpdc[0], //源设备
				0, 0, 1600, 1200, //源矩形
				SRCCOPY);

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

	//加载位图
	hbmp[0] = (HBITMAP)LoadImageA(
		0, //应用程序实例句柄
		"bliss.bmp", //路径
		IMAGE_BITMAP, //类型
		0, //加载宽，为0表示加载位图的整个宽度
		0, //加载高，为0表示加载位图的整个高度
		LR_LOADFROMFILE); //LR_LOADFROMFILE表示从外部文件加载

	//得到主设备
	HDC main_dc = GetDC(hwnd);

	//通过主设备创建兼容设备
	bmpdc[0] = CreateCompatibleDC(main_dc);

	//释放主设备
	ReleaseDC(hwnd, main_dc);

	//将位图选入到兼容设备中
	HBITMAP old_bmp0 = (HBITMAP)SelectObject(bmpdc[0], hbmp[0]);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//卸载老位图
	DeleteObject(old_bmp0);

	//释放设备（含有新位图）
	DeleteDC(bmpdc[0]);

	return 1;
}