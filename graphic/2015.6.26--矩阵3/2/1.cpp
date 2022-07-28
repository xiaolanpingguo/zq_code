#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <iostream>
#include "Vector2.h"
#include "Matrix.h"
#include "MY_XFORM.h"

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
#include <vector>

HDC main_dc; //主设备
HDC back_dc; //后备设备
HBITMAP back_bmp; //后备设备位图

HDC bmpdc;
HBITMAP hbmp;

CMY_XFORM dw; //单位矩阵

CVector2 pos(_CLIENT_W / 2, _CLIENT_H / 2); //位置
float angle = 0.0f; //角度

struct _XIAN_DUAN
{
	CVector2 v[2];
};
std::vector<_XIAN_DUAN> xd;

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

	//开启高级绘图模式
	SetGraphicsMode(back_dc, GM_ADVANCED);

	hbmp = (HBITMAP)LoadImageA(0, "0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc = CreateCompatibleDC(main_dc);
	DeleteObject(SelectObject(bmpdc, hbmp));
}

void GameRun()
{
	//清空后备
	BitBlt(back_dc, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	//得到夹角
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(g_hWnd, &p);
	CVector2 dir = CVector2(p.x, p.y) - pos;
	dir = dir.Normalize(); //单位化了之后长度为1
	angle = acos(dir * CVector2(0.0f, -1.0f));
	if (p.x < pos.x) //角度的正负处理
		angle = -angle;

	CMY_XFORM mx1, mx2, mx3;
	mx1.Rotate(angle);
	mx2.Translate(pos.x, pos.y);
	mx3 = mx1 * mx2; //重载了的矩阵乘法

	SetWorldTransform(back_dc, &mx3);
	TransparentBlt(back_dc, -15, -25, 30, 50, bmpdc, 0, 0, 30, 50, RGB(0, 255, 0));
	SetWorldTransform(back_dc, &dw);

	//绘制线段
	for (int i = 0; i < xd.size(); ++i)
	{
		MoveToEx(back_dc, xd[i].v[0].x, xd[i].v[0].y, 0);
		LineTo(back_dc, xd[i].v[1].x, xd[i].v[1].y);
	}

	//发射
	if (GetAsyncKeyState('W') & 0x8000)
		pos.y -= 5.0f;
	if (GetAsyncKeyState('S') & 0x8000)
		pos.y += 5.0f;
	if (GetAsyncKeyState('A') & 0x8000)
		pos.x -= 5.0f;
	if (GetAsyncKeyState('D') & 0x8000)
		pos.x += 5.0f;
	if (GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		CVector2 v = CVector2(p.x, p.y) - pos;
		v = v.Normalize();
		CVector2 v1 = v.Clock();
		CVector2 v2 = v.CounterClock();
		v1 = v1 * 50 + CVector2(p.x, p.y);
		v2 = v2 * 50 + CVector2(p.x, p.y);
		_XIAN_DUAN a;
		a.v[0] = v1;
		a.v[1] = v2;
		xd.push_back(a);
	}

	//二次缓冲
	BitBlt(main_dc, 0, 0, _CLIENT_W, _CLIENT_H, back_dc, 0, 0, SRCCOPY);
}

void GameEnd()
{
	DeleteObject(hbmp);
	DeleteDC(bmpdc);

	//释放后备设备位图
	DeleteObject(back_bmp);

	//释放后备设备
	DeleteDC(back_dc);

	//释放主绘图设备
	ReleaseDC(g_hWnd, main_dc);
}