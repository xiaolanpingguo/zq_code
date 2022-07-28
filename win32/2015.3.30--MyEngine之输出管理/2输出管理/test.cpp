#include <windows.h>
#include "GameOutput.h"

HWND g_hWnd;
BOOL g_Act = TRUE;
CGameOutput* go;

void GameInit()
{
	go = new CGameOutput(g_hWnd);
	go->LoadBmp("0.bmp");
}

void GameRun()
{
	go->Begin();
	go->DrawLine(0,0,100,200);
	go->DrawLine(100,0,0,200,RGB(255,0,0));
	go->DrawLine(0,100,100,100,RGB(255,0,255),5);
	go->DrawRectangle1(220,220,280,280,RGB(0,255,0));
	go->DrawRectangle2(250,0,400,50,RGB(0,255,255),RGB(255,255,0));
	go->DrawEllipse1(0,0,300,400,RGB(0,0,255));
	go->DrawEllipse2(150,150,250,250,RGB(255,0,255),RGB(0,255,0));

	go->DrawBmp("0.bmp",400,100,40,70,0,0);
	go->DrawBmp("0.bmp",440,150,40,70,0,0);
	go->End();
	Sleep(33);
}

void GameEnd()
{
	delete go;
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
	g_hWnd = CreateWindow(wc.lpszClassName,
							 "输出管理",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	ShowWindow(g_hWnd,nCmdShow);
	UpdateWindow(g_hWnd);
	GameInit();
	MSG msg = {};
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(g_Act)
		{
			GameRun();
		}
		else
		{
			WaitMessage();
		}
	}

	GameEnd();
	return 1;
}