#include <windows.h>
#include "UseBmp.h"

BOOL g_Act = TRUE;//窗口激活标志

HDC g_mainDC;//主显示设备

POINT g_hero;

HDC g_bmpdc;

void GameInit(HWND hwnd)
{
	//获取主显示设备
	g_mainDC = GetDC(hwnd);

	g_hero.x = 150;
	g_hero.y = 240;

	g_bmpdc = GetBmpDC(hwnd,"0.bmp");
}

void GameRun()
{
	BitBlt(g_mainDC,0,0,640,480,g_bmpdc,0,0,SRCCOPY);
	Rectangle(g_mainDC,g_hero.x,g_hero.y,g_hero.x + 20,g_hero.y + 20);

	if(GetAsyncKeyState(VK_UP) & 0x8000)
		g_hero.y -= 5;
	if(GetAsyncKeyState(VK_DOWN) & 0x8000)
		g_hero.y += 5;
	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
		g_hero.x -= 5;
	if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
		g_hero.x += 5;
	Sleep(33);
}

void GameEnd(HWND hwnd)
{
	ReleaseDC(hwnd,g_mainDC);
	DeleteBmpDC(g_bmpdc);
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
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "八班";
	RegisterClass(&wc);

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	RECT r = 
	{
		(sw - 640) / 2,
		(sh - 480) / 2,
		(sw - 640) / 2 + 640,
		(sh - 480) / 2 + 480
	};

	AdjustWindowRect(&r,WS_OVERLAPPED | WS_CAPTION
		|WS_SYSMENU,FALSE);

	HWND hWnd = CreateWindow(wc.lpszClassName,
							 "更适合游戏的循环",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
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

	//查看当前消息队列中的队头消息，
	//最后的参数可以指定是否删除得到的
	//队头消息,无论有没有消息，PeekMessage
	//都立刻返回，只不过，有消息返回真
	//没有消息返回假
	//PeekMessage(
 //   LPMSG lpMsg,//用于得到消息的结构体地址
 //   HWND hWnd,//指定得到消息的窗口，为0则表示得到本线程的所有窗口消息
 //   UINT wMsgFilterMin,//消息过滤的是下限
 //   UINT wMsgFilterMax,//消息过滤的是上限
 //   UINT wRemoveMsg);//PM_REMOVE表示移除得到的队头消息,PM_NOREMOVE表示不移除

	GameInit(hWnd);
	MSG msg = {};
	while(msg.message != WM_QUIT)
	{
		//如果有消息就处理消息
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//如果没有消息且窗口是激活状态就处理游戏循环
		else if(g_Act)
			GameRun();
		else
			WaitMessage();
	}

	GameEnd(hWnd);

	return 1;
}