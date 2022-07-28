#include <windows.h>
#include <iostream>

#pragma comment(lib, "msimg32.lib")

#define _MAP_W 16
#define _MAP_H 12
#define _GRID_W 41 //格子的宽、高处理为奇数是为了计算格子的中心点
#define _GRID_H 41
#define _CLIENT_W (_MAP_W * _GRID_W)
#define _CLIENT_H (_MAP_H * _GRID_H)
#define _SLEEP_TIME 33

HWND g_hWnd;
BOOL g_AppActive = TRUE;

void GameInit();
void GameRun();
void GameEnd();

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
			g_AppActive = (BOOL)wParam;
			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "Test";
	RegisterClass(&wc);

	RECT r
		=
	{
		(GetSystemMetrics(SM_CXSCREEN) - _CLIENT_W) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - _CLIENT_H) / 2,
		(GetSystemMetrics(SM_CXSCREEN) - _CLIENT_W) / 2 + _CLIENT_W,
		(GetSystemMetrics(SM_CYSCREEN) - _CLIENT_H) / 2 + _CLIENT_H
	};

	AdjustWindowRect(&r, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	g_hWnd = CreateWindow(
		wc.lpszClassName,
		"简单脚本测试",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		r.left,
		r.top,
		r.right - r.left,
		r.bottom - r.top,
		HWND_DESKTOP,
		0,
		wc.hInstance,
		0);

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	GameInit();

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (g_AppActive)
			GameRun();
		else
			WaitMessage();
	}

	GameEnd();

	return 1;
}

HDC mainDC;
HDC backDC;
HBITMAP backBMP;

void Init();
void Run();
void End();

void GameInit()
{
	mainDC = GetDC(g_hWnd);
	backDC = CreateCompatibleDC(mainDC);
	backBMP = CreateCompatibleBitmap(mainDC, _CLIENT_W, _CLIENT_H);
	SelectObject(backDC, backBMP);
	SetBkMode(backDC, TRANSPARENT);

	Init();
}

void GameRun()
{
	//得到进入系统一瞬间到目前经历的毫秒
	int bt = GetTickCount();
	BitBlt(backDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	Run();

	//得到本次游戏循环经历的时间
	BitBlt(mainDC, 0, 0, _CLIENT_W, _CLIENT_H, backDC, 0, 0, SRCCOPY);
	int et = GetTickCount() - bt;
	if (et < _SLEEP_TIME)
		Sleep(_SLEEP_TIME - et);
	else
		Sleep(10);
}

void GameEnd()
{
	End();

	DeleteObject(backBMP);
	DeleteDC(backDC);
	ReleaseDC(g_hWnd, mainDC);
}

#include "FindPathW.h"
#include <vector>
#include <string>



typedef struct _OBJECT
{
	int x, y; //物体中心点
	int wd2, hd2; //物体宽、高的一半
	int speed; //移动速度
	std::vector<int> path; //路径
}OBJECT;

std::vector<OBJECT> obj_vec; //物体表

void ObjectMove(OBJECT* obj);

void DrawRect(int x1, int y1, int x2, int y2, COLORREF c)
{
	HBRUSH b1 = CreateSolidBrush(c);
	HBRUSH b0 = (HBRUSH)SelectObject(backDC, b1);
	Rectangle(backDC, x1, y1, x2, y2);
	SelectObject(backDC, b0);
	DeleteObject(b1);
}

char map[_MAP_W * _MAP_H] = 
{
	0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,
	1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,
	1,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1,
	1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,
	1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,
	0,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,
	1,1,0,1,1,1,1,0,0,0,0,0,1,0,0,1,
	1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,
	1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1
};

void Init()
{
	_OBJECT obj = {60, 12, 7, 7, 5};
	obj_vec.push_back(obj);
}

void Run()
{
	//绘制地图
	for (int i = 0; i < _MAP_W * _MAP_H; ++i)
	{
		int x = (i % _MAP_W) * _GRID_W;
		int y = (i / _MAP_W) * _GRID_H;
		DrawRect(x, y, x + _GRID_W, y + _GRID_H, map[i] == 0 ? RGB(127, 127, 127) : RGB(255, 255, 255));
		char buf[32];
		sprintf_s(buf, 32, "%d", i);
		TextOutA(backDC, x, y, buf, (int)strlen(buf));
	}

	//绘制物体
	for (int i = 0; i < (int)obj_vec.size(); ++i)
	{
		DrawRect(
			obj_vec[i].x - obj_vec[i].wd2,
			obj_vec[i].y - obj_vec[i].hd2,
			obj_vec[i].x + obj_vec[i].wd2,
			obj_vec[i].y + obj_vec[i].hd2,
			RGB(255, 0, 0));
	}

	//移动
	for (int i = 0; i < (int)obj_vec.size(); ++i)
		ObjectMove(&obj_vec[i]);

	//寻路
	if (GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		//得到当前光标在桌面上面的坐标
		POINT p;
		GetCursorPos(&p);

		//将桌面坐标转换为窗口客户区坐标
		ScreenToClient(g_hWnd, &p);

		//点中客户区
		if (p.x >= 0 && p.x < _CLIENT_W && p.y >= 0 && p.y < _CLIENT_H)
		{
			//点中了可以移动的位置
			int dest = (p.x / _GRID_W) + (p.y / _GRID_H) * _MAP_W;
			if (map[dest] == 1)
			{
				int cur = (obj_vec[0].x / _GRID_W) + (obj_vec[0].y / _GRID_H) * _MAP_W;
				FindPathW(map, _MAP_W, _MAP_H, cur, dest, &obj_vec[0].path);
			}
		}
	}
}

void End()
{
	
}

#define _JDZ(a) ((a)<0?(-(a)):(a))

void ObjectMove(OBJECT* obj)
{
	//当前无路不用移动了
	if (obj->path.empty())
		return;

	//得到当前的目标格子
	int ti = obj->path.back();

	//得到目标格子的左上、右下角
	int gx1 = (ti % _MAP_W) * _GRID_W;
	int gy1 = (ti / _MAP_W) * _GRID_H;
	int gx2 = gx1 + _GRID_W - 1;
	int gy2 = gy1 + _GRID_H - 1;

	//得到物体的的左上、右下角
	int ox1 = obj->x - obj->wd2;
	int oy1 = obj->y - obj->hd2;
	int ox2 = obj->x + obj->wd2;
	int oy2 = obj->y + obj->hd2;

	//当前物体是否已经在目标格子
	if (ox1 >= gx1 && ox2 <= gx2 && oy1 >= gy1 && oy2 <= gy2)
	{
		//删除掉当前目标格子
		obj->path.pop_back();
		return;
	}

	//得到格子的中心点
	int gcx = (gx1 + gx2) / 2;
	int gcy = (gy1 + gy2) / 2;

	//移动

	//物体在格子的竖方向
	if (ox1 >= gx1 && ox2 <= gx2)
	{
		//上方
		if (obj->y < gcy)
			obj->y += obj->speed;
		//下方
		else
			obj->y -= obj->speed;
	}
	//物体在格子的横方向
	else if (oy1 >= gy1 && oy2 <= gy2)
	{
		//左方
		if (obj->x < gcx)
			obj->x += obj->speed;
		//下方
		else
			obj->x -= obj->speed;
	}
	else
	{
		//判断当前物体中心点是否是在
		//目标格子的对角线延长线上面
		if (_JDZ(gcx - obj->x) == _JDZ(gcy - obj->y))
		{
			//4种情况讨论
			if (obj->x <= gcx && obj->y <= gcy)
			{
				obj->x += obj->speed;
				obj->y += obj->speed;
			}
			else if (obj->x <= gcx && obj->y >= gcy)
			{
				obj->x += obj->speed;
				obj->y -= obj->speed;
			}
			else if (obj->x >= gcx && obj->y >= gcy)
			{
				obj->x -= obj->speed;
				obj->y -= obj->speed;
			}
			else
			{
				obj->x -= obj->speed;
				obj->y += obj->speed;
			}
		}
		else
		{
			//8种情况讨论
			
			//6、7象限
			if (obj->x <= gcx && obj->y <= gcy)
			{
				//6象限
				if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
				{
					int x = obj->x;
					obj->x += obj->speed;
					if (_JDZ(gcx - obj->x) < _JDZ(gcy - obj->y))
						obj->x = x + (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
				//7象限
				else
				{
					int y = obj->y;
					obj->y += obj->speed;
					if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
						obj->y = y + (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
			}
			//4、5象限
			else if (obj->x <= gcx && obj->y >= gcy)
			{
				//5象限
				if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
				{
					int x = obj->x;
					obj->x += obj->speed;
					if (_JDZ(gcx - obj->x) < _JDZ(gcy - obj->y))
						obj->x = x + (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
				//4象限
				else
				{
					int y = obj->y;
					obj->y -= obj->speed;
					if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
						obj->y = y - (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
			}
			//2、3象限
			else if (obj->x >= gcx && obj->y >= gcy)
			{
				//2象限
				if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
				{
					int x = obj->x;
					obj->x -= obj->speed;
					if (_JDZ(gcx - obj->x) < _JDZ(gcy - obj->y))
						obj->x = x - (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
				//3象限
				else
				{
					int y = obj->y;
					obj->y -= obj->speed;
					if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
						obj->y = y - (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
			}
			//0、1象限
			else
			{
				//1象限
				if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
				{
					int x = obj->x;
					obj->x -= obj->speed;
					if (_JDZ(gcx - obj->x) < _JDZ(gcy - obj->y))
						obj->x = x - (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
				//0象限
				else
				{
					int y = obj->y;
					obj->y += obj->speed;
					if (_JDZ(gcx - obj->x) > _JDZ(gcy - obj->y))
						obj->y = y + (_JDZ(_JDZ(gcx - obj->x) - _JDZ(gcy - obj->y)) - 1);
				}
			}
		}
	}
}