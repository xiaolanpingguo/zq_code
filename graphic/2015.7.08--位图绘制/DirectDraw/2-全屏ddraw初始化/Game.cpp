#include "Game.h"
#include "Main.h"

#include "ddraw.h"
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

LPDIRECTDRAW7 dd; //ddraw对象


void Init()
{
	if (DD_OK != DirectDrawCreateEx(0, (void**)&dd, IID_IDirectDraw7, 0))
		return;

	//DDSCL_ALLOWREBOOT:允许在全屏下面使用Ctrl+Alt+Del
	//DDSCL_EXCLUSIVE:独占模式，值的是ddraw程序完全独占显示器
	//DDSCL_FULLSCREEN:全屏模式
	if (DD_OK != dd->SetCooperativeLevel(g_hWnd, DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN))
		return;

	dd->SetDisplayMode(640, 480, 32, 0, 0);
}

void Run()
{
	
}

void End()
{
	if (dd)
		dd->Release();
}