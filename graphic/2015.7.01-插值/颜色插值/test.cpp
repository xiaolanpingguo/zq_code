#include <windows.h>
#include <time.h>
#pragma comment(lib, "msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

BOOL g_Act = TRUE;//窗口激活标志

HDC g_MainDC;
HDC g_BackDC;
HWND g_hWnd[5];
COLORREF c[3];
float ams, cms; //总持续时间、当前时间

COLORREF slerp_color(COLORREF c0, COLORREF c1, float a, float c)
{
	float bl = c / a;
	int cc0[] = {GetRValue(c0), GetGValue(c0), GetBValue(c0)};
	int cc1[] = {GetRValue(c1), GetGValue(c1), GetBValue(c1)};
	int cc2[]
	=
	{
		(cc1[0] - cc0[0]) * bl + cc0[0],
		(cc1[1] - cc0[1]) * bl + cc0[1],
		(cc1[2] - cc0[2]) * bl + cc0[2],
	};
	return RGB(cc2[0], cc2[1], cc2[2]);
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
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case 1:
				{
					COLORREF cust_c[16] = {};
					CHOOSECOLOR cc = {};
					cc.lStructSize = sizeof(cc);
					cc.lpCustColors = cust_c;
					if (IDOK == ChooseColor(&cc))
					{
						c[0] = cc.rgbResult;
						InvalidateRect(g_hWnd[0], 0, TRUE);
					}
					break;
				}
			case 2:
				{
					COLORREF cust_c[16] = {};
					CHOOSECOLOR cc = {};
					cc.lStructSize = sizeof(cc);
					cc.lpCustColors = cust_c;
					if (IDOK == ChooseColor(&cc))
					{
						c[1] = cc.rgbResult;
						InvalidateRect(g_hWnd[0], 0, TRUE);
					}
					break;
				}
			case 3:
				{
					//取得源颜色和目标颜色
					if (c[0] == c[1])
					{
						MessageBoxA(g_hWnd[0], "源颜色和目标颜色相同不能插值", "提示", MB_OK);
						break;
					}

					//取得变化时间
					char buf[32] = {};
					GetDlgItemTextA(g_hWnd[0], 4, buf, 32);
					ams = atoi(buf) * 1000;
					if (ams == 0)
					{
						MessageBoxA(g_hWnd[0], "时间为0不能插值", "提示", MB_OK);
						break;
					}
					cms = 0;

					//启动颜色插值
					SetTimer(g_hWnd[0], 0, 10, 0);

					for (int i = 1; i <= 4; ++i)
						EnableWindow(g_hWnd[i], FALSE);

					break;
				}
			}

			return 0;
		}
	case WM_TIMER:
		{
			//插值1
			//c[2] = (c[1] - c[0]) * (cms / ams) + c[0];

			//插值1
			//float bl = cms / ams;
			//int c0[] = {GetRValue(c[0]), GetGValue(c[0]), GetBValue(c[0])};
			//int c1[] = {GetRValue(c[1]), GetGValue(c[1]), GetBValue(c[1])};
			//int c2[]
			//=
			//{
			//	(c1[0] - c0[0]) * bl + c0[0],
			//	(c1[1] - c0[1]) * bl + c0[1],
			//	(c1[2] - c0[2]) * bl + c0[2],
			//};
			//c[2] = RGB(c2[0], c2[1], c2[2]);

			c[2] = slerp_color(c[0], c[1], ams, cms);

			cms += 10;
			if (cms > ams)
			{
				KillTimer(g_hWnd[0], 0);
				for (int i = 1; i <= 4; ++i)
					EnableWindow(g_hWnd[i], TRUE);
			}

			InvalidateRect(g_hWnd[0], 0, TRUE);

			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC dc = BeginPaint(g_hWnd[0], &ps);

			HBRUSH b[3];
			for (int i = 0; i < 3; ++i)
				b[i] = CreateSolidBrush(c[i]);

			HBRUSH old_b = (HBRUSH)SelectObject(dc, b[0]);
			Rectangle(dc, 120, 80, 220, 240);

			SelectObject(dc, b[1]);
			Rectangle(dc, 240, 80, 340, 240);

			SelectObject(dc, b[2]);
			Rectangle(dc, 360, 80, 460, 240);

			SelectObject(dc, old_b);

			for (int i = 0; i < 3; ++i)
				DeleteObject(b[i]);

			EndPaint(g_hWnd[0], &ps);
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
	int ws = (WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME) & ~WS_MAXIMIZEBOX;
	AdjustWindowRect(&r, ws, FALSE);

	g_hWnd[0] = CreateWindow(
		wc.lpszClassName,
		"颜色插值",//窗口标题栏文字
		ws,//窗口风格
		r.left,//窗口的左上角x坐标
		r.top,//窗口的左上角y坐标
		r.right - r.left,//窗口的宽（像素）
		r.bottom - r.top,//窗口的高（像素）
		HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
		0,//窗口菜单句柄，不使用菜单填0
		wc.hInstance,//应用程序实例句柄
		0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	const char* str[] = {"源颜色", "目标颜色", "运行"};
	for (int i = 1; i <= 3; ++i)
	{
		g_hWnd[i] = CreateWindow(
			"button",
			str[i - 1],//窗口标题栏文字
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,//窗口风格
			i * 120,//窗口的左上角x坐标
			0,//窗口的左上角y坐标
			100,//窗口的宽（像素）
			60,//窗口的高（像素）
			g_hWnd[0],//父窗口窗口句柄,HWND_DESKTOP表示桌面
			(HMENU)i,//窗口菜单句柄，不使用菜单填0
			wc.hInstance,//应用程序实例句柄
			0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0
	}
	g_hWnd[4] = CreateWindow(
		"edit",
		"持续时间",//窗口标题栏文字
		WS_CHILD | WS_VISIBLE | WS_BORDER,//窗口风格
		0,//窗口的左上角x坐标
		0,//窗口的左上角y坐标
		80,//窗口的宽（像素）
		20,//窗口的高（像素）
		g_hWnd[0],//父窗口窗口句柄,HWND_DESKTOP表示桌面
		(HMENU)4,//窗口菜单句柄，不使用菜单填0
		wc.hInstance,//应用程序实例句柄
		0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	ShowWindow(g_hWnd[0], nCmdShow);
	UpdateWindow(g_hWnd[0]);

	MSG msg = {};
	while(GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}