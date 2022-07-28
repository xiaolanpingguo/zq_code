#include <windows.h>
#include <iostream>

#define _CLIENT_W 640
#define _CLIENT_H 480

//R（红）G（绿）B（蓝）
//255 0 0:标准红
//0 255 0:标准绿
//0 0 255:标准蓝
//255 255 0:标准黄
//255 0 255:标准紫
//0 255 255:标准天蓝
//0 0 0:黑
//255 255 255:白
//? ? ?:灰

LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg, //消息值
							WPARAM wParam, //消息的附加参数1
							LPARAM lParam) //消息的附加参数2
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC dc = BeginPaint(hwnd, &ps);

			//高级模式要显卡支持
			SetGraphicsMode(dc, GM_ADVANCED);

			//创建一个红色画笔
			HPEN p1 = CreatePen(
				PS_SOLID, //风格
				50, //像素宽，如果像素宽度大于1，那么风格只能是PS_SOLID
				RGB(255, 0, 0)); //颜色

			//p0就得到老的画笔
			HPEN p0 = (HPEN)SelectObject(dc, p1);

			//画笔[p1]
			//画刷[b0]
			//字体[f0]

			Rectangle(dc, 100, 100, 200, 300);
			
			HPEN p2 = CreatePen(
				PS_DOT, //风格
				1, //像素宽，如果像素宽度大于1，那么风格只能是PS_SOLID
				RGB(0, 255, 0));

			SelectObject(dc, p2);

			//画笔[p2]
			//画刷[b0]
			//字体[f0]

			Ellipse(dc, 200, 150, 300, 350);

			//创建实心画刷
			HBRUSH b1 = CreateSolidBrush(
				RGB(255, 255, 0)); //颜色

			HBRUSH b0 = (HBRUSH)SelectObject(dc, b1);

			//画笔[p2]
			//画刷[b1]
			//字体[f0]

			Rectangle(dc, 250, 250, 400, 300);

			//创建有风格画刷
			HBRUSH b2 = CreateHatchBrush(
				HS_DIAGCROSS, //风格
				RGB(255, 0, 255)); //颜色

			SelectObject(dc, b2);

			//画笔[p2]
			//画刷[b2]
			//字体[f0]

			Ellipse(dc, 300, 300, 400, 450);

			HFONT f1 = CreateFontA(
				40, //高
				20, //宽
				0, //字体基准线斜度,单位为0.1度
				300, //字体斜度,单位为0.1度，必须开启高级绘图模式
				400, //粗细0~800
				false, //是否斜体
				false, //是否下划线
				false, //是否破折线
				DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_DONTCARE,
				"幼圆"); //字体外观

			HFONT f0 = (HFONT)SelectObject(dc, f1);

			//画笔[p2]
			//画刷[b2]
			//字体[f1]

			//字体的颜色不是画笔控制，而是单独一个函数来设置
			SetTextColor(dc, RGB(0, 0, 255));

			//可以设置字体的背景显示方式，TRANSPARENT表示背景不填颜色
			SetBkMode(dc, TRANSPARENT);

			TextOutA(dc, 0, 0, "123abc你好", 8);

			HFONT f2 = CreateFontA(
				40,
				20,
				450,
				0,
				800,
				true,
				false,
				false,
				DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_DONTCARE,
				"黑体");

			SelectObject(dc, f2);

			//画笔[p2]
			//画刷[b2]
			//字体[f2]

			SetTextColor(dc, RGB(255, 255, 0));

			TextOutA(dc, 0, 300, "123abc你好", 10);

			//不会伴随dc一起释放的GDI对象我们只能自己释放
			DeleteObject(p0);
			DeleteObject(p1);
			DeleteObject(b0);
			DeleteObject(b1);
			DeleteObject(f0);
			DeleteObject(f1);

			EndPaint(hwnd, &ps); //会释放dc和p2、b2、f2
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
	wc.hbrBackground = (HBRUSH)COLOR_MENU;
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
		WS_OVERLAPPEDWINDOW, //窗口风格
		FALSE); //有无菜单

	HWND hwnd = CreateWindowA(
		wc.lpszClassName, //使用的窗口类别结构体的名字
		"hello world", //窗口标题栏文字
		WS_OVERLAPPEDWINDOW, //窗口风格
		cr.left, //窗口左上角x坐标
		cr.top, //窗口左上角y坐标
		cr.right - cr.left, //窗口宽
		cr.bottom - cr.top, //窗口高
		HWND_DESKTOP, //父窗口，一般来说填写桌面窗口
		0, //菜单句柄，不用就填写0
		wc.hInstance, //应用程序实例句柄
		0); //保留参数

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}