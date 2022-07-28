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

#define _R 32 //半径
#define _SPEED 10.0f //速率
#define _SPEED_SUB 0.1f //速率
CVector2 pos; //位置
CVector2 speed; //速度

struct _SEGMENT
{
	CVector2 v[2];
};
std::vector<_SEGMENT> segments; //线段表

//球和线段的碰撞
bool Collide(CVector2& pos, CVector2& speed, CVector2& v0, CVector2& v1, CVector2& jd)
{
	//得到之前的位置
	CVector2 pre_pos = pos - speed;

	//得到相关的三根向量
	CVector2 u1 = pre_pos - v0;
	CVector2 u2 = pos - v0;
	CVector2 u3 = v1 - v0;

	//扩充为三维向量
	float w1[] = {u1.x, u1.y, 0.0f};
	float w2[] = {u2.x, u2.y, 0.0f};
	float w3[] = {u3.x, u3.y, 0.0f};

	//得到叉乘的z值
	float z1 = u3.x * u1.y - u3.y * u1.x;
	float z2 = u3.x * u2.y - u3.y * u2.x;

	//如果同号那么pos和pre_pos还在线段v0-v1的同侧
	if (z1 * z2 >= 0.0f)
		return false;
	
	//得到两条直线（y=kx+b）
	float k1 = (pos.y - pre_pos.y) / (pos.x - pre_pos.x);
	float b1 = pos.y - k1 * pos.x;
	float k2 = (v1.y - v0.y) / (v1.x - v0.x);
	float b2 = v0.y - k2 * v0.x;

	//得到两条直线的交点
	//y=k1x+b1
	//y=k2x+b2
	float x = (b2 - b1) / (k1 - k2);

	jd.x = x;
	jd.y = k1 * x + b1;

	//得到线段的x最值
	float minx = v0.x < v1.x ? v0.x : v1.x;
	float maxx = v0.x > v1.x ? v0.x : v1.x;

	return x >= minx && x <= maxx;
}

void Rebound(CVector2& pos, CVector2& speed, CVector2& v0, CVector2& v1)
{
	CVector2 jd;
	bool b = Collide(pos, speed, v0, v1, jd);
	if (b)
	{
		pos = jd - speed.Normalize();
		CVector2 v = v0 - v1;
		CVector2 u = speed.Projection(v);
		CVector2 w = speed - u;
		speed = -w + u;
	}
}

void GameInit(HWND hwnd)
{
	g_MainDC = GetDC(hwnd);
	g_BackDC = CreateCompatibleDC(g_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(g_MainDC, _CLIENT_W, _CLIENT_H);
	DeleteObject(SelectObject(g_BackDC,hbmp));
	DeleteObject(hbmp);

	srand(time(0));
}

void GameRun(HWND hwnd)
{
	//绘制
	BitBlt(g_BackDC, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	Ellipse(g_BackDC, pos.x - _R, pos.y - _R, pos.x + _R, pos.y + _R);
	for (int i = 0; i < segments.size(); ++i)
	{
		MoveToEx(g_BackDC, segments[i].v[0].x, segments[i].v[0].y, 0);
		LineTo(g_BackDC, segments[i].v[1].x, segments[i].v[1].y);
	}

	BitBlt(g_MainDC, 0, 0, _CLIENT_W, _CLIENT_H, g_BackDC, 0, 0, SRCCOPY);

	//减小速度
	if (!_IS_ZERO(speed.Length()))
	{
		pos += speed;

		for (int i = 0; i < segments.size(); ++i)
			Rebound(pos, speed, segments[i].v[0], segments[i].v[1]);

		float speed_len = speed.Length();
		CVector2 speed_nor = speed.Normalize();
		speed_len -= _SPEED_SUB;
		if (speed_len <= 0.0f)
			speed.Set();
		else
			speed = speed_len * speed_nor; //标量*向量
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(hwnd, &p);
		if (p.x >= 0 && p.x < _CLIENT_W && p.y >= 0 && p.y < _CLIENT_H)
		{
			CVector2 dir = CVector2(p.x, p.y) - pos;
			speed = dir.Normalize();
			speed *= _SPEED;
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 1)
	{
		_SEGMENT s;
		s.v[0].Set(rand() % _CLIENT_W, rand() % _CLIENT_H);
		s.v[1].Set(rand() % _CLIENT_W, rand() % _CLIENT_H);
		segments.push_back(s);
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