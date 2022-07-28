#include <windows.h>
#include<vector>
#include<CString>
#include<iostream>

#include"resource.h"
using namespace std;

#define MAP_W 16
#define MAP_H 8
#define MAP_S MAP_W*MAP_H

#define _KD 0
#define _ZA 1

#define _NODIR 0
#define _LEFT_ 1
#define _RIGHT_ 2
#define _UP_ 3
#define _DOWN_ 4

int x=0,y=0;
//每个格子的宽高
int ew,eh;
//移动的方向
int dir = _NODIR;



char map[MAP_S]=
{
	0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,
	0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,
	1,0,0,1,0,0,0,1,1,1,0,0,1,1,0,1,
	1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,
	1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,
	1,1,1,1,1,1,0,0,1,0,1,1,1,0,0,1,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1

};
//横向每次触发计时器的偏移量
int x_py;
//纵向每次触发计时器的偏移量
int y_py;
//触发计时器的次数
int m_time = 0;

__w64 long __stdcall WindowProc(HWND hwnd,unsigned int uMsg,__w64 unsigned int wParam,__w64 long lParam)
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
			if(dir !=_NODIR)
			{
				return 0;
			}
			if(wParam==VK_DOWN)
			{
				if(y<MAP_H-1)
				{
					RECT r ={x*ew,(y+1)*eh,(x+1)*ew,(y+2)*eh};
					for(int i=0;i<MAP_S;i++)
					{
						if(map[i]==_ZA)
						{
							int x1 = i%MAP_W;
							int y1 = i/MAP_W;
							RECT r1;
							RECT r2 = {x1*ew,y1*eh,(x1+1)*ew,(y1+1)*eh};
							if(IntersectRect(&r1,&r,&r2))
							{
								return 0;
							}
						}
					}
					dir = _DOWN_;
				}
			}
			if(wParam==VK_UP)
			{
				if(y>0)
				{
					RECT r ={x*ew,(y-1)*eh,(x+1)*ew,y*eh};
					for(int i=0;i<MAP_S;i++)
					{
						if(map[i]==_ZA)
						{
							int x1 = i%MAP_W;
							int y1 = i/MAP_W;
							RECT r1;
							RECT r2 = {x1*ew,y1*eh,(x1+1)*ew,(y1+1)*eh};
							if(IntersectRect(&r1,&r,&r2))
							{
								return 0;
							}
						}
					}
					dir = _UP_;
				}
			}
			if(wParam==VK_LEFT)
			{
				if(x>0)
				{
					RECT r ={(x-1)*ew,y*eh,x*ew,(y+1)*eh};
					for(int i=0;i<MAP_S;i++)
					{
						if(map[i]==_ZA)
						{
							int x1 = i%MAP_W;
							int y1 = i/MAP_W;
							RECT r1;
							RECT r2 = {x1*ew,y1*eh,(x1+1)*ew,(y1+1)*eh};
							if(IntersectRect(&r1,&r,&r2))
							{
								return 0;
							}
						}
					}
					dir = _LEFT_;
				}
			}
			if(wParam==VK_RIGHT)
			{
				if(x<MAP_W-1)
				{
					RECT r ={(x+1)*ew,y*eh,(x+2)*ew,(y+1)*eh};
					for(int i=0;i<MAP_S;i++)
					{
						if(map[i]==_ZA)
						{
							int x1 = i%MAP_W;
							int y1 = i/MAP_W;
							RECT r1;
							RECT r2 = {x1*ew,y1*eh,(x1+1)*ew,(y1+1)*eh};
							if(IntersectRect(&r1,&r,&r2))
							{
								return 0;
							}
						}
					}
					dir = _RIGHT_;
				}
			}
			return 0;
		}
	
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc =BeginPaint(hwnd,&ps);
			for(int i=0;i<MAP_S;i++)
			{
				if(map[i]==_ZA)
				{
					int x1 = i%MAP_W;
					int y1 = i/MAP_W;
					Rectangle(hdc,x1*ew,y1*eh,(x1+1)*ew,(y1+1)*eh);
				}
			}
			switch(dir)
			{
			case _NODIR:
				{
					Ellipse(hdc,x*ew,y*eh,(x+1)*ew,(y+1)*eh);
					break;
				}
			case _LEFT_:
				{
					Ellipse(hdc,x*ew-x_py*m_time,y*eh,(x+1)*ew-x_py*m_time,(y+1)*eh);
					break;
				}
			case _RIGHT_:
				{
					Ellipse(hdc,x*ew+x_py*m_time,y*eh,(x+1)*ew+x_py*m_time,(y+1)*eh);
					break;
				}
			case _UP_:
				{
					Ellipse(hdc,x*ew,y*eh-y_py*m_time,(x+1)*ew,(y+1)*eh-y_py*m_time);
					break;
				}
			case _DOWN_:
				{
					Ellipse(hdc,x*ew,y*eh+y_py*m_time,(x+1)*ew,(y+1)*eh+y_py*m_time);
					break;
				}
			}
			if(m_time == 10)
			{
				switch(dir)
				{
				case _LEFT_:
					{
						x--;
						break;
					}
				case _RIGHT_:
					{
						x++;
						break;
					}
				case _UP_:
					{
						y--;
						break;
					}
				case _DOWN_:
					{
						y++;
						break;
					}
				}
				m_time = 0;
				dir = _NODIR;
			}
			/*char a[5];
			if(x<10)
			{
				a[0]=x+48;
				a[1]=' ';
				a[2]=y+48;
				TextOutA(hdc,x*ew,y*eh,a,3);
			}else
			{
				a[0]=1+48;
				a[1]=x-10+48;
				a[2]=' ';
				a[3]=y+48;
				TextOutA(hdc,x*ew,y*eh,a,4);
			}*/
			
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_TIMER:
		{
			if(dir!=_NODIR)
			{
				m_time++;
				InvalidateRect(hwnd,0,TRUE);
			}
			return 0;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == 0)
			{
				switch(LOWORD(wParam))
				{
				case ID_40001:
					{
						FILE* pf =0;
						fopen_s(&pf,"存档.txt","wb");
						fwrite(&x,1,sizeof(int),pf);
						fwrite(&y,1,sizeof(int),pf);
						fclose(pf);
						MessageBoxA(hwnd,"存档成功！",0,MB_OK);
						break;
					}
				case ID_40002:
					{
						FILE* pf = 0;
						fopen_s(&pf,"存档.txt","rb");
						fread(&x,1,4,pf);
						fread(&y,1,4,pf);
						fclose(pf);
						MessageBoxA(hwnd,"读档成功！",0,MB_OK);
						InvalidateRect(hwnd,0,TRUE);
						break;
					}
				case ID_40003:
					{
						if(IDYES==MessageBoxA(hwnd,"真的要退出游戏吗",0,MB_YESNO))
						{
							DestroyWindow(hwnd);
						}
						break;
					}
				}
			}
			return 0;
		}
	}
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
	wc.hIcon =LoadIcon(0,IDI_APPLICATION);
	wc.hCursor =LoadCursor(0,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName =L"八班";
	RegisterClass(&wc);
	HWND hWnd = CreateWindow(wc.lpszClassName,
							L"绘制线段",
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							HWND_DESKTOP,
							0,
							wc.hInstance,
							0);
	RECT r ;
	GetClientRect(hWnd,&r);
	ew = (r.right-r.left)/MAP_W;
	eh = (r.bottom-r.top)/MAP_H;
	x_py = ew/10;
	y_py = eh/10;
	SetTimer(hWnd,0,40,0);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	
	

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	KillTimer(hWnd,0);
	return 1;
}