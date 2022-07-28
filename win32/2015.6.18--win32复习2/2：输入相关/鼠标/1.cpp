#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <iostream>

//#define _WIN32_WINNT 0x0400
//#ifndef _WIN32_WINNT
//#define _WIN32_WINNT 0x0300
//#endif

#define _CLIENT_W 640
#define _CLIENT_H 480

//WM_LBUTTONDOWN（鼠标左键按下）、WM_LBUTTONUP（鼠标左键抬起）、WM_LBUTTONDBLCLK（鼠标左键双击）
//WM_MBUTTONDOWN（鼠标中键按下）、WM_MBUTTONUP（鼠标中键抬起）、WM_MBUTTONDBLCLK（鼠标中键双击）
//WM_RBUTTONDOWN（鼠标右键按下）、WM_RBUTTONUP（鼠标右键抬起）、WM_RBUTTONDBLCLK（鼠标右键双击）
//WM_MOUSEWHEEL（鼠标滚轮滚动消息）
//WM_MOUSEMOVE（光标在客户区移动消息）
//只要是鼠标相关消息，那么lParam参数中都放有光标的坐标数据

//MessageBox
//OutputDebugString
//SetWindowText

LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg, //消息值
							WPARAM wParam, //消息的附加参数1
							LPARAM lParam) //消息的附加参数2
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			//鼠标左键在本窗口的客户区按下的时候触发本消息

			//本消息中，光标相对于本窗口客户区的左上角
			//的相对位置是放在了lParam参数中的，放的方
			//法是XX XX YY YY，而LOWORD、HIWORD宏可以
			//得到一个4字节数据中的前两个字节和后两个
			//字节的数据
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			char buf[64];
			sprintf_s(buf, 64, "[%d,%d]", x, y);
			MessageBox(hwnd, buf, "点中位置", MB_OK);

			return 0;
		}

	case WM_RBUTTONUP:
		{
			//鼠标右键在本窗口的客户区抬起的时候触发本消息

			//本消息中，lParam也是存储的光标当前的位置
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			char buf[64];
			sprintf_s(buf, 64, "[%d,%d]", x, y);
			MessageBox(hwnd, buf, "抬起位置", MB_OK);

			return 0;
		}

		//如果要希望本窗口可以接受双击消息，那么都必须
		//在窗口类别结构体的风格中加上CS_DBLCLKS，这个
		//风格表示允许双击
	case WM_RBUTTONDBLCLK:
		{
			Beep(500, 200);
			return 0;
		}
	case WM_MOUSEWHEEL:
		{
			//注意本消息需要_WIN32_WINNT这宏的版
			//本号要大于等于0x0400，我们可以在包
			//含Windows.h之前定义这个宏
			//往前还是往后滚动可以通过下面的代码
			//来判断，这个值是放在wParam的高字部
			//分，一个字WORD就是两个字节，一个双
			//字DWORD就是两个字也是四个字节
			if (WHEEL_DELTA == HIWORD(wParam))
				OutputDebugStringA("往前滚动\n");
			else if (-WHEEL_DELTA == (short)HIWORD(wParam))
				OutputDebugStringA("往后滚动\n");

			return 0;
		}
	case WM_MOUSEMOVE:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			char buf[64];
			sprintf_s(buf, 64, "[%d,%d]", x, y);

			//设置指定窗口中标题栏的文字
			SetWindowTextA(hwnd, buf);

			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "123abc";

	RegisterClass(&wc);

	//可以根据客户区大小来计算窗口大小
	int sw = GetSystemMetrics(SM_CXSCREEN); //得到桌面的宽
	int sh = GetSystemMetrics(SM_CYSCREEN); //得到桌面的高
	RECT cr //cr得到客户区的位置、尺寸
		=
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		(sw - _CLIENT_W) / 2 + _CLIENT_W,
		(sh - _CLIENT_H) / 2 + _CLIENT_H
	};
	//根据传入的客户区位置、尺寸来计算窗口应该有的位置、尺寸
	AdjustWindowRect(
		&cr, //客户区矩形，本函数执行完毕之后会填入窗口矩形
		WS_OVERLAPPEDWINDOW, //窗口风格
		FALSE); //有无菜单

	HWND hwnd = CreateWindowA(
		wc.lpszClassName, //使用的窗口类别结构体的名字
		"hello world", //窗口标题栏文字
		WS_OVERLAPPEDWINDOW, //窗口风格
		cr.left, //窗口左上角x坐标
		cr.top, //窗口左上角y坐标
		cr.right - cr.left, //窗口宽
		cr.bottom - cr.top, //窗口高
		HWND_DESKTOP, //父窗口，一般来说填写桌面窗口
		0, //菜单句柄，不用就填写0
		wc.hInstance, //应用程序实例句柄
		0); //保留参数

	//可以得到客户区的尺寸
	RECT r; //矩形结构体：左上角（left，top），右下角（right，bottom）
	GetClientRect(hwnd, &r);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}