#include <windows.h>
#include <vector>
#include <time.h>
#include "Matrix3.h"
#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

BOOL g_Act = TRUE;//窗口激活标志

HDC g_MainDC;
HDC g_BackDC;

CVector2 zfx[4];

float angle = 0.0f; //角度
bool fd = true; //放大
float sfl = 1.0f; //缩放量
CVector2 wz; //位置

void GameInit(HWND hwnd)
{
	g_MainDC = GetDC(hwnd);
	g_BackDC = CreateCompatibleDC(g_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_MainDC, _CLIENT_W, _CLIENT_H);
	DeleteObject(SelectObject(g_BackDC,hbmp));
	DeleteObject(hbmp);

	srand(time(0));

	zfx[0].Set(100, 100);
	zfx[1].Set(100, -100);
	zfx[2].Set(-100, -100);
	zfx[3].Set(-100, 100);
}

void GameRun(HWND hwnd)
{
	BitBlt(g_BackDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	CMatrix3 m0, m1, m2, m3, m4;

	//得到旋转矩阵
	angle += 0.1f;
	m0.Rotate(angle);

	//得到平移矩阵
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);
	wz.x = p.x;
	wz.y = p.y;
	m1.Translate(wz.x, wz.y);

	//得到缩放矩阵
	if (fd)
	{
		sfl += 0.05f;
		if (sfl > 3.0f)
			fd = false;
	}
	else
	{
		sfl -= 0.05f;
		if (sfl < 0.333f)
			fd = true;
	}
	m2.Scaling(sfl, sfl);

	//得到组合矩阵
	_MxM(_MxM(&m0, &m2, &m3), &m1, &m4);

	//得到变换结果
	CVector2 u[4];
	for (int i = 0; i < 4; ++i)
		_VxM(&zfx[i], &m4, &u[i]); //u2存储了先选择再平移的结果
	
	//绘制
	MoveToEx(g_BackDC, u[0].x, u[0].y, 0);
	LineTo(g_BackDC, u[1].x, u[1].y);
	MoveToEx(g_BackDC, u[1].x, u[1].y, 0);
	LineTo(g_BackDC, u[2].x, u[2].y);
	MoveToEx(g_BackDC, u[2].x, u[2].y, 0);
	LineTo(g_BackDC, u[3].x, u[3].y);
	MoveToEx(g_BackDC, u[3].x, u[3].y, 0);
	LineTo(g_BackDC, u[0].x, u[0].y);

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