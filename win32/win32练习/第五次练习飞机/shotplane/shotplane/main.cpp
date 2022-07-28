#include <windows.h>
#include"resource.h"
#include"mplane.h"
#include<vector>
#include "eplane.h"
#include"GameOutput.h"
#include"GameLogic.h"
#include"GameInput.h"
#include"mBullet.h"
#include"eBullet.h"

#include<time.h>

#define WINDOW_W 450
#define WINDOW_H 650

//存储敌方飞机的容器
extern std::vector<CEplane> g_vEplane;
std::vector<CEplane> g_vEplane;
//我方飞机变量
extern CMplane g_mplane;
CMplane g_mplane;
//存储我方子弹的容器
extern std::vector<CMbullet> g_vMbullet;
std::vector<CMbullet> g_vMbullet;
//存储敌方子弹的容器
extern std::vector<CEbullet> g_vEbullet;
std::vector<CEbullet> g_vEbullet;

CGameOutput gameOutput;
extern CGameLogic gameLogic;
CGameLogic gameLogic;
CGameInput gameInput;




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
			
			return 0;
		}
	
	case WM_PAINT:
		{
			gameOutput.pm(hwnd);
			gameLogic.isOut(hwnd);
			gameLogic.isTouch();
			gameLogic.isDeath(hwnd);
			return 0;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam)==0)
			{
				switch(LOWORD(wParam))
				{
				case ID_40001:
					{
						DestroyWindow(hwnd);
						break;
					}
				case ID_40002:
					{
						SetTimer(hwnd,0,70,0);
						gameLogic.setSpeed(SLOW);
						break;
					}
				case ID_40003:
					{
						SetTimer(hwnd,0,50,0);
						gameLogic.setSpeed(MID);
						break;
					}
				case ID_40004:
					{
						SetTimer(hwnd,0,30,0);
						gameLogic.setSpeed(QUICK);
						break;
					}
				}
			}
			return 0;
		}
	case WM_TIMER:
		{
			gameInput.run(hwnd);
			gameLogic.addPlane();
			gameLogic.run();
			gameLogic.addBullet();
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			gameInput.addMbullet();
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			gameInput.boom();
			InvalidateRect(hwnd,0,TRUE);
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
	srand((unsigned int)time(0));
	WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon =LoadIcon(0,IDI_APPLICATION);
	wc.hCursor =LoadCursor(0,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName =MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName =L"八班";
	RegisterClass(&wc);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	RECT r =
	{
		(sw- WINDOW_W)/2,
		(sh- WINDOW_H)/2,
		(sw- WINDOW_W)/2 + WINDOW_W,
		(sh- WINDOW_H)/2 + WINDOW_H
	};
	HWND hWnd = CreateWindow(wc.lpszClassName,
							L"shot plane",
							WS_OVERLAPPEDWINDOW,
							r.left,
							r.top,
							WINDOW_W,
							WINDOW_H,
							HWND_DESKTOP,
							0,
							wc.hInstance,
							0);
	//中速
	SetTimer(hWnd,0,50,0);
	////快速
	//SetTimer(hWnd,QUICK,30,0);
	////慢速
	//SetTimer(hWnd,SLOW,70,0);
	
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