#include <windows.h>
#include"UseBmp.h"
#include<iostream>

#pragma comment(lib,"MSIMG32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480

#define _XDL 5   //行动力

//兼容设备
HDC bmpdc; 
//客户区大小
RECT client_r;
//英雄矩形
RECT hero_r={220,290,240,320};

__w64 long __stdcall WindowProc(HWND hwnd,//产生消息的窗口
								unsigned int uMsg,//消息类型
								__w64 unsigned int wParam,//消息附加参数1
								__w64 long lParam)//消息附加参数2
{
	switch(uMsg)
	{
	//销毁消息触发方式
	//1)点击系统菜单的关闭菜单项（Alt + F4）
	//2)右上角的X按钮
	case WM_DESTROY:
		{
			//投递一个WM_QUIT消息到本线程的消息队列中
			PostQuitMessage(0);
			//一般我们处理了某个消息都要直接返回0.
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);
			GetClientRect(hwnd,&client_r);

			TransparentBlt(hdc,client_r.left,client_r.top,client_r.right,client_r.bottom,
						   bmpdc,0,0,640,480,RGB(0,0,0));
			Rectangle(hdc,hero_r.left,hero_r.top,hero_r.right,hero_r.bottom);

			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			POINT p ={LOWORD(lParam),HIWORD(lParam)};
			char buf[256];
			HDC hdc = GetDC(hwnd);
			COLORREF color = GetPixel(hdc,p.x,p.y);
			unsigned char r =  GetRValue(color);
			unsigned char g =  GetGValue(color);
			unsigned char b =  GetBValue(color);
			sprintf_s(buf,256,"R:%d,G:%d,B:%d",r,g,b);
			MessageBoxA(hwnd,buf,"提示",MB_OK);
			ReleaseDC(hwnd,hdc);
			return 0;
		}
	case WM_KEYDOWN:
		{
			HDC hdc = GetDC(hwnd);
			COLORREF color;
			//上
			if(wParam == VK_UP)
			{
				RECT r ={ hero_r.left,hero_r.top-_XDL,hero_r.right,hero_r.top};
				int flag = 0;
				for(int i = r.left;i<=r.right;i++)
				{
					int flag1=0;
					for(int j =r.top;j<r.bottom;j++)
					{
						color = GetPixel(hdc,i,j);
						if(color==RGB(128,64,0))
						{
							flag =1;
							flag1 =1;
							break;
						}
					}
					if(flag1==1)
						break;
				}
				if(flag == 0)
				{
					hero_r.top-=_XDL;
					hero_r.bottom-=_XDL;
					InvalidateRect(hwnd,0,TRUE);
				}
			}
			//下
			if(wParam == VK_DOWN)
			{
				RECT r ={ hero_r.left,hero_r.bottom,hero_r.right,hero_r.bottom+_XDL};
				int flag = 0;
				for(int i = r.left;i<=r.right;i++)
				{
					int flag1=0;
					for(int j =r.top+1;j<=r.bottom;j++)
					{
						color = GetPixel(hdc,i,j);
						if(color==RGB(128,64,0))
						{
							flag =1;
							flag1 =1;
							break;
						}
					}
					if(flag1==1)
						break;
				}
				if(flag == 0)
				{
					hero_r.top+=_XDL;
					hero_r.bottom+=_XDL;
					InvalidateRect(hwnd,0,TRUE);
				}
			}
			//左
			if(wParam == VK_LEFT)
			{
				RECT r ={ hero_r.left-_XDL,hero_r.top,hero_r.left,hero_r.bottom};
				int flag = 0;
				for(int i = r.left;i<r.right;i++)
				{
					int flag1=0;
					for(int j =r.top;j<=r.bottom;j++)
					{
						color = GetPixel(hdc,i,j);
						if(color==RGB(128,64,0))
						{
							flag =1;
							flag1 =1;
							break;
						}
					}
					if(flag1==1)
						break;
				}
				if(flag == 0)
				{
					hero_r.left-=_XDL;
					hero_r.right-=_XDL;
					InvalidateRect(hwnd,0,TRUE);
				}
			}
			//右
			if(wParam == VK_RIGHT)
			{
				RECT r ={ hero_r.right-_XDL,hero_r.top,hero_r.right+_XDL,hero_r.bottom};
				int flag = 0;
				for(int i = r.left+1;i<=r.right;i++)
				{
					int flag1=0;
					for(int j =r.top;j<=r.bottom;j++)
					{
						color = GetPixel(hdc,i,j);
						if(color==RGB(128,64,0))
						{
							flag =1;
							flag1 =1;
							break;
						}
					}
					if(flag1==1)
						break;
				}
				if(flag == 0)
				{
					hero_r.left+=_XDL;
					hero_r.right+=_XDL;
					InvalidateRect(hwnd,0,TRUE);
				}
			}
			ReleaseDC(hwnd,hdc);
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
	WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 0;

	wc.hCursor = 0;

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wc.lpszMenuName = 0;

	wc.lpszClassName = L"八班";

	RegisterClass(&wc);

	//得到当前桌面的宽和高
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	//窗口的位置，大小
	RECT r = 
	{
		(sw - _CLIENT_W)/2,
		(sh - _CLIENT_H)/2,
		(sw - _CLIENT_W)/2 + _CLIENT_W,
		(sh - _CLIENT_H)/2 + _CLIENT_H
	};

	AdjustWindowRect(&r,//设定的客户区的位置，宽高
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,//窗口风格
	FALSE);//是否有菜单

	//03)用窗口类别结构体来创建窗口
	HWND hWnd = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 L"像素碰撞",//窗口标题栏文字
							 //WS_THICKFRAME 通过鼠标拖动改变窗口大小
							 //WS_MAXIMIZEBOX 窗口右上角的最大化和还原按钮
							 WS_OVERLAPPEDWINDOW ,//& ~WS_THICKFRAME ,//& ~WS_MAXIMIZEBOX,//窗口风格
							 r.left,//窗口的左上角x坐标
							 r.top,//窗口的左上角y坐标
							 r.right - r.left,//窗口的宽（像素）
							 r.bottom - r.top,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	bmpdc = GetBmpDC(hWnd,"0.bmp");

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);


	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DeleteDC(bmpdc);

	return 1;
}


