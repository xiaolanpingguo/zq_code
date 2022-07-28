#include <windows.h>
#include <vector>
#include "FindPath.h"
#include "UseBmp.h"

#pragma comment(lib,"MSIMG32.lib")

HDC bmpdc[2];

#define _MAP_W 15
#define _MAP_H 12
#define _MAP_S (_MAP_W * _MAP_H)

#define _TL 0

char map[_MAP_S];

int g_xw;
int g_xh;

bool g_isHeroMove = false;

POINT g_heroPoint = {0,0};

int path[_MAP_S];
int pathlen = 0;

int curpath;//当前位置
int curstep;//当前步数
int herox;
int heroy;

int hero_dir = 1;//0123上下左右

RECT rect;
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
	case WM_LBUTTONDOWN:
		{
			if(g_isHeroMove)
				return 0;
			int x = LOWORD(lParam) / g_xw;
			int y = HIWORD(lParam) / g_xh;
			bool find = CFindPath::FindPathW(
				map,_MAP_W,_MAP_H,
				g_heroPoint.x + g_heroPoint.y * _MAP_W,
				x + y * _MAP_W,path,&pathlen);
			if(!find)
				return 0;

			g_isHeroMove = true;
			//得到英雄当前的像素位置和图片
			curpath = 0;//当前在路径数组中的位置

			curstep = 0;//当前步数

			herox = g_heroPoint.x * g_xw;
			heroy = g_heroPoint.y * g_xh;

			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			int x = LOWORD(lParam) / g_xw;
			int y = HIWORD(lParam) / g_xh;

			if(map[x + y * _MAP_W] == _TL)
				map[x + y * _MAP_W] = 1;
			else 
				map[x + y * _MAP_W] = _TL;
			return 0;
		}
	case WM_TIMER:
		{
			if(g_isHeroMove)
			{
				if(curpath == pathlen - 1)
				{
					g_isHeroMove = false;
					return 0;
				}
				//得到方向
				switch(path[curpath + 1] - path[curpath])
				{
				case -_MAP_W:hero_dir = 0;break;
				case _MAP_W: hero_dir = 1;break;
				case -1:hero_dir = 2;break;
				case 1:hero_dir = 3;break;
				}

				if(curstep == 3)
				{
					curpath += 1;
					curstep = 0;
					g_heroPoint.x = path[curpath] % _MAP_W;
					g_heroPoint.y = path[curpath] / _MAP_W;
				}
				else
				{
					++curstep;

					switch(hero_dir)
					{
					case 0:heroy -= g_xh/3;break;
					case 1:heroy += g_xh/3;break;
					case 2:herox -= g_xw/3;break;
					case 3:herox += g_xw/3;break;
					}
				}

			}
			
			for(int i = 0; i < _MAP_S;++i)
			{
				if(map[i] != _TL)
				{
					if(map[i] == 8)
						map[i] = 1;
					else
						map[i] += 1;
				}
			}
			
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			bool gaibian = false;

			RECT clientRect ;
			GetClientRect(hwnd,&clientRect);
			if(rect.right - rect.left != clientRect.right - clientRect.left
			|| rect.bottom - rect.top != clientRect.bottom - clientRect.top)
				gaibian = true;
			rect = clientRect;

			int cw = clientRect.right - clientRect.left;
			int ch = clientRect.bottom - clientRect.top;
			
			//Rectangle(hdc,0,0,clientRect.right,clientRect.bottom);
			g_xw = cw / _MAP_W;
			g_xh = ch / _MAP_H;

			for(int i = 1; i < _MAP_H; ++i)
			{
				POINT p;
				MoveToEx(hdc,0,i * g_xh,&p);
				LineTo(hdc,cw,g_xh * i);
			}
			for(int i = 1; i < _MAP_W; ++i)
			{
				POINT p;
				MoveToEx(hdc,i * g_xw,0,&p);
				LineTo(hdc,g_xw * i,ch);
			}

			for(int i = 0 ; i < _MAP_S; ++i)
			{
				if(map[i] != _TL)
				{
					int x = (i % _MAP_W) * g_xw;
					int y = (i / _MAP_W) * g_xh;
					TransparentBlt(hdc,x,y,g_xw,g_xh,bmpdc[1],(map[i] - 1)* 30,0,30,33,RGB(0,255,0));
				}
			}

			//绘制英雄

			if(gaibian)
			{
				herox = g_heroPoint.x * g_xw;
				heroy = g_heroPoint.y * g_xh;
			}
			if(g_isHeroMove)
			{
				TransparentBlt(hdc,herox,heroy,g_xw,g_xh,bmpdc[0],
					curstep * 30,hero_dir * 33,30,33,RGB(0,255,0));
			}
			else
			{

				TransparentBlt(hdc,herox,heroy,g_xw,g_xh,bmpdc[0],
					0,hero_dir * 33,30,33,RGB(0,255,0));
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

	HWND hWnd = CreateWindow(wc.lpszClassName,
							 "人",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	bmpdc[0] = GetBmpDC(hWnd,"bmp\\0.bmp");
	bmpdc[1] = GetBmpDC(hWnd,"bmp\\1.bmp");
	
	GetClientRect(hWnd,&rect);

	for(int i = 0; i < _MAP_S;++i)
		map[i] = _TL;

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	
	SetTimer(hWnd,0,40,0);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		//如果发现有WM_KEYDOWN和WM_KEYUP消息就根据当前的输入法
		//在产生一个WM_CHAR消息并投递到消息队列中
		TranslateMessage(&msg);
		//派发消息回操作系统(估计就是下面DispatchMessage来调用窗口消息函数)
		DispatchMessage(&msg);
	}

	KillTimer(hWnd,0);
	DeleteBmpDC(bmpdc[0]);
	DeleteBmpDC(bmpdc[1]);

	return 1;
}