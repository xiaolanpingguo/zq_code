#include <windows.h>
#include<vector>
using namespace std;

vector<RECT> g_vRect;

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
			RECT r ={p.x-50,p.y-30,p.x+50,p.y+3};
			RECT r1;
			if(g_vRect.size()>0)
			{
				for(vector<RECT>::iterator riter = g_vRect.begin();riter!=g_vRect.end();riter++)
				{
					RECT r2 ={riter->left,riter->top,riter->right,riter->bottom};
					if(IntersectRect(&r1,
									&r,
									&r2))
					{
						MessageBoxA(hwnd,"已和之前的矩形重合","提示",MB_OK);
						return 0;
					}
				}
			}
			g_vRect.push_back(r);
			InvalidateRect(hwnd,
							0,
							TRUE);
			return 0;
		}
	
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc =BeginPaint(hwnd,&ps);
			for(vector<RECT>::iterator riter= g_vRect.begin();riter!=g_vRect.end();riter++)
			{
				Rectangle(hdc,riter->left,riter->top,riter->right,riter->bottom);
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