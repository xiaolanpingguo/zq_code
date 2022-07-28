#include <windows.h>
#include"wzq.h"
#include"map.h"

#define CLIENT_W 400
#define CLIENT_H 460

CWzq wzq;
CMap map;
int QZ_size;//棋子的大小
int x,y;//点击鼠标所代表的棋盘坐标


__w64 long __stdcall WindowProc(HWND hwnd,unsigned int uMsg,__w64 unsigned int wParam,__w64 long lParam)
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
			POINT p ={LOWORD(lParam),HIWORD(lParam)};
			if(p.y<30||p.y>30+MAP_H*QZ_size)
				return 0;
			x=p.x/QZ_size;
			y=(p.y-30)/QZ_size;
			if(map.GetMap(x+y*MAP_W)==_KD)
			{
				if(map.GetCp()->GetPc()%2==0)
				{
					map.SetMap(x+y*MAP_W,_HQ);
					map.GetCp()->SetPc(map.GetCp()->GetPc()+1);
				}else
				{
					map.SetMap(x+y*MAP_W,_BQ);
					map.GetCp()->SetPc(map.GetCp()->GetPc()+1);
				}
			}else
			{
				MessageBoxA(hwnd,"不能在有子的地方落子","提示",MB_OK);
				return 0;
			}
			InvalidateRect(hwnd,0,TRUE);
			return 0;
			
		}
	case WM_PAINT:
		{
			RECT r;
			GetClientRect(hwnd,&r);
			PAINTSTRUCT ps;
			HDC hdc =BeginPaint(hwnd,&ps);
			if(wzq.GetPc()%2==0)
			{
				TextOutA(hdc,0,0,"请黑棋落子",10);
			}else
				TextOutA(hdc,0,0,"请白棋落子",10);
			int cw = r.right-r.left;
			int ch = r.bottom-r.top;
			//每个棋子的大小
			QZ_size = cw/MAP_W;
			//绘制棋盘
			for(int i=0;i<MAP_H;i++)
			{
				POINT p;
				MoveToEx(hdc,0+QZ_size/2,30+QZ_size/2+i*QZ_size,&p);
				LineTo(hdc,0+QZ_size/2+(MAP_W-1)*QZ_size,30+QZ_size/2+i*QZ_size);
			}
			for(int i=0;i<MAP_W;i++)
			{
				POINT p;
				MoveToEx(hdc,0+QZ_size/2+i*QZ_size,30+QZ_size/2,&p);
				LineTo(hdc,0+QZ_size/2+i*QZ_size,30+QZ_size/2+(MAP_W-1)*QZ_size);
			}
			for(int i=0;i<MAP_S;i++)
			{
				int x1 =i%MAP_W;
				int y1 =i/MAP_W;
				if(map.GetMap(i)==_BQ)
				{
					Ellipse(hdc,0+x1*QZ_size,30+y1*QZ_size,0+x1*QZ_size+QZ_size,30+y1*QZ_size+QZ_size);
				}else
				if(map.GetMap(i)==_HQ)
				{
					for(int i=0;i<QZ_size/2;i++)
					{
						Ellipse(hdc,0+x1*QZ_size+i,30+y1*QZ_size+i,0+x1*QZ_size+QZ_size-i,30+y1*QZ_size+QZ_size-i);
					}
				}
			}
			int flag=0;
			flag = wzq.run(map.GetMapdz(),x,y);
			if(flag==1)
			{
				MessageBoxA(hwnd,"黑方获胜!","提示",MB_OK);
				map.CleanMap();
				wzq.SetPc(0);
				InvalidateRect(hwnd,0,TRUE);
			}else
			if(flag==2)
			{
				MessageBoxA(hwnd,"白方获胜!","提示",MB_OK);
				map.CleanMap();
				wzq.SetPc(0);
				InvalidateRect(hwnd,0,TRUE);
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
	
	int sw=GetSystemMetrics(SM_CXSCREEN);
	int sh=GetSystemMetrics(SM_CYSCREEN);

	map.SetCp(&wzq);
	/*wzq.SetCp(&map);*/
	
	RECT r = {
		(sw-CLIENT_W)/2,
		(sh-CLIENT_H)/2,
		(sw-CLIENT_W)/2+CLIENT_W,
		(sh-CLIENT_H)/2+CLIENT_H
	};
	HWND hWnd = CreateWindow(wc.lpszClassName,
							L"五子棋",
							WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX&~WS_THICKFRAME,
							r.left,
							r.top,
							CLIENT_W,
							CLIENT_H,
							HWND_DESKTOP,
							0,
							wc.hInstance,
							0);

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