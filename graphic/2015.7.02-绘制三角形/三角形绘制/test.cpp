#include <windows.h>
#include <vector>
#include <time.h>

#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

BOOL g_Act = TRUE;//窗口激活标志
HDC g_MainDC;
HDC g_BackDC;

void DrawTriangle(int x0, int y0,
				  int x1, int y1,
				  int x2, int y2,
				  COLORREF color);

void GameInit(HWND hwnd)
{
	g_MainDC = GetDC(hwnd);
	g_BackDC = CreateCompatibleDC(g_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_MainDC, _CLIENT_W, _CLIENT_H);
	DeleteObject(SelectObject(g_BackDC,hbmp));
	DeleteObject(hbmp);

	srand(time(0));
}

void GameRun(HWND hwnd)
{
	BitBlt(g_BackDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	DrawTriangle(100, 100, 300, 300, 200, 100, RGB(255, 0, 0));

	BitBlt(g_MainDC, 0, 0, _CLIENT_W, _CLIENT_H, g_BackDC, 0, 0, SRCCOPY);
}

void GameEnd(HWND hwnd)
{
	DeleteDC(g_BackDC);
	ReleaseDC(hwnd, g_MainDC); 
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
	case WM_ACTIVATEAPP:
		{
			g_Act = (BOOL)wParam;
			return 0;
		}
	}
	//我们不关心的消息就调用DefWindowProc(windows对所有消息的默认处理函数)来帮助我们处理
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//应用程序实例句柄
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	//01)填充一个窗口类别的结构体
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "3dtest";
	RegisterClass(&wc);

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	RECT r = 
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		(sw - _CLIENT_W) / 2 + _CLIENT_W,
		(sh - _CLIENT_H) / 2 + _CLIENT_H
	};

	//得到窗口风格
	//已知字节????????和风格00001000
	//那么(字节&~风格)就为
	//????????
	//11110111
	//--------
	//????0???
	int ws = (WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME) & ~WS_MAXIMIZEBOX;

	AdjustWindowRect(&r, ws, FALSE);

	HWND hWnd = CreateWindow(
		wc.lpszClassName,
		"矩阵测试",//窗口标题栏文字
		ws,//窗口风格
		r.left,//窗口的左上角x坐标
		r.top,//窗口的左上角y坐标
		r.right - r.left,//窗口的宽（像素）
		r.bottom - r.top,//窗口的高（像素）
		HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
		0,//窗口菜单句柄，不使用菜单填0
		wc.hInstance,//应用程序实例句柄
		0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	GameInit(hWnd);

	MSG msg = {};
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(g_Act)
		{
			int bt = GetTickCount();
			GameRun(hWnd);
			int at = GetTickCount() - bt;
			Sleep(at < _SLEEP_TIME ? _SLEEP_TIME - at : 1);
		}
		else
			WaitMessage();
	}

	GameEnd(hWnd);

	return 1;
}

void DrawTriangle_FlatBottom(int x0, int y0,
							 int x1, int y1,
							 int x2, int y2,
							 COLORREF color)
{
	//   (x0,y0)
	//(x1,y1)(x2,y2)
	//直线公式中的斜率k，其表示的意思就是x每递
	//增一个单位y的变化量，1/k则表示y每递增一个
	//单位x的变化量

	//求得左右两条直线的梯度变化值(y递增方向)
	float left_grads = (float)(x0 - x1) / (y0 - y1);
	float right_grads = (float)(x0 - x2) / (y0 - y2);
	
	//得到线段的左右x值
	float left_x = x0;
	float right_x = x0;

	//循环绘制
	for (int y = y0; y <= y1; ++y)
	{
		//得到当前线段左右x的整数值
		int left_int_x = (int)left_x;
		int right_int_x = (int)right_x;

		//绘制当前线段
		for (int x = left_int_x; x <= right_int_x; ++x)
			SetPixel(g_BackDC, x, y, color);

		left_x += left_grads;
		right_x += right_grads;
	}
}

void DrawTriangle_FlatTop(int x0, int y0,
						  int x1, int y1,
						  int x2, int y2,
						  COLORREF color)
{
	//(x1,y1)(x2,y2)
	//   (x0,y0)

	//求得左右两条直线的梯度变化值(y递减方向)
	float left_grads = (float)(x1 - x0) / (y0 - y1);
	float right_grads = (float)(x2 - x0) / (y0 - y2);
	
	//得到线段的左右x值
	float left_x = x0;
	float right_x = x0;

	//循环绘制
	for (int y = y0; y >= y1; --y)
	{
		//得到当前线段左右x的整数值
		int left_int_x = (int)left_x;
		int right_int_x = (int)right_x;

		//绘制当前线段
		for (int x = left_int_x; x <= right_int_x; ++x)
		{
			SetPixel(g_MainDC, x, y, color);
			//Sleep(1);
		}

		left_x += left_grads;
		right_x += right_grads;
	}
}

void DrawTriangle(int x0, int y0,
				  int x1, int y1,
				  int x2, int y2,
				  COLORREF color)
{
	//三点相同的判断
	if (x0 == x1 && x1 == x2 && y0 == y1 && y1 == y2)
		return;

	//三点共线的判断
	if ((y0 - y1) * (x1 - x2) == (y1 - y2) * (x0 - x1))
		return;

	//三点的y值都不相同
	if (y0 != y1 && y1 != y2 && y0 != y2)
	{
		//拆分三角形
	}
	//三点中的2个点的y值相同
	else
	{
		//让cx0、cy0得到单独的那个点的坐标
		//让cx1、cy1、cx2、cy2得到y值相等的那两个点的坐标，且cx1在cx2左侧
		//经过处理我们一定得到下面的情况
		//			(cx0、cy0)
		//(cx1、cy1)		(cx2、cy2)
		//或
		//(cx1、cy1)		(cx2、cy2)
		//			(cx0、cy0)
		int cx0, cx1, cx2, cy0, cy1, cy2;

		if (y1 == y2)
		{
			cx0 = x0; cy0 = y0;
			if (x1 < x2)
			{
				cx1 = x1; cy1 = y1;
				cx2 = x2; cy2 = y2;
			}
			else
			{
				cx1 = x2; cy1 = y2;
				cx2 = x1; cy2 = y1;
			}
		}
		else if (y0 == y1)
		{
			cx0 = x2; cy0 = y2;
			if (x0 < x1)
			{
				cx1 = x0; cy1 = y0;
				cx2 = x1; cy2 = y1;
			}
			else
			{
				cx1 = x1; cy1 = y1;
				cx2 = x0; cy2 = y0;
			}
		}
		else
		{
			cx0 = x1; cy0 = y1;
			if (x0 < x2)
			{
				cx1 = x0; cy1 = y0;
				cx2 = x2; cy2 = y2;
			}
			else
			{
				cx1 = x2; cy1 = y2;
				cx2 = x0; cy2 = y0;
			}
		}

		//平底三角形
		if (cy0 < cy1)
		{
			DrawTriangle_FlatBottom(
				cx0, cy0,
				cx1, cy1,
				cx2, cy2,
				color);
		}
		//平顶三角形
		else
		{
			DrawTriangle_FlatTop(
				cx0, cy0,
				cx1, cy1,
				cx2, cy2,
				color);
		}
	}
}

