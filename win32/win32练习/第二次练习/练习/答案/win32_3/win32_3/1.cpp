#include <windows.h>
#include<vector>
#include<CString>
using namespace std;

#define MAP_W 16
#define MAP_H 8
#define MAP_S MAP_W*MAP_H

#define _KD 0
#define _ZA 1

int x=0,y=0;
int ew,eh; 
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
					y++;
					InvalidateRect(hwnd,0,TRUE);
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
					y--;
					InvalidateRect(hwnd,0,TRUE);
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
					x--;
					InvalidateRect(hwnd,0,TRUE);
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
					x++;
					InvalidateRect(hwnd,0,TRUE);
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
			Ellipse(hdc,x*ew,y*eh,(x+1)*ew,(y+1)*eh);
			char a[5];
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
			}
			
			EndPaint(hwnd,&ps);
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
	wc.lpszMenuName = 0;
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
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	
	

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 1;
}