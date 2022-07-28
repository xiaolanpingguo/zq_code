//#include <windows.h>
//#include <vector>
//
//#define _MAP_W 800
//#define _MAP_H 640
////地图上能画多少个
//#define _MAP_W_W 10
//#define _MAP_W_H 8
////地图数组
//char map[]=
//{
//	0,1,1,1,1,1,1,1,1,0,
//	0,0,0,1,0,0,0,1,1,0,
//	0,1,0,1,1,1,0,1,1,0,
//	0,1,0,0,0,0,0,1,1,0,
//	0,1,1,1,0,0,0,1,1,0,
//	0,1,1,1,0,0,0,1,1,0,
//	0,1,1,1,0,0,0,1,1,0,
//	0,1,1,1,1,1,1,1,1,0
//};
////每一个矩形范围的像素宽和高
//int ew,eh;
////记录所有的矩形
//std::vector<RECT> g_vRect;
//
////英雄的矩形
//RECT ellRect;
//
////英雄坐标
//int x,y;
//
////窗口消息函数，本函数将被操作系统调用
//__w64 long __stdcall WindowProc(HWND hwnd,//产生消息的窗口
//								unsigned int uMsg,//消息类型
//								__w64 unsigned int wParam,//消息附加参数1
//								__w64 long lParam)//消息附加参数2
//{
//	switch(uMsg)
//	{
//	case WM_DESTROY:
//		{
//			PostQuitMessage(0);
//			return 0;
//		}
//	case WM_KEYDOWN:
//		{
//			int lx = x;
//			int ly = y;
//			if(wParam == VK_UP)
//			{
//				if(y > 0)
//					y--;
//			}
//			if(wParam == VK_DOWN)
//			{
//				if(y < _MAP_W_H - 1)
//					y++;
//			}
//			if(wParam == VK_LEFT)
//			{
//				if(x > 0)
//					x--;
//			}
//			if(wParam == VK_RIGHT)
//			{
//				if(x < _MAP_W_W - 1)
//					x++;
//			}
//
//			RECT lsr = 
//			{
//				ew * x,
//				eh * y,
//				ew * x + ew,
//				eh * y + eh
//			};
//
//			RECT returnR;
//			for(std::vector<RECT>::iterator i = g_vRect.begin(); i != g_vRect.end();++i)
//			{
//				if(IntersectRect(&returnR,&(*i),&lsr) == TRUE)
//				{
//					x = lx;
//					y = ly;
//					return 0;
//				}
//			}
//
//			ellRect.left = ew * x;
//			ellRect.top = eh * y;
//			ellRect.right = ew * x + ew;
//			ellRect.bottom = eh * y + eh;
//
//			InvalidateRect(hwnd,0,TRUE);
//			return 0;
//		}
//		//InvalidateRect,InvalidateRgn函数
//	//case WM_LBUTTONDOWN:
//	//	{
//	//		POINT p = {LOWORD(lParam),HIWORD(lParam)};
//	//		
//	//			if(IntersectRect(&lr,&(*i),&r) == TRUE)
//
//
//	//		InvalidateRect(hwnd,//窗口句柄
//	//			          0,//区域的矩形地址，为0表示整个客户区
//	//					  TRUE);//是否让操作系统绘制窗口背景色
//	//						//(如果是，则WM_PAINT消息中的绘制会在系统用白色填充
//	//		               //整个客户区之后，如果否，则WM_PAINT消息之前操作系统
//	//						//不会用白色填充客户区)
//	//		return 0;
//	//	}
//	case WM_PAINT:
//		{
//			PAINTSTRUCT ps;
//			HDC hdc = BeginPaint(hwnd,&ps);
//
//			for(std::vector<RECT>::iterator i = g_vRect.begin(); i != g_vRect.end();++i)
//			{
//				Rectangle(hdc,i->left,i->top,i->right,i->bottom);
//			}
//
//			Ellipse(hdc,ellRect.left,ellRect.top,ellRect.right,ellRect.bottom);
//			char buf[32];
//			sprintf_s(buf,32,"%d,%d",x,y);
//			TextOutA(hdc,ellRect.left,ellRect.top,buf,(int)strlen(buf));
//			EndPaint(hwnd,&ps);
//
//			return 0;
//		}
//	}
//	return DefWindowProc(hwnd,uMsg,wParam,lParam);
//}
//
//int __stdcall WinMain(HINSTANCE hInstance,//应用程序实例句柄
//					  HINSTANCE hPrevInstance,
//					  LPSTR lpCmdLine,
//					  int nCmdShow)
//{
//	WNDCLASS wc;
//	wc.style = CS_HREDRAW|CS_VREDRAW;
//	wc.lpfnWndProc = WindowProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hInstance = hInstance;
//	
//	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
//	
//	wc.hCursor = LoadCursor(0,IDC_ARROW);
//	
//	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
//	
//	wc.lpszMenuName = 0;
//	
//	wc.lpszClassName = L"八班";
//	
//	RegisterClass(&wc);
//
//	int sw = GetSystemMetrics(SM_CXSCREEN);
//	int sh = GetSystemMetrics(SM_CYSCREEN);
//
//	RECT wr =
//	{
//		(sw - _MAP_W) / 2,
//		(sh - _MAP_H) / 2,
//		(sw - _MAP_W) / 2 + _MAP_W,
//		(sh - _MAP_H) / 2 + _MAP_H
//	};
//	
//	AdjustWindowRect(&wr,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,FALSE	);
//
//	HWND hWnd = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
//		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
//							 //帮助完成创建窗口的任务
//							 L"简单移动及碰撞",//窗口标题栏文字
//							 WS_OVERLAPPEDWINDOW,//窗口风格
//							 wr.left,//窗口的左上角x坐标
//							 wr.top,//窗口的左上角y坐标
//							 wr.right - wr.left,//窗口的宽（像素）
//							 wr.bottom - wr.top,//窗口的高（像素）
//							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
//							 0,//窗口菜单句柄，不使用菜单填0
//							 wc.hInstance,//应用程序实例句柄
//							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0
//
//	RECT clientR;
//	GetClientRect(hWnd,&clientR);
//	int cw = clientR.right - clientR.left;
//	int ch = clientR.bottom - clientR.top;
//
//	ew = cw / _MAP_W_W;
//	eh = ch / _MAP_W_H;
//
//	bool setHero = false;
//	
//	for(int i = 0;i < _MAP_W_H;++i)
//	{
//		for(int j = 0; j < _MAP_W_W;++j)
//		{
//			if(map[j + i * _MAP_W_W] == 1)
//			{
//				RECT jx = 
//				{
//					ew * j,
//					eh * i,
//					ew * j + ew,
//					eh * i + eh
//				};
//				g_vRect.push_back(jx);
//			}
//			else if(!setHero && map[j + i * _MAP_W_W] == 0)
//			{
//				setHero = true;
//				ellRect.left = ew * j;
//				ellRect.top = eh * i;
//				ellRect.right = ew * j + ew;
//				ellRect.bottom = eh * i + eh;
//				x = j;
//				y = i;
//			}
//		}
//	}
//
//
//	ShowWindow(hWnd,nCmdShow);
//	UpdateWindow(hWnd);
//	
//	MSG msg;
//	while(GetMessage(&msg,0,0,0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//
//	return 1;
//}

#include <windows.h>
#include <vector>

#define _MAP_W 10
#define _MAP_H 8
#define _GRID_W 50
#define _GRID_H 60
#define _CLIENT_W (_MAP_W * _GRID_W)
#define _CLIENT_H (_MAP_H * _GRID_H)
int x, y;
char map[]=
{
	1,1,0,1,1,1,1,1,1,1,
	1,1,0,0,1,1,1,1,1,1,
	1,1,1,0,1,1,1,1,1,1,
	1,1,1,0,1,0,0,1,1,1,
	1,1,1,1,1,1,0,0,0,1,
	1,1,1,1,1,1,1,1,0,1,
	1,1,0,0,1,1,1,0,1,1,
	1,1,0,1,1,1,1,1,1,1
};

__w64 long __stdcall WindowProc(HWND hwnd,
								unsigned int uMsg,
								__w64 unsigned int wParam,
								__w64 long lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_KEYDOWN:
		{
			bool ok = true;

			switch (wParam)
			{
			case VK_UP:
				{
					if (y > 0 && map[x + (y - 1) * _MAP_W] == 1)
						--y;
					break;
				}
			case VK_DOWN:
				{
					if (y < _MAP_H - 1 && map[x + (y + 1) * _MAP_W] == 1)
						++y;
					break;
				}
			case VK_LEFT:
				{
					if (x > 0 && map[x - 1 + y * _MAP_W] == 1)
						--x;
					break;
				}
			case VK_RIGHT:
				{
					if (x < _MAP_W - 1 && map[x + 1 + y * _MAP_W] == 1)
						++x;
					break;
				}
			default:
				{
					ok = false;
				}
			}
			if (ok)
				InvalidateRect(hwnd, 0, TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			for (int i = 0; i < _MAP_W * _MAP_H; ++i)
			{
				int cx = i % _MAP_W;
				int cy = i / _MAP_W;
				if (0 == map[cx + cy * _MAP_W])
					Rectangle(hdc, cx * _GRID_W, cy * _GRID_H, (cx + 1) * _GRID_W, (cy + 1) * _GRID_H);
			}
			Ellipse(hdc, x * _GRID_W, y * _GRID_H, (x + 1) * _GRID_W, (y + 1) * _GRID_H);
			char buf[32];
			sprintf_s(buf, 32, "%d-%d", x, y);
			TextOutA(hdc, x * _GRID_W, y * _GRID_H, buf, (int)strlen(buf));
			
			EndPaint(hwnd, &ps);
			return 0;
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"六三";

	RegisterClass(&wc);
	HWND hWnd = CreateWindow(
				wc.lpszClassName,
				L"简单移动及碰撞",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				HWND_DESKTOP,
				0,
				wc.hInstance,
				0);
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}