#include <windows.h>
#include <time.h>
#include "FindPath.h"
#pragma comment(lib,"msimg32.lib")

#define _GRID_W 4 // 图片宽高
#define _GRID_H 4
#define _MAP_W 200 //地图数组的宽
#define _MAP_H 150
#define _MAP_S (_MAP_W * _MAP_H)
#define _CLIENT_W (_GRID_W * _MAP_W)
#define _CLIENT_H (_GRID_H * _MAP_H)
#define _ZA_NUM (_MAP_S / 30)

//地图
char map[_MAP_S] = {};

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
	case WM_LBUTTONDOWN:
		{
			POINT p = {LOWORD(lParam), HIWORD(lParam)};
			p.x /= _GRID_W;
			p.y /= _GRID_H;

			std::vector<int> path;

			//int t0 = GetTickCount();
			//FindPathW(map, _MAP_W, _MAP_H, 0, p.x + p.y * _MAP_W, &path);
			//int t1 = GetTickCount() - t0;

			//int t2 = GetTickCount();
			//FindPathD(map, _MAP_W, _MAP_H, 0, p.x + p.y * _MAP_W, &path);
			//int t3 = GetTickCount() - t2;

			int t4 = GetTickCount();
			FindPathA(map, _MAP_W, _MAP_H, 0, p.x + p.y * _MAP_W, &path);
			int t5 = GetTickCount() - t4;

			//char buf[256];
			//sprintf_s(buf, "广度：%d 深度：%d A星：%d", t1, t3, t5);
			//SetWindowTextA(hwnd, buf);

			//char buf[256];
			//sprintf_s(buf, "广度：%d A星：%d", t1, t5);
			//SetWindowTextA(hwnd, buf);

			for (int i = 0; i < path.size(); ++i)
				map[path[i]] = 2;
			
			char buf[256];
			sprintf_s(buf, "A星：%d", t5);
			SetWindowTextA(hwnd, buf);

			::InvalidateRect(hwnd, 0, TRUE);

			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			for (int i = 0; i < _MAP_S; ++i)
			{
				if (map[i] == 0)
				{
					int x = i % _MAP_W, y = i / _MAP_W;
					x *= _GRID_W;
					y *= _GRID_H;
					Rectangle(hdc, x, y, x + _GRID_W, y + _GRID_H);
				}
				else if (map[i] == 2)
				{
					int x = i % _MAP_W, y = i / _MAP_W;
					x *= _GRID_W;
					y *= _GRID_H;
					SetPixel(hdc, x, y, RGB(255, 0, 0));
				}
			}
			
			EndPaint(hwnd,&ps);
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
	srand((unsigned int)time(0));

	//初始化地图
	for (int i = 0; i < _MAP_S; ++i)
		map[i] = 1;
	for (int i = 0; i < _ZA_NUM; ++i)
		map[(rand() * rand()) % _MAP_S] = 0;

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
	wc.lpszClassName = "九班";
	RegisterClass(&wc);
	//获取桌面的宽
	int sw = GetSystemMetrics(SM_CXSCREEN);
	//获取桌面的高
	int sh = GetSystemMetrics(SM_CYSCREEN);

	RECT r = 
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		(sw - _CLIENT_W) / 2 + _CLIENT_W,
		(sh - _CLIENT_H) / 2 + _CLIENT_H
	};

	//本函数执行完毕，会将第一个参数执行的RECT设置为窗口应有的矩形
	AdjustWindowRect(&r,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,
		FALSE);//是否有菜单

	HWND hWnd = CreateWindow(wc.lpszClassName,
							 "人",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 r.left,//窗口的左上角x坐标
							 r.top,//窗口的左上角y坐标
							 r.right - r.left,//窗口的宽（像素）
							 r.bottom - r.top,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		//如果发现有WM_KEYDOWN和WM_KEYUP消息就根据当前的输入法
		//在产生一个WM_CHAR消息并投递到消息队列中
		TranslateMessage(&msg);
		//派发消息回操作系统(估计就是下面DispatchMessage来调用窗口消息函数)
		DispatchMessage(&msg);
	}
	return 1;
}