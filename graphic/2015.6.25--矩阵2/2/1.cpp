#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <iostream>
#include "Vector2.h"
#include "Matrix3.h"

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
#include "Matrix3.h"

HDC main_dc; //主设备
HDC back_dc; //后备设备
HBITMAP back_bmp; //后备设备位图

bool xz = true; //旋转标志，为真表示旋转，为假表示伸缩
float angle = 0.0f; //角度
bool add_angle = true; //角度递增标志
CVector2 cur; //当前的点
CVector2 cur1; //当前的点
float len = 1.0f;
bool sc = true;
CVector2 qiu; //球
float qiu_r; //球的半径
bool jz; //击中了球的标志

void DrawLine(const CVector2* v1, const CVector2* v2)
{
	MoveToEx(back_dc, v1->x, v1->y, 0);
	LineTo(back_dc, v2->x, v2->y);
}

float get_rand_float(float min, float max)
{
	return (max - min) * (rand() / 32767.0f) + min;
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

	//初始化球
	srand(time(0));
	qiu.Set(rand() % _CLIENT_W, rand() % (_CLIENT_H - 100) + 100);
	qiu_r = get_rand_float(10.0f, 50.0f);
}

void GameRun()
{
	//旋转
	if (xz)
	{
		//角度变化
		if (add_angle)
		{
			angle += 0.05f;
			if (angle >= 3.1415926f)
				add_angle = false;
		}
		else
		{
			angle -= 0.05f;
			if (angle <= 0.0f)
				add_angle = true;
		}

		//状态改变
		if (GetAsyncKeyState(VK_RETURN) & 1)
		{
			len = 100.0f;
			sc = true;
			xz = false;
		}
	}
	else
	{
		if (sc)
		{
			//得到方向向量的单位向量
			CVector2 dir = cur - CVector2(_CLIENT_W / 2.0f, 0.0f);
			dir = dir.Normalize();

			//长度变化
			len += 5.0f;

			//得到当前的绘制位置
			cur1 = len * dir;
			cur1 += CVector2(_CLIENT_W / 2.0f, 0.0f);

			//判断是否碰到了球
			if ((cur1 - qiu).Length() < qiu_r)
			{
				sc = false;
				jz = true;
			}

			if (cur1.x < 0 || cur1.x > _CLIENT_W || cur1.y < 0 || cur1.y > _CLIENT_H)
			{
				sc = false;
				jz = false;
				cur1.Set();
			}
		}
		else
		{
			//得到方向向量的单位向量
			CVector2 dir = cur - CVector2(_CLIENT_W / 2.0f, 0.0f);
			dir = dir.Normalize();

			//长度变化
			len -= 5.0f;

			//得到当前的绘制位置
			cur1 = len * dir;
			cur1 += CVector2(_CLIENT_W / 2.0f, 0.0f);

			if (jz)
			{
				qiu = cur1;
			}

			if (len < 100.0f)
			{
				if (jz)
				{
					qiu.Set(rand() % _CLIENT_W, rand() % (_CLIENT_H - 100) + 100);
					qiu_r = get_rand_float(10.0f, 50.0f);
				}
				xz = true;
			}
		}
	}

	BitBlt(back_dc, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	Ellipse(back_dc, qiu.x - qiu_r, qiu.y - qiu_r, qiu.x + qiu_r, qiu.y + qiu_r);
	
	if (xz)
	{
		//构造旋转矩阵
		CMatrix3 m0;
		m0.Rotate(angle);

		//构造平移矩阵
		CMatrix3 m1;
		m1.Translate(_CLIENT_W / 2.0f, 0.0f);

		//得到组合矩阵
		CMatrix3 m2;
		_Mat_X_Mat(&m0, &m1, &m2);

		//变换
		CVector2 v(100.0f, 0.0f);
		_Vec_X_Mat(&v, &m2, &cur);

		CVector2 u(_CLIENT_W / 2.0f, 0.0f);
		DrawLine(&u, &cur);
	}
	else
	{
		CVector2 u(_CLIENT_W / 2.0f, 0.0f);
		DrawLine(&u, &cur1);
	}
	
	BitBlt(main_dc, 0, 0, _CLIENT_W, _CLIENT_H, back_dc, 0, 0, SRCCOPY);
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