#include <windows.h>
#include <vector>
#include <time.h>

#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 200

BOOL g_Act = TRUE;//窗口激活标志
HDC g_MainDC;
HDC g_BackDC;
HDC g_BmpDC;

void DrawTriangleLine(int x0, int y0,
					  int x1, int y1,
					  int x2, int y2)
{
	MoveToEx(g_BackDC, x0, y0, 0);
	LineTo(g_BackDC, x1, y1);
	MoveToEx(g_BackDC, x1, y1, 0);
	LineTo(g_BackDC, x2, y2);
	MoveToEx(g_BackDC, x2, y2, 0);
	LineTo(g_BackDC, x0, y0);
}

void DrawTriangleTexture_FlatBottom(int x0, int y0,
									int x1, int y1,
									int x2, int y2,
									HDC bmpdc,
									int u0, int v0,
									int u1, int v1,
									int u2, int v2);

void GameInit(HWND hwnd)
{
	g_MainDC = GetDC(hwnd);
	g_BackDC = CreateCompatibleDC(g_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_MainDC, _CLIENT_W, _CLIENT_H);
	DeleteObject(SelectObject(g_BackDC,hbmp));
	DeleteObject(hbmp);

	g_BmpDC = CreateCompatibleDC(g_MainDC);
	hbmp = (HBITMAP)LoadImageA(0, "01.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	DeleteObject(SelectObject(g_BmpDC,hbmp));
	DeleteObject(hbmp);

	srand(time(0));
}

int get_rand_int(int min, int max)
{
	return min + rand() % (max - min + 1);
}

void GameRun(HWND hwnd)
{
	BitBlt(g_MainDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	//绘制纹理到右边
	BitBlt(g_MainDC, 320, 0, 320, _CLIENT_H, g_BmpDC, 0, 0, SRCCOPY);

	//
	DrawTriangleTexture_FlatBottom(
		100, 0,
		0, 100,
		200, 100,
		g_MainDC,
		320, 0,
		640, 0,
		320, 480);

	DrawTriangleLine(
		100, 0,
		0, 100,
		200, 100);
	DrawTriangleLine(
		320, 0,
		640, 0,
		320, 480);

	//BitBlt(g_MainDC, 0, 0, _CLIENT_W, _CLIENT_H, g_BackDC, 0, 0, SRCCOPY);
}

void GameEnd(HWND hwnd)
{
	DeleteDC(g_BmpDC);
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

void DrawTriangleTexture_FlatBottom(int x0, int y0,
									int x1, int y1,
									int x2, int y2,
									HDC bmpdc,
									int u0, int v0,
									int u1, int v1,
									int u2, int v2)
{
	//		 (x0,y0)
	//(x1,y1)		(x2,y2)

	//得到所有梯度，即得到每一个变化的坐标随着目标三
	//角形上y值每递增一个单位这些变化的坐标的变化量
	float left_x_grads = (float)(x0 - x1) / (y0 - y1);
	float right_x_grads = (float)(x0 - x2) / (y0 - y2);
	float left_u_grads = (float)(u0 - u1) / (y0 - y1);
	float right_u_grads = (float)(u0 - u2) / (y0 - y2);
	float left_v_grads = (float)(v0 - v1) / (y0 - y1);
	float right_v_grads = (float)(v0 - v2) / (y0 - y2);

	//得到每个变化的坐标的初值
	float left_x = x0;
	float right_x = x0;
	float left_u = u0;
	float right_u = u0;
	float left_v = v0;
	float right_v = v0;

	//绘制循环
	for (int y = y0; y <= y1; ++y)
	{
		int x_left = (int)left_x;
		int x_right = (int)right_x;

		//for (int x = x_left; x <= x_right; ++x)
		//{
		//}

		MoveToEx(g_MainDC, x_left, y, 0);
		LineTo(g_MainDC, x_right, y);

		MoveToEx(g_MainDC, (int)left_u, (int)left_v, 0);
		LineTo(g_MainDC, (int)right_u, (int)right_v);

		Sleep(1);

		left_x += left_x_grads;
		right_x += right_x_grads;
		left_u += left_u_grads;
		right_u += right_u_grads;
		left_v += left_v_grads;
		right_v += right_v_grads;
	}
}