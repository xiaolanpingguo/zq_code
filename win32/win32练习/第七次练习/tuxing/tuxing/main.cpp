#include <windows.h>
#include"resource.h"
#include<vector>

#define _JX 1
#define _YX 2

HWND g_hwnd[3];
int flag = _JX;

std::vector<POINT> g_vPoint;
std::vector<int> g_vInt;

INT_PTR __stdcall f(HWND hwndDlg,
					UINT uMsg,
					WPARAM wParam,
					LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CLOSE:
		{
			ShowWindow(hwndDlg,SW_HIDE);
			return 1;
		}
	case WM_INITDIALOG:
		{
			char buf[256] = "请选择";
			SetWindowTextA(hwndDlg,buf);
			return 1;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
			{
				if(LOWORD(wParam) == IDOK)
				{
					flag =_JX;
				}
				else 
				{
					flag =_YX;
				}
			}
			return 1;
		}
	}
	return 0;
}


__w64 long __stdcall WindowProc(HWND hwnd,unsigned int uMsg,__w64 unsigned int wParam,__w64 long lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc =BeginPaint(hwnd,&ps);
			std::vector<int>::iterator a =g_vInt.begin();
			for(std::vector<POINT>::iterator i = g_vPoint.begin();i!=g_vPoint.end();i++,a++)
			{
				if((*a)==_JX)
				{
					Rectangle(hdc,i->x-30,i->y-15,i->x+30,i->y+15);
				}else
				{
					Ellipse(hdc,i->x-30,i->y-15,i->x+30,i->y+15);
				}
			}
			
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			POINT p = {LOWORD(lParam),HIWORD(lParam)};
			g_vPoint.push_back(p);
			g_vInt.push_back(flag);
			InvalidateRect(hwnd,0,TRUE);
			return 0;
			
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam)==BN_CLICKED)
			{
				if(LOWORD(wParam)==1)
				{
					g_hwnd[2]= CreateDialog(GetModuleHandle(0),
											MAKEINTRESOURCE(IDD_DIALOG1),
											g_hwnd[0],
											f);
					MoveWindow(g_hwnd[2],300,200,400,300,TRUE);
					ShowWindow(g_hwnd[2],SW_SHOW);
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
	wc.lpszMenuName = 0;
	wc.lpszClassName =L"八班";
	RegisterClass(&wc);
	g_hwnd[0] = CreateWindow(wc.lpszClassName,
							L"非模式对话框",
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							816,
							458,
							HWND_DESKTOP,
							0,
							wc.hInstance,
							0);
	g_hwnd[1] = CreateWindow(L"button",
							L"图形选择",
							WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
							0,
							0,
							100,
							30,
							g_hwnd[0],
							(HMENU)1,
							wc.hInstance,
							0);
	
	ShowWindow(g_hwnd[0],nCmdShow);
	UpdateWindow(g_hwnd[0]);
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 1;
	
	
}