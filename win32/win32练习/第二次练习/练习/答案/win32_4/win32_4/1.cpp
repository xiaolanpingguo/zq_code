#include <windows.h>
#include<vector>
using namespace std;

char s[64];
int len =0;
int flag =0;

__w64 long __stdcall WindowProc(HWND hwnd,unsigned int uMsg,__w64 unsigned int wParam,__w64 long lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	/*case WM_KEYDOWN:
		{
			if(wParam == VK_BACK)
			{
				if(len>0)
				{
					len--;
					InvalidateRect(hwnd,
							0,
							TRUE);
				}
			}
		}*/
	case WM_CHAR:
		{
			if(wParam==VK_RETURN)
			{
				return 0;
			}
			if(wParam==VK_BACK)
			{
				if(len>0)
				{
					if(s[len-1]<0||s[len-1]>128)
					{
						len-=2;
					}else
						len--;
					InvalidateRect(hwnd,
							0,
							TRUE);
				}
				return 0;
			}
			if(len==63)
			{
				MessageBoxA(hwnd,"不能超过63个字符","提示",MB_OK);
				return 0;
			}
			if(wParam<0||wParam>128)
			{
				if(len==62)
				{
					if(flag%2==0)
						MessageBoxA(hwnd,"不能超过63个字符","提示",MB_OK);
					flag++;
					return 0;
				}
			}
			s[len++] = (char)wParam;
			s[len]=0;
			
			InvalidateRect(hwnd,
							0,
							TRUE);
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc =BeginPaint(hwnd,&ps);
			TextOutA(hdc,0,0,s,len);
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
	wc.lpszClassName ="八班";
	RegisterClass(&wc);
	HWND hWnd = CreateWindow(wc.lpszClassName,
							"绘制线段",
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