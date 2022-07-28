#include <windows.h>
#include<vector>
#include"Astar.h"

#pragma comment(lib,"MSIMG32.lib")

#define _CLIENT_W 800
#define _CLIENT_H 600

#define MAP_W 20
#define MAP_H 15
#define MAP_S MAP_W*MAP_H

#define _LEFT 2
#define _RIGHT 3
#define _UP 0
#define _DOWN 1

#define _KD 1
#define _ZA 0



HDC GetBmpDC(HWND hwnd,const char* bmpfile)
{
	HBITMAP hbmp = (HBITMAP)LoadImageA(0,bmpfile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(!hbmp)
		return 0;
	//窗口主显示设备
	//HDC maindc = GetDC(HWND_DESKTOP);
	//得到主设备
	HDC maindc = GetDC(hwnd);

	//创建兼容显示设备
	HDC bmpdc = CreateCompatibleDC(maindc);

	//将新位图选入兼容设备中
	HBITMAP oldbmp = (HBITMAP)SelectObject(bmpdc,hbmp);

	//删除新位图，新位图选入到兼容设备后，兼容设备内部就完整的
	//复制了一份新位图的数据
	DeleteObject(hbmp);

	//删除老位图
	DeleteObject(oldbmp);

	//释放主设备
	ReleaseDC(hwnd,maindc);

	return bmpdc;
}

void DeleteBmpDC(HDC hdc)
{
	DeleteDC(hdc);
}

struct ZA
{
	POINT p;
	int time;
};

char map[MAP_S];

//障碍vector


HDC bmpdc[2];
//每个格子的宽
int ew=_CLIENT_W/MAP_W;
//每个格子的高
int eh=_CLIENT_H/MAP_H;
//英雄位置
POINT Hero_p;
//定义英雄方向
int dir;
//终点
POINT end_p;
//是否处于移动状态
bool isMove;
//移动时的图片切换
int pic;
//计步器
int jbq;
//存放障碍的vector
std::vector<ZA> g_vZa;
//移动时的路长
int luchang;
//存放移动时的路径
int path[MAP_S];
//移动过程下标记录
int flag;




//窗口消息函数，本函数将被操作系统调用
__w64 long __stdcall WindowProc(HWND hwnd,//产生消息的窗口
								unsigned int uMsg,//消息类型
								__w64 unsigned int wParam,//消息附加参数1
								__w64 long lParam)//消息附加参数2
{
	switch(uMsg)
	{
	case WM_CREATE:
		{
			/*g_vZa.clear();*/
			for(int i=0;i<MAP_S;i++)
			{
				map[i]=_KD;
			}
			Hero_p.x = 0;
			Hero_p.y = 0;
			dir=_DOWN;
			isMove=false;
			pic=1;
			jbq=1;
			return 0;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);
			for(int i=0;i<=MAP_H;i++)
			{
				POINT p;
				MoveToEx(hdc,0,i*eh,&p);
				LineTo(hdc,_CLIENT_W-1,i*eh);
			}
			for(int i=0;i<=MAP_W;i++)
			{
				POINT p;
				MoveToEx(hdc,i*ew,0,&p);
				LineTo(hdc,i*ew,_CLIENT_H-1);
			}
			for(std::vector<ZA>::iterator i=g_vZa.begin();i!=g_vZa.end();i++)
			{
				TransparentBlt(hdc,
						i->p.x*ew,
						i->p.y*eh,
						ew,
						eh,
						bmpdc[1],
						30*(i->time),
						0,
						30,
						33,
						RGB(0,255,0));
				if(i->time==7)
				{
					i->time=0;
				}else
				{
					i->time++;
				}
			}
			if(!isMove)
			{
				TransparentBlt(hdc,
						Hero_p.x*ew,
						Hero_p.y*eh,
						ew,
						eh,
						bmpdc[0],
						0,
						33*dir,
						30,
						33,
						RGB(0,255,0));
			}else
			{
				int k = path[flag]-path[flag-1];
				switch(k)
				{
				case MAP_W:
					{
						dir = _UP;
						break;
					}
				case -MAP_W:
					{
						dir = _DOWN;
						break;
					}
				case 1:
					{
						dir = _LEFT;
						break;
					}
				case -1:
					{
						dir = _RIGHT;
						break;
					}
				}
				switch(dir)
				{
				case _RIGHT:
					{
						TransparentBlt(hdc,
						Hero_p.x*ew+jbq*ew/4,
						Hero_p.y*eh,
						ew,
						eh,
						bmpdc[0],
						30*pic,
						33*dir,
						30,
						33,
						RGB(0,255,0));
						break;
					}
				case _LEFT:
					{
						TransparentBlt(hdc,
						Hero_p.x*ew-jbq*ew/4,
						Hero_p.y*eh,
						ew,
						eh,
						bmpdc[0],
						30*pic,
						33*dir,
						30,
						33,
						RGB(0,255,0));
						break;
					}
				case _UP:
					{
						TransparentBlt(hdc,
						Hero_p.x*ew,
						Hero_p.y*eh-jbq*eh/4,
						ew,
						eh,
						bmpdc[0],
						30*pic,
						33*dir,
						30,
						33,
						RGB(0,255,0));
						break;
					}
				case _DOWN:
					{
						TransparentBlt(hdc,
						Hero_p.x*ew,
						Hero_p.y*eh+jbq*eh/4,
						ew,
						eh,
						bmpdc[0],
						30*pic,
						33*dir,
						30,
						33,
						RGB(0,255,0));
						break;
					}
				}
				if(pic==1)
				{
					pic=2;
				}else
				{
					pic=1;
				}
				jbq++;
				if(jbq == 4+1)
				{
					jbq = 1;
					Hero_p.x = path[flag-1]%MAP_W;
					Hero_p.y = path[flag-1]/MAP_W;
					flag --;
					if(flag==0)
					{
						isMove = false;
					}
					InvalidateRect(hwnd,0,TRUE);
				}
				

			}
		
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_TIMER:
		{
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			if(!isMove)
			{
				int x1 = LOWORD(lParam)/ew;
				int y1 = HIWORD(lParam)/eh;
				end_p.x = x1;
				end_p.y = y1;
				if(map[x1 + y1 * MAP_W] != _ZA && ((Hero_p.x + Hero_p.y * MAP_W) != (x1 +y1 * MAP_W)))
				{
					luchang = AStar::FindPath(map,20,15,Hero_p.x + Hero_p.y * MAP_W ,x1 + y1 * MAP_W,path);
					if(luchang>0)
					{
						isMove = true;
						flag = luchang -1;
						InvalidateRect(hwnd,0,TRUE);
					}
				}
			}
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			if(!isMove)
			{
				POINT p = {LOWORD(lParam),HIWORD(lParam)};
				int x1 = p.x/ew;
				int y1 = p.y/eh;
				p.x = x1;
				p.y = y1;
				if(map[x1+y1*MAP_W]==_KD&&((Hero_p.x+Hero_p.y*MAP_W)!=(x1+y1*MAP_W)))
				{
					ZA z ={p,0};
					g_vZa.push_back(z);
					map[x1+y1*MAP_W]=_ZA;
					InvalidateRect(hwnd,0,TRUE);
				}else
				if(map[x1+y1*MAP_W]==_ZA)
				{
					for(std::vector<ZA>::iterator i = g_vZa.begin();i!=g_vZa.end();i++)
					{
						if(i->p.x ==p.x&&i->p.y == p.y)
						{
							g_vZa.erase(i);
							map[x1+y1*MAP_W]=_KD;
							InvalidateRect(hwnd,0,TRUE);
							break;
						}
					}
				}
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
	wc.lpszClassName = L"八班";
	RegisterClass(&wc);
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
	
	
	HWND hWnd = CreateWindow(wc.lpszClassName,
							 L"左键移动英雄、右键设置取消障碍",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,//窗口风格
							 r.left,//窗口的左上角x坐标
							 r.top,//窗口的左上角y坐标
							 r.right-r.left,//窗口的宽（像素）
							 r.bottom-r.top,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0
	
	
	bmpdc[0] = GetBmpDC(hWnd,"0.bmp");
	bmpdc[1] = GetBmpDC(hWnd,"1.bmp");

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	SetTimer(hWnd,0,60,0);

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