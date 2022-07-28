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

HDC bmpdc;
HBITMAP hbmp;

XFORM dw;

//单位化
void XFORM_Identity(XFORM* xf);
void XFORM_Scaling(XFORM* xf, float x, float y);
void XFORM_Rotate(XFORM* xf, float a);
void XFORM_Translate(XFORM* xf, float x, float y);
XFORM* _XF_X_XF(const XFORM* xf1, const XFORM* xf2, XFORM* output);

void GameInit()
{
	//得到主绘图设备
	main_dc = GetDC(g_hWnd);

	//得到后备设备
	back_dc  = CreateCompatibleDC(main_dc);

	//开启高级绘图模式
	SetGraphicsMode(back_dc, GM_ADVANCED);

	//创建后备设备位图
	back_bmp = CreateCompatibleBitmap(main_dc, _CLIENT_W, _CLIENT_H);

	//讲后备设备位图选入后备设备
	DeleteObject(SelectObject(back_dc, back_bmp));

	//初始化单位矩阵
	XFORM_Identity(&dw);

	hbmp = (HBITMAP)LoadImageA(0, "1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc = CreateCompatibleDC(main_dc);
	DeleteObject(SelectObject(bmpdc, hbmp));
}

void GameRun()
{
	BitBlt(back_dc, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);
	
	XFORM xf1, xf2, xf3;

	static float a = 0.0f;
	a += 0.05f;
	XFORM_Rotate(&xf1, a);
	XFORM_Translate(&xf2, _CLIENT_W / 2, _CLIENT_H / 2);
	_XF_X_XF(&xf1, &xf2, &xf3);
	
	int t1 = GetTickCount();

	SetWorldTransform(back_dc, &xf3);

	BitBlt(back_dc, 0, 0, 100, 100, bmpdc, 0, 0, SRCCOPY);

	char buf[32];
	sprintf_s(buf, 32, "%d", GetTickCount() - t1);
	SetWindowTextA(g_hWnd, buf);

	//我们自己用矩阵来完成变换，实际上非常消耗效率，这种矩阵处理
	//实际上很多显卡直接支持，Windows中就提供了对变换矩阵的一些操作
	
	//恢复变换矩阵为单位矩阵
	SetWorldTransform(back_dc, &dw);
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

//Windows中提供的矩阵叫XFORM，其结构如下
//eM11 eM12 0
//eM21 eM22 0
//eDx  eDy  1
//但是Windows并没有提供直接创建各种变换矩阵的函数，所以这些函数只能我们自己实现
//1）Windows中要使用图形变换，必须开启高级绘制功能
//2）用SetWorldTransform来设置当前绘制的变换矩阵，
//   一旦设置这个变换矩阵会影响其后所有的绘制，如
//   果在某个绘制之前不希望该绘制收矩阵影响，那么
//   设置变换矩阵为单位矩阵即可

//单位化
void XFORM_Identity(XFORM* xf)
{
	xf->eM11 = xf->eM22 = 1.0f;
	xf->eM12 = xf->eM21 = xf->eDx = xf->eDy = 0.0f;
}

//缩放
void XFORM_Scaling(XFORM* xf, float x, float y)
{
	xf->eM11 = x;		xf->eM12 = 0.0f;
	xf->eM21 = 0.0f;	xf->eM22 = y;
	xf->eDx = 0.0f;		xf->eDy = 0.0f;
}

//旋转
void XFORM_Rotate(XFORM* xf, float a)
{
	xf->eM11 = cos(a);		xf->eM12 = sin(a);
	xf->eM21 = -xf->eM12;	xf->eM22 = xf->eM11;
	xf->eDx = 0.0f;			xf->eDy = 0.0f;
}

//平移
void XFORM_Translate(XFORM* xf, float x, float y)
{
	xf->eM11 = 1.0f;	xf->eM12 = 0.0f;
	xf->eM21 = 0.0f;	xf->eM22 = 1.0f;
	xf->eDx = x;		xf->eDy = y;
}

XFORM* _XF_X_XF(const XFORM* xf1,
				const XFORM* xf2,
				XFORM* output)
{
	//eM11 eM12 0
	//eM21 eM22 0
	//eDx  eDy  1

	output->eM11 = xf1->eM11 * xf2->eM11 + xf1->eM12 * xf2->eM21;
	output->eM12 = xf1->eM11 * xf2->eM12 + xf1->eM12 * xf2->eM22;

	output->eM21 = xf1->eM21 * xf2->eM11 + xf1->eM22 * xf2->eM21;
	output->eM22 = xf1->eM21 * xf2->eM12 + xf1->eM22 * xf2->eM22;

	output->eDx = xf1->eDx * xf2->eM11 + xf1->eDy * xf2->eM21 + xf2->eDx;
	output->eDy = xf1->eDx * xf2->eM12 + xf1->eDy * xf2->eM22 + xf2->eDy;

	return output;
}