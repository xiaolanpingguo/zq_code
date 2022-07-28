#include <windows.h>
#include <iostream>
#include "GameScript.h"

#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 800
#define _CLIENT_H 600
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

//游戏脚本类对象
CGameScript gs;

void Init()
{
	gs.LoadScript("TestTmp");
}

void Run()
{
	//系统运行
	gs.Run();

	//绘制物体
	std::vector<CGameScript::_OBJECT>* obj = gs.GetObjects();
	for (std::vector<CGameScript::_OBJECT>::iterator it = obj->begin(); it != obj->end(); ++it)
	{
		if (it->type == 0)
			Rectangle(backDC, it->x - it->radius, it->y - it->radius, it->x + it->radius, it->y + it->radius);
		else
			Ellipse(backDC, it->x - it->radius, it->y - it->radius, it->x + it->radius, it->y + it->radius);
	}
}

void End()
{

}