#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <iostream>
#include "Vector2.h"

#pragma comment(lib, "Msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

HWND g_hWnd = 0;
BOOL g_Act = TRUE;

void GameInit();
void GameRun();
void GameEnd();

extern int speed;
void SetSpeed();

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
	case WM_MOUSEWHEEL:
		{
			if (WHEEL_DELTA == (short)HIWORD(wParam) && speed < 32)
				speed += 1;
			else if (-WHEEL_DELTA == (short)HIWORD(wParam) && speed > 1)
			{
				speed -= 1;
			}
			SetSpeed();
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

#define _R 20
#define _SPEED 10
#define _MCL 0.05f

struct _SPHERE //球
{
	CVector2 pos; //位置
	CVector2 speed; //速度
};
_SPHERE Sphere[10]; //第0个为白球
int speed; //击球速度

void SetSpeed()
{
	char buf[64];
	sprintf_s(buf, 64, "击球速度:%d", speed);
	SetWindowTextA(g_hWnd, buf);
}

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

	//初始化白球位置
	Sphere[0].pos.Set(_CLIENT_W * 0.25f, _CLIENT_H / 2);

	//初始化其它球
	for (int i = 1; i < 10; ++i)
	{
		Sphere[i].pos.Set(_CLIENT_W * 0.75f, i * 45);
	}

	//初始化击球速度
	speed = 16;
	SetSpeed();
}

void GameRun()
{
	BitBlt(back_dc, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);
	
	for (int i = 0; i < 10; ++i)
	{
		Ellipse(back_dc, Sphere[i].pos.x - _R, Sphere[i].pos.y - _R, Sphere[i].pos.x + _R, Sphere[i].pos.y + _R);
		char buf[32];
		sprintf_s(buf, 32, "%d", i);
		TextOutA(back_dc, Sphere[i].pos.x, Sphere[i].pos.y, buf, strlen(buf));
	}

	BitBlt(main_dc, 0, 0, _CLIENT_W, _CLIENT_H, back_dc, 0, 0, SRCCOPY);

	//所有球体和墙壁的碰撞
	for (int i = 0; i < 10; ++i)
	{
		//逻辑
		if (!_IS_ZERO(Sphere[i].speed.Length()))
		{
			Sphere[i].pos += Sphere[i].speed;

			//与墙体的碰撞

			//x方向
			if (Sphere[i].pos.x - _R <= 0.0f || Sphere[i].pos.x + _R >= _CLIENT_W)
			{
				if (Sphere[i].pos.x - _R <= 0.0f)
					Sphere[i].pos.x = _R;
				else
					Sphere[i].pos.x = _CLIENT_W - _R;

				Sphere[i].speed.x = -Sphere[i].speed.x;
			}
			//y方向
			if (Sphere[i].pos.y - _R <= 0.0f || Sphere[i].pos.y + _R >= _CLIENT_H)
			{
				if (Sphere[i].pos.y - _R <= 0.0f)
					Sphere[i].pos.y = _R;
				else
					Sphere[i].pos.y = _CLIENT_H - _R;

				Sphere[i].speed.y = -Sphere[i].speed.y;
			}

			float len = Sphere[i].speed.Length();
			CVector2 nor = Sphere[i].speed.Normalize();
			len -= _MCL;
			if (len <= 0.0f)
				Sphere[i].speed.Set();
			else
				Sphere[i].speed = nor * len;
		}
	}

	//所有球体和球体的碰撞
	for (int i = 0; i < 9; ++i)
	{
		for (int j = i + 1; j < 10; ++j)
		{
			//v是两个球i和球j的球心连线向量
			CVector2 v = Sphere[i].pos - Sphere[j].pos;
			if (v.Length() < 2 * _R)
			{
				//将两个球分开
				CVector2 u = v.Normalize();
				CVector2 w = u * (2 * _R - v.Length());
				Sphere[i].pos += w;

				//计算碰撞之后的速度

				//得到两个球在球心连线上面的投影
				CVector2 vi1 = Sphere[i].speed.Shadow(-v);
				CVector2 vi2 = Sphere[i].speed - vi1;
				CVector2 vj1 = Sphere[j].speed.Shadow(v);
				CVector2 vj2 = Sphere[j].speed - vj1;

				//更新速度
				Sphere[i].speed = vi2 + vj1;
				Sphere[j].speed = vj2 + vi1;
			}
		}
	}

	//输入
	if (GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		//得到光标相对于桌面的坐标
		POINT p;
		GetCursorPos(&p);

		//桌面的坐标转换为窗口客户区的坐标
		ScreenToClient(g_hWnd, &p);

		//在客户区中
		if (p.x >= 0 && p.x < _CLIENT_W && p.y >= 0 && p.y < _CLIENT_H)
		{
			Sphere[0].speed = CVector2(p.x, p.y) - Sphere[0].pos;
			Sphere[0].speed = Sphere[0].speed.Normalize() * speed;
		}
	}
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