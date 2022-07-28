#include <windows.h>
#include"UseBmp.h"
#include<time.h>
#pragma comment(lib,"msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480

#define MAP_W 16
#define MAP_H 12
#define MAP_S MAP_W*MAP_H

#define ALL_MAP_W 32
#define ALL_MAP_H 24
#define ALL_MAP_S ALL_MAP_W*ALL_MAP_H

#define _HUA 0
#define _CAO 1
#define _SHUI 2
#define _SHU 3


//主显示设备
HDC	g_mainDC;
//后备设备
HDC backDC;
//兼容设备
HDC g_bmpdc[2];
//备用设备
HDC byDC;
//格子的宽
int grid_w;
//格子的高
int grid_h;
//全地图
char allmap[ALL_MAP_W][ALL_MAP_H];
//地图
char map[MAP_W][MAP_H];
//地图位移
int offset_x;
int offset_y;
BOOL g_Act = TRUE;//窗口激活标志
//英雄像素位置
POINT hero_p;





void GameInit(HWND hwnd)
{
	hero_p.x =0;
	hero_p.y =0;
	grid_w = _CLIENT_W / MAP_W;
	grid_h = _CLIENT_H / MAP_H;
	g_mainDC = GetDC(hwnd);
	backDC = CreateCompatibleDC(g_mainDC);
	byDC = CreateCompatibleDC(g_mainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_mainDC,grid_w*ALL_MAP_W,grid_h*ALL_MAP_H);
	DeleteObject(SelectObject(byDC,hbmp));	
	HBITMAP hbmp1 = CreateCompatibleBitmap(g_mainDC,_CLIENT_W,_CLIENT_H);
	DeleteObject(SelectObject(backDC,hbmp1));	
	DeleteObject(hbmp);
	DeleteObject(hbmp1);
	g_bmpdc[0] = GetBmpDC(hwnd,"bmp\\0.bmp");
	g_bmpdc[1] = GetBmpDC(hwnd,"bmp\\1.bmp");
	
	offset_x = 0;
	offset_y = 0;
	for(int i=0;i<ALL_MAP_W;i++)
	{
		for(int j = 0;j<ALL_MAP_H;j++)
		{
			allmap[i][j] = rand()%4;
		}
	}
	/*for(int i=0 ;i<MAP_W;i++)
	{
		for(int j=0;j<MAP_H;j++)
		{
			map[i][j] = allmap[i][j];
		}
	}*/
	//BitBlt(backDC,0,0,grid_w*ALL_MAP_W,grid_h*ALL_MAP_H,0,0,0,WHITENESS);
	HBRUSH newh = CreateSolidBrush(RGB(255,215,0));
	HBRUSH oldh = (HBRUSH)SelectObject(byDC,newh);
	Rectangle(byDC,0,0,grid_w*ALL_MAP_W-1,grid_h*ALL_MAP_H-1);
	for(int j=0;j<ALL_MAP_H;j++)
	{
		for(int i=0;i<ALL_MAP_W;i++)
		{
			TransparentBlt(byDC,i*grid_w,j*grid_h,grid_w,grid_h,g_bmpdc[0],allmap[i][j]*40,0,40,30,RGB(0,255,0));
		}
	}
	SelectObject(backDC,oldh);
	DeleteObject(newh);
	DeleteObject(oldh);
}

void GameRun()
{
	BitBlt(backDC,0,0,grid_w*ALL_MAP_W,grid_h*ALL_MAP_H,0,0,0,WHITENESS);
	if(GetAsyncKeyState('W') & 0x8000)
	{
		if(offset_y>0&&hero_p.y<=_CLIENT_H/2)
			offset_y-=10;
		else
		{
			if(hero_p.y>0)
			{
				hero_p.y-=10;
			}
		}
	}
	if(GetAsyncKeyState('S') & 0x8000)
	{
		if(hero_p.y<_CLIENT_H/2||offset_y>=ALL_MAP_H*grid_h-_CLIENT_H)
		{
			if((hero_p.y+offset_y)<ALL_MAP_H*grid_h-grid_h)
				hero_p.y+=10;
		}
		else
			offset_y+=10;
	}
	if(GetAsyncKeyState('A') & 0x8000)
	{
		
		if(offset_x>0&&hero_p.x<=_CLIENT_W/2)
			offset_x-=10;
		else
		{
			if(hero_p.x>0)
			{
				hero_p.x-=10;
			}
		}
	}
	if(GetAsyncKeyState('D') & 0x8000)
	{
		if(hero_p.x<_CLIENT_W/2||offset_x>=ALL_MAP_W*grid_w-_CLIENT_W)
		{
			if((hero_p.x+offset_x)<ALL_MAP_W*grid_w-grid_w)
				hero_p.x+=10;
		}
		else
			offset_x+=10;
	}
	
	BitBlt(backDC,0,0,_CLIENT_W,_CLIENT_H,byDC,offset_x,offset_y,SRCCOPY);
	TransparentBlt(backDC,hero_p.x,hero_p.y,grid_w,grid_h,g_bmpdc[1],0,0,30,20,RGB(0,255,0));
	BitBlt(g_mainDC,0,0,_CLIENT_W,_CLIENT_H,backDC,0,0,SRCCOPY);
	BitBlt(backDC,0,0,grid_w*ALL_MAP_W,grid_h*ALL_MAP_H,0,0,0,WHITENESS);

	Sleep(33);

}

void GameEnd(HWND hwnd)
{
	ReleaseDC(hwnd,g_mainDC);
	DeleteBmpDC(g_bmpdc[0]);
	DeleteBmpDC(g_bmpdc[1]);
}



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
	case WM_ACTIVATEAPP:
	{
		g_Act=(BOOL)wParam;
		return 0;
	}
	case WM_DESTROY:
		{
			//投递一个WM_QUIT消息到本线程的消息队列中
			PostQuitMessage(0);
			//一般我们处理了某个消息都要直接返回0.
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
	wc.hIcon =0;

	wc.hCursor =0;

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
							 L"滚屏",//窗口标题栏文字
							 //WS_THICKFRAME 通过鼠标拖动改变窗口大小
							 //WS_MAXIMIZEBOX 窗口右上角的最大化和还原按钮
							 WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,//窗口风格
							 r.left,//窗口的左上角x坐标
							 r.top,//窗口的左上角y坐标
							 r.right - r.left,//窗口的宽（像素）
							 r.bottom - r.top,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	srand((unsigned int)time(0));

	GameInit(hWnd);
	MSG msg={} ;
	while (msg.message!=WM_QUIT)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(g_Act)
			GameRun();
		else
			WaitMessage();
	}
	GameEnd(hWnd);

	return 1;
}


