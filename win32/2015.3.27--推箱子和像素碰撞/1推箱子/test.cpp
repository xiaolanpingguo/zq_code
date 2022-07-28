#include <windows.h>
#include "UseBmp.h"

#pragma comment(lib,"Msimg32.lib")

#define CLIENT_W 640
#define CLIENT_H 480
#define _GRID_W 100
#define _GRID_H 50
#define _GRID_HW (_GRID_W / 2)
#define _GRID_HH (_GRID_H / 2)
#define _INIT_X  (CLIENT_W / 2 - _GRID_W / 2)
#define _INIT_Y  0

#define _MAP_W 6
#define _MAP_H 6
#define _MAP_S (_MAP_W * _MAP_H)


//0 通路 0.bmp
//1 障碍 1.bmp
//2 箱子 2.bmp
//3 木   3.bmp
//4 困   4.bmp
//5 英雄 5
//6 囚
char map[_MAP_S] = 
{
	0,1,1,1,1,1,
	0,0,0,0,0,0,
	0,0,3,2,0,0,
	0,0,0,4,0,0,
	0,5,0,0,0,0,
	0,0,0,0,0,0
};

HDC bmpdc[7];

//窗口消息函数，本函数将被操作系统调用
__w64 long __stdcall WindowProc(HWND hwnd,//产生消息的窗口
								unsigned int uMsg,//消息类型
								__w64 unsigned int wParam,//消息附加参数1
								__w64 long lParam)//消息附加参数2
{
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			Rectangle(hdc,0,0,CLIENT_W,CLIENT_H);

			int offset[]
			= 
			{
				0,13,13,36,36,50,50
			};

			for(int i = 0; i < _MAP_S ;++i)
			{
				int x = i % _MAP_W;
				int y = i / _MAP_W;
				int rx = _INIT_X + (x - y) * _GRID_HW;
				int ry = _INIT_Y + (x + y) * _GRID_HH;

				TransparentBlt(hdc,rx,ry - offset[map[i]],_GRID_W, _GRID_H + offset[map[i]],bmpdc[map[i]],
					0,0,_GRID_W,_GRID_H + offset[map[i]],RGB(0,255,0));
			}

			EndPaint(hwnd,&ps);
			return 0;
		}
	}
	//我们不关心的消息就调用DefWindowProc(windows对所有消息的默认处理函数)来帮助我们处理
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//应用程序实例句柄
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	//01)填充一个窗口类别的结构体
	WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "八班";
	RegisterClass(&wc);

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	RECT r = 
	{
		(sw - CLIENT_W) / 2,
		(sh - CLIENT_H) / 2,
		(sw - CLIENT_W) / 2 + CLIENT_W,
		(sh - CLIENT_H) / 2 + CLIENT_H
	};

	AdjustWindowRect(&r,WS_OVERLAPPED | WS_CAPTION | 
		WS_SYSMENU,FALSE);

	HWND hWnd = CreateWindow(wc.lpszClassName,
							 "推箱子",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 r.left,//窗口的左上角x坐标
							 r.top,//窗口的左上角y坐标
							 r.right - r.left,//窗口的宽（像素）
							 r.bottom - r.top,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	bmpdc[0] = GetBmpDC(hWnd,"bmp\\0.bmp");
	bmpdc[1] = GetBmpDC(hWnd,"bmp\\1.bmp");
	bmpdc[2] = GetBmpDC(hWnd,"bmp\\2.bmp");
	bmpdc[3] = GetBmpDC(hWnd,"bmp\\3.bmp");
	bmpdc[4] = GetBmpDC(hWnd,"bmp\\4.bmp");
	bmpdc[5] = GetBmpDC(hWnd,"bmp\\5.bmp");
	bmpdc[6] = GetBmpDC(hWnd,"bmp\\6.bmp");

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		//如果发现有WM_KEYDOWN和WM_KEYUP消息就根据当前的输入法
		//在产生一个WM_CHAR消息并投递到消息队列中
		TranslateMessage(&msg);
		//派发消息回操作系统(估计就是下面DispatchMessage来调用窗口消息函数)
		DispatchMessage(&msg);
	}

	for(int i = 0; i < 7;++i)
		DeleteBmpDC(bmpdc[i]);

	return 1;
}