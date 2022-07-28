#include <windows.h>
#include "UseBmp.h"

#pragma comment(lib,"Msimg32.lib")

#define CLIENT_W 640
#define CLIENT_H 480
#define HERO_W  20
#define HERO_H  30
#define HERO_SPEED 5
HDC bmpdc;

POINT hero = {160,240};

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
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_UP:
				{
					POINT p[]
					=
					{
						{hero.x,hero.y - HERO_SPEED},
						{hero.x + HERO_W / 2 ,hero.y - HERO_SPEED},
						{hero.x + HERO_W ,hero.y - HERO_SPEED}
					};

					bool go = true;

					for(int i = 0; i < 3;++i)
					{
						COLORREF c = GetPixel(bmpdc,p[i].x,p[i].y);

					    if(c == RGB(128,64,0))
						{
							go = false;
							break;
						}
					}
					if(go)
					{
						hero.y -= HERO_SPEED;
					}

				}
				break;
			case VK_DOWN:
				{
				
				}
				break;
			case VK_LEFT:
				{
				
				}
				break;
			case VK_RIGHT:
				{
					
				}
				break;
			}
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			BitBlt(hdc,0,0,640,480,bmpdc,0,0,SRCCOPY);

			Rectangle(hdc,hero.x,hero.y,hero.x + HERO_W, hero.y + HERO_H);

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
							 "像素碰撞",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 r.left,//窗口的左上角x坐标
							 r.top,//窗口的左上角y坐标
							 r.right - r.left,//窗口的宽（像素）
							 r.bottom - r.top,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0
	
	bmpdc = GetBmpDC(hWnd,"bmp\\0.bmp");
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

	DeleteBmpDC(bmpdc);

	return 1;
}