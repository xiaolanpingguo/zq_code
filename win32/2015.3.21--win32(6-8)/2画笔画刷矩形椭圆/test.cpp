#include <windows.h>
#include "resource.h"
#include <list>
//1 矩形
//2 椭圆
//3 画笔
//4 画刷

//记录是否是矩形，真为矩形，假为椭圆
bool g_bJx = true;

//画笔画刷的颜色
COLORREF g_pen = RGB(0,0,0);
COLORREF g_b = RGB(255,255,255);

//记录起始点
POINT g_start;

struct TX
{
	RECT r;
	bool jx;
	COLORREF p;
	COLORREF b;
};

std::list<TX>  g_tx;

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
	case WM_LBUTTONDOWN:
		{
			g_start.x = LOWORD(lParam);
			g_start.y = HIWORD(lParam);
			return 0;
		}
	case WM_LBUTTONUP:
		{
			if(g_start.x != LOWORD(lParam)
			&& g_start.y != HIWORD(lParam))
			{
				TX t;
				t.r.left = g_start.x < LOWORD(lParam) ? g_start.x: LOWORD(lParam);
				t.r.top = g_start.y < HIWORD(lParam) ? g_start.y : HIWORD(lParam);
				
				t.r.right = g_start.x < LOWORD(lParam) ? LOWORD(lParam) : g_start.x;
				t.r.bottom = g_start.y < HIWORD(lParam) ? HIWORD(lParam): g_start.y;
				
				t.jx = g_bJx;

				t.p = g_pen;

				t.b = g_b;

				g_tx.push_back(t);

				InvalidateRect(hwnd,0,TRUE);
			}
			return 0;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case ID_40001:g_bJx = true;break;
			case ID_40002:g_bJx = false;break;
			case ID_40003:
			case ID_40004:
				{
					COLORREF custColor[16] = {};
					CHOOSECOLOR cc = {};
					cc.lStructSize = sizeof(cc);
					cc.hwndOwner = hwnd;
					cc.lpCustColors = custColor;

					if(IDOK == ChooseColor(&cc))
					{
						if(LOWORD(wParam) == ID_40003)
							g_pen = cc.rgbResult;
						else
							g_b = cc.rgbResult;
					}
				}
				break;
			}
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			std::list<TX>::iterator i;
			for(i = g_tx.begin(); i != g_tx.end(); ++i)
			{
				HPEN p1 = CreatePen(PS_SOLID,1,i->p);
				HBRUSH b1 = CreateSolidBrush(i->b);

				HPEN p2 = (HPEN)SelectObject(hdc,p1);
				HBRUSH b2 = (HBRUSH)SelectObject(hdc,b1);

				if(i->jx)
					Rectangle(hdc,i->r.left,i->r.top,i->r.right,i->r.bottom);
				else
					Ellipse(hdc,i->r.left,i->r.top,i->r.right,i->r.bottom);

				SelectObject(hdc,p2);
				SelectObject(hdc,b2);
				DeleteObject(p1);
				DeleteObject(b1);
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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = "八班";
	RegisterClass(&wc);
	HWND hWnd = CreateWindow(wc.lpszClassName,
							 "画笔画刷矩形椭圆",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	ShowWindow(hWnd,nCmdShow);
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