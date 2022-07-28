#include <windows.h>
#include"UseBmp.h"

#pragma comment(lib,"msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480

#define MAP_W 20
#define MAP_H 20
#define MAP_S MAP_W*MAP_H

#define _TL 0
#define _ZA 1

#define _FALL 0
#define _UP 1
#define _NOMOVE 2


//格子属性
int grid_w = _CLIENT_W/MAP_W;
int grid_h = _CLIENT_H/MAP_H;
//地图
char map[MAP_S];
//主显示设备
HDC mainDC;
//后备设备
HDC backDC;
//兼容设备
HDC bmpdc[2];


BOOL g_Act = TRUE;//窗口激活标志

//英雄位置RECT
RECT hero_r;
//英雄存在标志
bool live;
//新英雄位置
RECT new_hero_r;
//英雄降落加速度
int a;
//英雄速度
int v;
//英雄状态的标志
int bz;


void GameInit(HWND hwnd)
{
	a= 2;
	v=10;
	bz=_FALL;
	mainDC = GetDC(hwnd);
	backDC = CreateCompatibleDC(mainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(mainDC,_CLIENT_W,_CLIENT_H);
	DeleteObject(SelectObject(backDC,hbmp));	
	DeleteObject(hbmp);
	bmpdc[0] =GetBmpDC(hwnd,"bmp\\0.bmp");
	bmpdc[1] =GetBmpDC(hwnd,"bmp\\1.bmp");
	
	live= false;
	for(int i=0;i<MAP_S;i++)
	{
		map[i] = _TL;
	}	
}
void GameRun()
{
	if(GetAsyncKeyState('A') & 0x8000)
	{
		int x = (hero_r.left - 10)/grid_w;
		int y1 = hero_r.top/grid_h;
		int y2 = hero_r.bottom/grid_h;
		if((hero_r.left - 10)>0)
		{
			int flag =0;
			for(int i=y1;i<=y2;i++)
			{
				if(map[x+i*MAP_W]==_ZA)
				{
					int cz = hero_r.left-(x+1)*grid_w-1;
					hero_r.left = (x+1)*grid_w+1;
					hero_r.right = hero_r.right - cz;
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				hero_r.left-=10;
				hero_r.right-=10;
			}
			
		}else
		{
			int cz = hero_r.left-1;
			hero_r.left = 1;
			hero_r.right = hero_r.right-cz;
		}
	}
	if(GetAsyncKeyState('D') & 0x8000)
	{
		int x = (hero_r.right + 10)/grid_w;
		int y1 = hero_r.top/grid_h;
		int y2 = hero_r.bottom/grid_h;
		if((hero_r.right + 10)<_CLIENT_W)
		{
			int flag =0;
			for(int i=y1;i<=y2;i++)
			{
				if(map[x+i*MAP_W]==_ZA)
				{
					int cz = x*grid_w-1-hero_r.right;
					hero_r.right = x*grid_w-1;
					hero_r.left = hero_r.left+cz;
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				hero_r.left+=10;
				hero_r.right+=10;
			}
			
		}else
		{
			int cz = _CLIENT_W-1 -hero_r.right;
			hero_r.right =_CLIENT_W-1 ;
			hero_r.left = hero_r.left +cz;
		}
	}
	if(GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		v = -14;
		bz = _UP;
	}
	BitBlt(backDC,0,0,_CLIENT_W,_CLIENT_H,0,0,0,WHITENESS);
	for(int i=0;i<MAP_S;i++)
	{
		int x = i%MAP_W;
		int y = i/MAP_W;
		if(map[i]==_ZA)
			TransparentBlt(backDC,x*grid_w,y*grid_h,grid_w,grid_h,bmpdc[0],0,0,40,30,RGB(0,255,0));
	}
	if(live)
	{
		TransparentBlt(backDC,hero_r.left,hero_r.top,hero_r.right-hero_r.left,hero_r.bottom-hero_r.top,bmpdc[1],0,0,56,56,RGB(0,255,0));
	}
	
	BitBlt(mainDC,0,0,_CLIENT_W,_CLIENT_H,backDC,0,0,SRCCOPY);
	BitBlt(backDC,0,0,_CLIENT_W,_CLIENT_H,0,0,0,WHITENESS);
	
	if(bz==_FALL)
	{
		if(v<=22)
			v= v+ a;
		int x1 = hero_r.left/grid_w;
		int x2 = hero_r.right/grid_w;
		int y = (hero_r.bottom+v)/grid_h;
			
		
		if(hero_r.bottom+v<_CLIENT_H)
		{
			for(int i=x1;i<=x2;i++)
			{
				if(map[i+y*MAP_W] == _ZA)
				{
					int cz = y*grid_h-1  - hero_r.bottom;
					hero_r.bottom = y*grid_h-1;
					hero_r.top =hero_r.top + cz;
					bz=_NOMOVE;
					v=10;
					break;
				}
			}
			if(bz==_FALL)
			{
				hero_r.bottom +=v;
				hero_r.top +=v;
			}
		}else
		{
			//差值
			int cz = _CLIENT_H-1 - hero_r.bottom;
			hero_r.bottom=_CLIENT_H-1;
			hero_r.top =hero_r.top + cz;
			bz=_NOMOVE;
			v=10;
		}
	}else
	if(bz==_NOMOVE)
	{
		int x1 = hero_r.left/grid_w;
		int x2 = hero_r.right/grid_w;
		int y = hero_r.bottom/grid_h+1;
		if(y<MAP_W)
		{
			int flag =0 ;
			for(int i=x1;i<=x2;i++)
			{
				if(map[i+y*MAP_W] == _ZA)
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				bz = _FALL;
			}
		}
	}else
	{
		int x1 = hero_r.left/grid_w;
		int x2 = hero_r.right/grid_w;
		int y = (hero_r.top+v)/grid_h;
			
		
		if(hero_r.top+v>0)
		{
			for(int i=x1;i<=x2;i++)
			{
				if(map[i+y*MAP_W] == _ZA)
				{
					int cz = hero_r.top-((y+1)*grid_h+1);
					hero_r.top =(y+1)*grid_h+1;
					hero_r.bottom = hero_r.bottom-cz;
					bz=_FALL;
					v=0;
					break;
				}
			}
			if(bz!=_FALL)
			{
				hero_r.bottom +=v;
				hero_r.top +=v;
			}
		}else
		{
			//差值
			int cz = hero_r.top-1;
			hero_r.top =1;
			hero_r.bottom=hero_r.bottom-cz;
			bz=_FALL;
			v=0;
		}
		v+=a;
		if(v==0)
			bz = _FALL;
	}
	Sleep(33);
}

void GameEnd(HWND hwnd)
{
	ReleaseDC(hwnd,mainDC);
	DeleteBmpDC(bmpdc[0]);
	DeleteBmpDC(bmpdc[1]);
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
	case WM_LBUTTONDOWN:
		{
			new_hero_r.left = LOWORD(lParam);
			new_hero_r.top = HIWORD(lParam);
			return 0;
		}
	case WM_LBUTTONUP:
		{
			new_hero_r.right = LOWORD(lParam);
			new_hero_r.bottom = HIWORD(lParam);
			if(new_hero_r.left!=new_hero_r.right||new_hero_r.bottom!=new_hero_r.top)
			{
				live = true;
				bz=_FALL;
				if(new_hero_r.left>new_hero_r.right)
				{
					int l = new_hero_r.left;
					new_hero_r.left = new_hero_r.right;
					new_hero_r.right =l;
				}
				if(new_hero_r.top>new_hero_r.bottom)
				{
					int l =new_hero_r.top;
					new_hero_r.top = new_hero_r.bottom;
					new_hero_r.bottom =l;
				}
				hero_r.left = new_hero_r.left;
				hero_r.right = new_hero_r.right;
				hero_r.top = new_hero_r.top;
				hero_r.bottom = new_hero_r.bottom;
			}
			else
				live = false;
			return 0;
		}
	case WM_DESTROY:
		{
			//投递一个WM_QUIT消息到本线程的消息队列中
			PostQuitMessage(0);
			//一般我们处理了某个消息都要直接返回0.
			return 0;
		}
	case WM_ACTIVATEAPP:
		{
			g_Act=(BOOL)wParam;
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			POINT p ={LOWORD(lParam),HIWORD(lParam)};
			int x = p.x/grid_w;
			int y = p.y/grid_h;
			RECT r;
			RECT r1 ={x*grid_w,y*grid_h,x*grid_w+grid_w,y*grid_h+grid_h};
			if(!IntersectRect(&r,&r1,&hero_r))
			{
				if(map[x+y*MAP_W] == _TL)
					map[x+y*MAP_W] = _ZA;
				else
					map[x+y*MAP_W] = _TL;
			}
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
							 L"简单移动",//窗口标题栏文字
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


