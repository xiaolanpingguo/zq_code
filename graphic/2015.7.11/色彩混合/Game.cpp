#include "Game.h"
#include "Main.h"
#include <iostream>
#include <ctime>

#include <ddraw.h>
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

LPDIRECTDRAW7 dd; //ddraw对象
LPDIRECTDRAWSURFACE7 dds; //ddraw表面对象
int rbs = 0; //主表面每行的字节数
char* color = 0; //主表面的颜色起始地址
int offset_x = 0, offset_y = 0; //窗口客户区左上角相对于屏幕的位置

void Init()
{
	DirectDrawCreateEx(0, (void**)&dd, IID_IDirectDraw7, 0);
	dd->SetCooperativeLevel(g_hWnd, DDSCL_NORMAL);
	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	dd->GetDisplayMode(&ddsd);
	dd->SetDisplayMode(ddsd.dwWidth, ddsd.dwHeight, ddsd.ddpfPixelFormat.dwRGBBitCount, 0, 0);

	//定义一个表面描述结构体
	ddsd.dwSize = sizeof(ddsd); //结构体的大小
	ddsd.dwFlags = DDSD_CAPS; //指明结构体中的ddsCaps成员变量有效
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE; //表明要创建的是主表面

	//创建主表面
	dd->CreateSurface(&ddsd, &dds, 0);

	srand((unsigned int)time(0));
}

#define _SURFACE_COLOR(x,y) *((int*)(color + (y) * rbs + (x) * 4))
#define _RGB_COLOR(r,g,b) ((r) << 16 | (g) << 8 | (b))
void DrawRect1(int, int, int, int, int);
void DrawRect2(int, int, int, int, int);
void DrawRect3(int, int, int, int, int);
void DrawRect4(int, int, int, int, int, float);

void Run()
{
	//锁定主表面，即开始绘制
	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	dds->Lock(
		0, //要锁定的表面中矩形地址，如果为空则表示锁定整个表面
		&ddsd, //此处的表面描述结构体是为了得到表面信息
		DDLOCK_WAIT, //表示如果锁定不了表面就等待直到能够锁定表面
		0);
	rbs = ddsd.lPitch;
	color = (char*)ddsd.lpSurface;
	POINT p = {0, 0};
	ClientToScreen(g_hWnd, &p);
	offset_x = p.x;
	offset_y = p.y;

	//绘制
	DrawRect3(0, 0, _CLIENT_W, _CLIENT_H, _RGB_COLOR(255, 255, 255));
	DrawRect4(100, 200, 250, 300, _RGB_COLOR(255, 0, 0), 1.0f);
	DrawRect4(140, 240, 350, 400, _RGB_COLOR(255, 255, 0), 0.5);

	//解锁主表面，即结束绘制
	dds->Unlock(0);
}

void End()
{
	if (dds)
		dds->Release();

	if (dd)
		dd->Release();
}

void DrawRect1(int left, int top, int right, int bottom, int c)
{
	for (int y = top; y <= bottom; ++y)
	{
		for (int x = left; x <= right; ++x)
		{
			_SURFACE_COLOR(x + offset_x, y + offset_y) = c;
		}
	}
}

void DrawRect2(int left, int top, int right, int bottom, int c)
{
	for (int y = top; y <= bottom; ++y)
	{
		for (int x = left; x <= right; ++x)
		{
			int dx = x + offset_x;
			int dy = y + offset_y;
			if (dx >= 0 && dx < g_ScreenW && dy >= 0 && dy < g_ScreenH)
				_SURFACE_COLOR(dx, dy) = c;
		}
	}
}

struct MY_RECT
{
	int left, top, right, bottom;
};

bool intersect_rect(const MY_RECT* r1,
					const MY_RECT* r2,
					MY_RECT* r3)
{
	if (r1->left > r2->right ||
		r2->left > r1->right ||
		r1->top > r2->bottom ||
		r2->top > r1->bottom)
		return false;
	else
	{
		*r3 = *r1;
		if (r2->left > r1->left)
			r3->left = r2->left;
		if (r2->right < r1->right)
			r3->right = r2->right;
		if (r2->top > r1->top)
			r3->top = r2->top;
		if (r2->bottom < r1->bottom)
			r3->bottom = r2->bottom;
		return true;
	}
}

void DrawRect3(int left, int top, int right, int bottom, int c)
{
	//得到桌面矩形
	MY_RECT r1 = {0, 0, g_ScreenW - 1, g_ScreenH - 1};

	//根据客户区位置得到绘制矩形相对于桌面的位置
	MY_RECT r2 = {left + offset_x, top + offset_y, right + offset_x, bottom + offset_y};

	MY_RECT r3;
	if (intersect_rect(&r1, &r2, &r3))
	{
		for (int y = r3.top; y <= r3.bottom; ++y)
		{
			for (int x = r3.left; x <= r3.right; ++x)
				_SURFACE_COLOR(x, y) = c;
		}
	}
}

//Alpha混合原理
//要使得画面呈现半透明，必须使用色彩混合技术
//1）棋格混合：两个要混合的色彩相互交叉绘制，因为
//   像素非常小，所以容易造成色彩混合到一起的感觉
//   这种处理相对简单，效率相比Alpha混合要高
//2）Alpha混合
//   已知color1、color2，以及color2的混合因子f(0~1的比值)
//   则要将color2绘制到color1上并进行Alpha混合的话，其混合公式如下：
//   dest_color.r = (color2.r * f) + (color1.r * (1 - f))
//   dest_color.g = (color2.g * f) + (color1.g * (1 - f))
//   dest_color.b = (color2.b * f) + (color1.b * (1 - f))

void DrawRect4(int left, int top, int right, int bottom, int c, float f)
{
	//得到桌面矩形
	MY_RECT r1 = {0, 0, g_ScreenW - 1, g_ScreenH - 1};

	//根据客户区位置得到绘制矩形相对于桌面的位置
	MY_RECT r2 = {left + offset_x, top + offset_y, right + offset_x, bottom + offset_y};

	MY_RECT r3;

	if (intersect_rect(&r1, &r2, &r3))
	{
		float nf = 1.0f - f;

		for (int y = r3.top; y <= r3.bottom; ++y)
		{
			for (int x = r3.left; x <= r3.right; ++x)
			{
				unsigned char* c1 = (unsigned char*)(color + (y) * rbs + (x) * 4);
				unsigned char* c2 = (unsigned char*)&c;

				unsigned char b = (unsigned char)(c1[0] * nf + c2[0] * f);
				unsigned char g = (unsigned char)(c1[1] * nf + c2[1] * f);
				unsigned char r = (unsigned char)(c1[2] * nf + c2[2] * f);

				_SURFACE_COLOR(x, y) = _RGB_COLOR(r, g, b);
			}
		}
	}
}