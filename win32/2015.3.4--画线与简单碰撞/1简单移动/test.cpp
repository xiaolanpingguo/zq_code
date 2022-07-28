#include <windows.h>

#define _MAP_W 10
#define _MAP_H 4

int ww,wh;
int x,y;

//HWND g_hWnd;

void UpdateWindowPos(HWND hwnd)
{
	MoveWindow(hwnd,x * ww,y * wh,ww,wh,TRUE);
}

//窗口消息函数，本函数将被操作系统调用
__w64 long __stdcall WindowProc(HWND hwnd,//产生消息的窗口
								unsigned int uMsg,//消息类型
								__w64 unsigned int wParam,//消息附加参数1
								__w64 long lParam)//消息附加参数2
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
			switch(wParam)
			{
			case VK_UP:
				{
					if(y > 0)
						y--;
					break;
				}
			case VK_DOWN:
				{
					if(y < _MAP_H - 1)
						y++;
					break;
				}
			case VK_LEFT:
				{
					if(x > 0)
						x--;
					break;
				}
			case VK_RIGHT:
				{
					if(x < _MAP_W - 1)
						x++;
					break;
				}
			}
			UpdateWindowPos(hwnd);
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
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"八班";
	RegisterClass(&wc);
	
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	ww = sw / _MAP_W;
	wh = sh / _MAP_H;
	x = y = 0;

	HWND hWnd = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 L"简单移动",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 0,//窗口的左上角x坐标
							 0,//窗口的左上角y坐标
							 200,//窗口的宽（像素）
							 200,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

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