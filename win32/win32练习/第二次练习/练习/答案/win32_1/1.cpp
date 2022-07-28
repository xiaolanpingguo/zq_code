#include <windows.h>
#include<vector>
using namespace std;

vector<POINT> g_vPoint;

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
			POINT p = {LOWORD(lParam),HIWORD(lParam)};
			g_vPoint.push_back(p);
			InvalidateRect(hwnd,
							0,
							TRUE);
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			if(g_vPoint.size()>0)
			{
				g_vPoint.pop_back();
				InvalidateRect(hwnd,0,TRUE);
			}
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc =BeginPaint(hwnd,&ps);
			if(g_vPoint.size()>=2)
			{
				
				for(vector<POINT>::iterator piter= g_vPoint.begin();piter!=g_vPoint.end()-1;piter++)
				{
					POINT p;
					MoveToEx(hdc,piter->x,piter->y,&p);
					LineTo(hdc,(piter+1)->x,(piter+1)->y);
				}
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