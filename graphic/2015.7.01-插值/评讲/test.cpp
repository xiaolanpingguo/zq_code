#include <windows.h>
#include <vector>
#include <time.h>
#include "Vector2.h"
#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

BOOL g_Act = TRUE;//窗口激活标志

HDC g_MainDC;
HDC g_BackDC;

//英雄
CVector2 pos;
CVector2 dir;

//激光
struct _DOT
{
	CVector2 pos;
	CVector2 speed;
};
std::vector<std::vector<_DOT>> laser; //激光表

void GameInit(HWND hwnd)
{
	g_MainDC = GetDC(hwnd);
	g_BackDC = CreateCompatibleDC(g_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_MainDC, _CLIENT_W, _CLIENT_H);
	DeleteObject(SelectObject(g_BackDC,hbmp));
	DeleteObject(hbmp);

	pos.Set(_CLIENT_W / 2, _CLIENT_H / 2);
}

void GameRun(HWND hwnd)
{
	//绘制
	BitBlt(g_BackDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	//得到朝向
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);
	CVector2 v(p.x, p.y);
	dir = (v - pos).Normalize();

	//绘制英雄
	CVector2 u = pos + (40.0f * dir);
	MoveToEx(g_BackDC, u.x, u.y, 0);
	LineTo(g_BackDC, pos.x, pos.y);
	Ellipse(g_BackDC, pos.x - 10, pos.y - 10, pos.x + 10, pos.y + 10);

	//绘制激光
	for (int i = 0; i < laser.size(); ++i)
	{
		for (int j = 0; j < laser[i].size() - 1; ++j)
		{
			MoveToEx(g_BackDC, laser[i][j].pos.x, laser[i][j].pos.y, 0);
			LineTo(g_BackDC, laser[i][j + 1].pos.x, laser[i][j + 1].pos.y);
		}
	}

	BitBlt(g_MainDC, 0, 0, _CLIENT_W, _CLIENT_H, g_BackDC, 0, 0, SRCCOPY);

	//激光运动
	for (int i = 0; i < laser.size(); ++i)
	{
		 //第一个点移动
		laser[i][0].pos += laser[i][0].speed;

		//是否和墙面发射碰撞
		if (laser[i][0].pos.x < 0 || laser[i][0].pos.x >= _CLIENT_W)
		{
			if (laser[i][0].pos.x < 0)
				laser[i][0].pos.x = 1;
			else
				laser[i][0].pos.x = _CLIENT_W - 2;

			laser[i][0].speed.x = -laser[i][0].speed.x;
			_DOT d;
			d.pos = laser[i][0].pos;
			d.speed.Set();
			laser[i].insert(laser[i].begin() + 1, d);
		}
		else if (laser[i][0].pos.y < 0 || laser[i][0].pos.y >= _CLIENT_H)
		{
			if (laser[i][0].pos.y < 0)
				laser[i][0].pos.y = 1;
			else
				laser[i][0].pos.y = _CLIENT_H - 2;

			laser[i][0].speed.y = -laser[i][0].speed.y;
			_DOT d;
			d.pos = laser[i][0].pos;
			d.speed.Set();
			laser[i].insert(laser[i].begin() + 1, d);
		}

		//最后的点的移动
		if (_IS_ZERO(laser[i].back().speed.Length()))
		{
			float len = 0.0f;
			for (int j = 0; j < laser[i].size() - 1; ++j)
			{
				len += (laser[i][j].pos - laser[i][j + 1].pos).Length();
			}
			if (len > 100.0f)
			{
				laser[i].back().speed
					= 
				laser[i][laser[i].size() - 2].pos - laser[i].back().pos;
				laser[i].back().speed = laser[i].back().speed.Normalize() * 5.0f;
			}
		}
		else
		{
			laser[i].back().pos += laser[i].back().speed;
			
			//是否和墙面发射碰撞
			if (laser[i].back().pos.x < 0 || laser[i].back().pos.x >= _CLIENT_W)
			{
				if (laser[i].back().pos.x < 0)
					laser[i].back().pos.x = 1;
				else
					laser[i].back().pos.x = _CLIENT_W - 2;

				laser[i].back().speed.x = -laser[i].back().speed.x;
				laser[i].erase(laser[i].end() - 2);
			}
			else if (laser[i].back().pos.y < 0 || laser[i].back().pos.y >= _CLIENT_H)
			{
				if (laser[i].back().pos.y < 0)
					laser[i].back().pos.y = 1;
				else
					laser[i].back().pos.y = _CLIENT_H - 2;

				laser[i].back().speed.y = -laser[i].back().speed.y;
				laser[i].erase(laser[i].end() - 2);
			}
		}
	}

	//移动英雄
	if (GetAsyncKeyState('W') & 0x8000)
		pos.y -= 5;
	if (GetAsyncKeyState('S') & 0x8000)
		pos.y += 5;
	if (GetAsyncKeyState('A') & 0x8000)
		pos.x -= 5;
	if (GetAsyncKeyState('D') & 0x8000) //10000000 00000000
		pos.x += 5;

	//发射激光
	if (GetAsyncKeyState(VK_LBUTTON) & 1) //00000000 00000001
	{
		_DOT front;
		front.pos = pos + (60.0f * dir);
		front.speed = 5.0f * dir;

		_DOT back;
		back.pos = pos + (60.0f * dir);
		back.speed.Set();

		std::vector<_DOT> v;
		v.push_back(front);
		v.push_back(back);
		laser.push_back(v);
	}
}

void GameEnd(HWND hwnd)
{
	DeleteDC(g_BackDC);
	ReleaseDC(hwnd, g_MainDC); 
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

class A
{
public:
	A(){}
	A(int a){}
	A(int a, int b){}
};

int __stdcall WinMain(HINSTANCE hInstance,//应用程序实例句柄
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	int aa = 1; //变量=常量
	A a2 = A(); //变量=常量（通过构造函数1构造出来的类常量）
	A a3 = A(1); //变量=常量（通过构造函数2构造出来的类常量）
	A a4 = A(1,2); //变量=常量（通过构造函数3构造出来的类常量）

	//01)填充一个窗口类别的结构体
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "3dtest";
	RegisterClass(&wc);

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	RECT r = 
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		(sw - _CLIENT_W) / 2 + _CLIENT_W,
		(sh - _CLIENT_H) / 2 + _CLIENT_H
	};

	//得到窗口风格
	//已知字节????????和风格00001000
	//那么(字节&~风格)就为
	//????????
	//11110111
	//--------
	//????0???
	int ws = (WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME) & ~WS_MAXIMIZEBOX;

	AdjustWindowRect(&r, ws, FALSE);

	HWND hWnd = CreateWindow(
		wc.lpszClassName,
		"向量测试",//窗口标题栏文字
		ws,//窗口风格
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

	GameInit(hWnd);

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
			int bt = GetTickCount();
			GameRun(hWnd);
			int at = GetTickCount() - bt;
			Sleep(at < _SLEEP_TIME ? _SLEEP_TIME - at : 1);
		}
		else
			WaitMessage();
	}

	GameEnd(hWnd);

	return 1;
}