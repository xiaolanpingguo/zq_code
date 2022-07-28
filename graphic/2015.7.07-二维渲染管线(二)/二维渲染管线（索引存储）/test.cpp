#include <windows.h>
#include <vector>
#include <time.h>
#include <math.h>
#include "Matrix3.h"
#include "Render2D.h"

#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

BOOL g_Act = TRUE;
HDC g_MainDC;
HDC g_BackDC;

#define _S_W 600
#define _S_H 400
#define _V_LEFT 100
#define _V_TOP 100
#define _V_W 300
#define _V_H 200
MODAL2D fk;
HDC g_BmpDC;

void GameInit(HWND hwnd)
{
	g_MainDC = GetDC(hwnd);
	g_BackDC = CreateCompatibleDC(g_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_MainDC, _CLIENT_W, _CLIENT_H);
	DeleteObject(SelectObject(g_BackDC,hbmp));
	DeleteObject(hbmp);

	srand(time(0));

	//加载模型和纹理
	LoadMODAL2D(&fk, "modal\\fk.txt");
	g_BmpDC = CreateCompatibleDC(g_MainDC);
	hbmp = (HBITMAP)LoadImageA(0, "texture\\01.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	DeleteObject(SelectObject(g_BmpDC,hbmp));
	DeleteObject(hbmp);

	//设置视口和视口变换矩阵
	CMatrix3 m;
	SetView(_V_LEFT, _V_TOP, _V_W, _V_H);
	GetViewMatrix(&m, _S_W, _S_H, _V_LEFT, _V_TOP, _V_W, _V_H);
	SetMatrix(_VIEW_MATRIX, &m);
}

int get_rand_int(int min, int max)
{
	return min + rand() % (max - min + 1);
}

void GameRun(HWND hwnd)
{
	//设置摄像机变换矩阵
	CMatrix3 m;
	static CVector2 eye(0.0f, 0.0f);
	static CVector2 at(0.0f, 1.0f);
	GetCameraMatrix(&m, &eye, &at);
	SetMatrix(_CAMERA_MATRIX, &m);
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		CVector2 dir = at - eye;
		eye += dir.Normalize();
		at += dir.Normalize();
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		CVector2 dir = at - eye;
		eye -= dir.Normalize();
		at -= dir.Normalize();
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		CVector2 dir = at - eye, new_dir;
		dir = dir.Normalize();
		CMatrix3 m;
		m.Rotate(-0.3f);
		_Vec_X_Mat(&dir, &m, &new_dir);
		at = eye + new_dir;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		CVector2 dir = at - eye, new_dir;
		dir = dir.Normalize();
		CMatrix3 m;
		m.Rotate(+0.3f);
		_Vec_X_Mat(&dir, &m, &new_dir);
		at = eye + new_dir;
	}

	BitBlt(g_BackDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	Rectangle(g_BackDC, _V_LEFT, _V_TOP, _V_LEFT + _V_W, _V_TOP + _V_H);

	//绘制物体1
	static float angle = 0.0f;
	//angle += 0.01f;
	CMatrix3 m0;
	m0.Rotate(angle);
	static float x = 0.0f, y = 0.0f;
	if (GetAsyncKeyState('W') & 0x8000)
		y -= 5.0f;
	if (GetAsyncKeyState('S') & 0x8000)
		y += 5.0f;
	if (GetAsyncKeyState('A') & 0x8000)
		x -= 5.0f;
	if (GetAsyncKeyState('D') & 0x8000)
		x += 5.0f;
	CMatrix3 m1;
	m1.Translate(x, y);
	CMatrix3 m2;
	SetMatrix(_WORLD_MATRIX, _Mat_X_Mat(&m0, &m1, &m2));
	DrawMODAL2D(g_BackDC, &fk, g_BmpDC);

	//绘制物体2
	m1.Translate(200, 200);
	SetMatrix(_WORLD_MATRIX, &m1);
	DrawMODAL2D(g_BackDC, &fk, g_BmpDC);

	//绘制摄像机
	MoveToEx(g_BackDC, (_V_LEFT + (_V_LEFT + _V_W)) / 2, (_V_TOP + (_V_TOP + _V_H)) / 2, 0);
	LineTo(g_BackDC, (_V_LEFT + (_V_LEFT + _V_W)) / 2, (_V_TOP + (_V_TOP + _V_H)) / 2 - 64);

	BitBlt(g_MainDC, 0, 0, _CLIENT_W, _CLIENT_H, g_BackDC, 0, 0, SRCCOPY);
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