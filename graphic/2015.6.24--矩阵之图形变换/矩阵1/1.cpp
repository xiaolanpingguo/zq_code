#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <iostream>
#include "Vector2.h"
#include "Matrix.h"

#pragma comment(lib, "Msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

HWND g_hWnd = 0;
BOOL g_Act = TRUE;

void GameInit();
void GameRun();
void GameEnd();

LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch (uMsg)
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
	wc.lpszClassName = "123abc";

	RegisterClass(&wc);

	//可以根据客户区大小来计算窗口大小
	int sw = GetSystemMetrics(SM_CXSCREEN); //得到桌面的宽
	int sh = GetSystemMetrics(SM_CYSCREEN); //得到桌面的高
	RECT cr //cr得到客户区的位置、尺寸
		=
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		(sw - _CLIENT_W) / 2 + _CLIENT_W,
		(sh - _CLIENT_H) / 2 + _CLIENT_H
	};
	//根据传入的客户区位置、尺寸来计算窗口应该有的位置、尺寸
	AdjustWindowRect(
		&cr, //客户区矩形，本函数执行完毕之后会填入窗口矩形
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, //窗口风格
		FALSE); //有无菜单

	g_hWnd = CreateWindowA(
		wc.lpszClassName, //使用的窗口类别结构体的名字
		"hello world", //窗口标题栏文字
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		cr.left, //窗口左上角x坐标
		cr.top, //窗口左上角y坐标
		cr.right - cr.left, //窗口宽
		cr.bottom - cr.top, //窗口高
		HWND_DESKTOP, //父窗口，一般来说填写桌面窗口
		0, //菜单句柄，不用就填写0
		wc.hInstance, //应用程序实例句柄
		0); //保留参数

	//游戏初始化
	GameInit();

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	//查看当前的队头消息，如果有消息就返回真，没有消息就返回假
	//BOOL PeekMessage(
	//	LPMSG lpMsg, //得到队头消息的消息结构体
	//	HWND hWnd, //窗口，为0则得到当前线程中创建的所有窗口的消息
	//	UINT wMsgFilterMin, //消息过滤下限
	//	UINT wMsgFilterMax, //消息过滤上限
	//	UINT wRemoveMsg); //PM_REMOVE表示查看了消息之后将其从消息队列中删除，PM_NOREMOVE表示仅仅查看消息而不会将查看到的消息从队列中删除

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		//如果有消息本次游戏循环就处理消息
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//如果没有消息其当前窗口为激活状态就执行游戏循环
		else if (g_Act)
		{
			//每帧开始的时间
			int t0 = GetTickCount();

			//游戏运行
			GameRun();

			//每帧游戏时间的处理
			int t1 = GetTickCount() - t0;
			Sleep(t1 < _SLEEP_TIME ? _SLEEP_TIME - t1 : 1);
		}
		else
		//如果没有消息其当前窗口未被激活就等待消息
			WaitMessage();
	}

	//游戏结束
	GameEnd();

	return 1;
}

#include <time.h>

HDC main_dc; //主设备
HDC back_dc; //后备设备
HBITMAP back_bmp; //后备设备位图

float a = 0.0f;

void GameInit()
{
	//得到主绘图设备
	main_dc = GetDC(g_hWnd);

	//得到后备设备
	back_dc  = CreateCompatibleDC(main_dc);

	//创建后备设备位图
	back_bmp = CreateCompatibleBitmap(main_dc, _CLIENT_W, _CLIENT_H);

	//讲后备设备位图选入后备设备
	DeleteObject(SelectObject(back_dc, back_bmp));
}

void DrawLine(const CVector2* v1, const CVector2* v2)
{
	MoveToEx(back_dc, v1->x, v1->y, 0);
	LineTo(back_dc, v2->x, v2->y);
}

void GameRun()
{
	//设置初始的点
	CVector2 v[4];
	v[0].Set(100 + _CLIENT_W / 2,100 + _CLIENT_H / 2);
	v[1].Set(100 + _CLIENT_W / 2,-100 + _CLIENT_H / 2);
	v[2].Set(-100 + _CLIENT_W / 2,-100 + _CLIENT_H / 2);
	v[3].Set(-100 + _CLIENT_W / 2,100 + _CLIENT_H / 2);

	//得到旋转矩阵
	a += 0.02f;
	CMatrix3 m;
	m.Rotate(a);

	//得到新点
	CVector2 u[4];
	for (int i = 0; i < 4; ++i)
		_Vec_X_Mat(&v[i], &m, &u[i]);

	BitBlt(back_dc, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);
	
	DrawLine(&u[0], &u[1]);
	DrawLine(&u[1], &u[2]);
	DrawLine(&u[2], &u[3]);
	DrawLine(&u[3], &u[0]);
	
	BitBlt(main_dc, 0, 0, _CLIENT_W, _CLIENT_H, back_dc, 0, 0, SRCCOPY);

	////输入
	//if (GetAsyncKeyState(VK_LBUTTON) & 1)
	//{
	//	//得到光标相对于桌面的坐标
	//	POINT p;
	//	GetCursorPos(&p);

	//	//桌面的坐标转换为窗口客户区的坐标
	//	ScreenToClient(g_hWnd, &p);

	//	//在客户区中
	//	if (p.x >= 0 && p.x < _CLIENT_W && p.y >= 0 && p.y < _CLIENT_H)
	//	{
	//		Sphere[0].speed = CVector2(p.x, p.y) - Sphere[0].pos;
	//		Sphere[0].speed = Sphere[0].speed.Normalize() * speed;
	//	}
	//}
}

void GameEnd()
{
	//释放后备设备位图
	DeleteObject(back_bmp);

	//释放后备设备
	DeleteDC(back_dc);

	//释放主绘图设备
	ReleaseDC(g_hWnd, main_dc);
}