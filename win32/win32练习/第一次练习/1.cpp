#include<windows.h>

__w64 long __stdcall  WindowProc(HWND hwnd,
							   unsigned int uMsg,
							   __w64 unsigned int wParam,
							   __w64 long lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_KEYDOWN :
		{
			if(wParam ==VK_RIGHT)
			{
				RECT r;
				GetWindowRect(hwnd,&r);
				int x = GetSystemMetrics(SM_CXSCREEN)/6;
				if(r.right<x*6)
				{
					r.left=r.left+x;
					r.right=r.right+x;
				}
				MoveWindow(hwnd,r.left,r.top,r.right-r.left,r.bottom-r.top,true);
			}
			if(wParam ==VK_LEFT)
			{
				RECT r;
				GetWindowRect(hwnd,&r);
				int x = GetSystemMetrics(SM_CXSCREEN)/6;
				if(r.left>0)
				{
					r.left=r.left-x;
					r.right=r.right-x;
				}
				MoveWindow(hwnd,r.left,r.top,r.right-r.left,r.bottom-r.top,true);
			}
			if(wParam ==VK_UP)
			{
				RECT r;
				GetWindowRect(hwnd,&r);
				int x = GetSystemMetrics(SM_CYSCREEN)/4;
				if(r.top>0)
				{
					r.top=r.top-x;
					r.bottom=r.bottom-x;
				}
				MoveWindow(hwnd,r.left,r.top,r.right-r.left,r.bottom-r.top,true);
			}
			if(wParam ==VK_DOWN)
			{
				RECT r;
				GetWindowRect(hwnd,&r);
				int x = GetSystemMetrics(SM_CYSCREEN)/4;
				if(r.bottom<x*4)
				{
					r.top=r.top+x;
					r.bottom=r.bottom+x;
				}
				MoveWindow(hwnd,r.left,r.top,r.right-r.left,r.bottom-r.top,true);
			}
			
			return 0;
		}
	}

	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	WNDCLASS  wc;
	wc.style= CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName =L"°Ë°à";
	wc.lpszMenuName = 0;
	
	RegisterClass(&wc);
	HWND hWnd =CreateWindow(wc.lpszClassName,
							L"ËÆÄ§¹íµÄ²½·¥",
							WS_OVERLAPPEDWINDOW &~WS_THICKFRAME ,
							0,
							0,
							GetSystemMetrics(SM_CXSCREEN)/6,
							GetSystemMetrics(SM_CYSCREEN)/4,
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
								