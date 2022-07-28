#include "Game.h"
#include "Main.h"
#include <iostream>
#include <ctime>

#include <ddraw.h>
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

#define _PIXEL_FORMAT 16

//555格式
//0rrrrrgg gggbbbbb
//rrrrrrrr & 0x1f = 000rrrrr << 10
//gggggggg & 0x1f = 000ggggg << 5
//bbbbbbbb & 0x1f = 000bbbbb

#define _555_RGB(r,g,b) \
	((((r) & 0x1f) << 10) | (((g) & 0x1f) << 5) | ((b) & 0x1f))

//565格式
//rrrrrggg gggbbbbb
//rrrrrrrr & 0x1f = 000rrrrr << 11
//gggggggg & 0x3f = 00gggggg << 5
//bbbbbbbb & 0x1f = 000bbbbb
#define _565_RGB(r,g,b) \
	((((r) & 0x1f) << 11) | (((g) & 0x3f) << 5) | ((b) & 0x1f))

short _555_color(unsigned char r, unsigned char g, unsigned char b)
{
	return _555_RGB(r, g, b);
}
short _565_color(unsigned char r, unsigned char g, unsigned char b)
{
	return _565_RGB(r, g, b);
}
short (*_16bit_color)(unsigned char, unsigned char, unsigned char) = 0;

LPDIRECTDRAW7 dd; //ddraw对象
LPDIRECTDRAWSURFACE7 dds; //ddraw表面对象
int rbs = 0; //主表面每行的字节数
char* color = 0; //主表面的颜色起始地址
int offset_x = 0, offset_y = 0; //窗口客户区左上角相对于屏幕的位置

bool _is_565()
{
	//锁定主表面，即开始绘制
	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	dds->Lock(0, &ddsd, DDLOCK_WAIT, 0);

	//若ddsd.ddpfPixelFormat.dwRGBBitCount为16，则当前颜色格式是565
	//若ddsd.ddpfPixelFormat.dwRGBBitCount为15，则当前颜色格式是555
	bool r = (ddsd.ddpfPixelFormat.dwRGBBitCount == 16);

	//解锁主表面，即结束绘制
	dds->Unlock(0);

	return r;
}

void Init()
{
	DirectDrawCreateEx(0, (void**)&dd, IID_IDirectDraw7, 0);
	dd->SetCooperativeLevel(g_hWnd, DDSCL_NORMAL);
	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	dd->GetDisplayMode(&ddsd);
	dd->SetDisplayMode(ddsd.dwWidth, ddsd.dwHeight, _PIXEL_FORMAT, 0, 0);

	//定义一个表面描述结构体
	ddsd.dwSize = sizeof(ddsd); //结构体的大小
	ddsd.dwFlags = DDSD_CAPS; //指明结构体中的ddsCaps成员变量有效
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE; //表明要创建的是主表面

	//创建主表面
	dd->CreateSurface(&ddsd, &dds, 0);

	if (_is_565())
		_16bit_color = _565_color;
	else
		_16bit_color = _555_color;
}

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

	//绘制矩形
	for (int y = 0; y < 100; ++y)
	{
		for (int x = 0; x < 200; ++x)
		{
			*((short*)(color + rbs * (y + offset_y) + (x + offset_x) * 2))
				=
			(*_16bit_color)(0, 255, 0);
		}
		//16bit				32bit
		//0		<--->		0
		//1		<--->		8
		//2		<--->		16
		//3		<--->		24
		//4		<--->		32
		//...
		//32	<--->		256
	}

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
