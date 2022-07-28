#include <windows.h>
#include "resource.h"
#include <string>
HWND dlg;

RECT g_rect = {100,100,400,400};
POINT start;
bool g_bButtonDown = false;

COLORREF c = RGB(0,0,0);
LOGFONT lf;

std::string s;

INT_PTR CALLBACK DialogProc(HWND hwnd,//产生消息的窗口
							UINT uMsg,//消息类型
							WPARAM wParam,//消息附加参数1
							LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
			return 1;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
			{
				switch(LOWORD(wParam))
				{
				case IDC_BUTTON1:
					{
						COLORREF custColor[16] = {};
						CHOOSECOLOR cc = {};
						cc.lStructSize = sizeof(cc);
						cc.hwndOwner = hwnd;
						cc.lpCustColors = custColor;
						if(IDOK == ChooseColor(&cc))
						{
							c = cc.rgbResult;
							InvalidateRect(GetParent(hwnd),0,TRUE);
						}
						break;
					}
				case IDC_BUTTON2:
					{
						CHOOSEFONT cf = {};
						cf.lStructSize = sizeof(cf);
						cf.hwndOwner = hwnd;
						cf.lpLogFont = &lf;
						cf.Flags = CF_SCREENFONTS;

						if(IDOK == ChooseFont(&cf))
						{
							InvalidateRect(GetParent(hwnd),0,TRUE);
						}
						break;
					}
				case IDCANCEL:
					{
						ShowWindow(dlg,SW_HIDE);
						break;
					}
				}
			}
			else if(HIWORD(wParam) == EN_CHANGE)
			{
				char buf[1024];
				HWND edit = GetDlgItem(hwnd,IDC_EDIT1);
				GetWindowTextA(edit,buf,1024);
				s = buf;
				InvalidateRect(GetParent(hwnd),0,TRUE);
			}
			return 1;
		}
	}
	return 0;
}


//窗口消息函数，本函数将被操作系统调用
__w64 long __stdcall WindowProc(HWND hwnd,//产生消息的窗口
								unsigned int uMsg,//消息类型
								__w64 unsigned int wParam,//消息附加参数1
								__w64 long lParam)//消息附加参数2
{
	switch(uMsg)
	{
	case WM_CREATE:
		{
			HDC hdc = GetDC(hwnd);

			HFONT f = (HFONT)GetCurrentObject(hdc,OBJ_FONT);

			GetObject(f,sizeof(lf),&lf);

			ReleaseDC(hwnd,hdc);
			return 0;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			start.x = LOWORD(lParam);
			start.y = HIWORD(lParam);
			g_bButtonDown = true;
			return 0;
		}
	case WM_LBUTTONUP:
		{
			g_bButtonDown = false;
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			ShowWindow(dlg,SW_SHOW);
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			if(g_bButtonDown && start.x != LOWORD(lParam) && start.y != HIWORD(lParam))
			{
				g_rect.left = start.x < LOWORD(lParam) ? start.x : LOWORD(lParam);
				g_rect.top = start.y < HIWORD(lParam) ? start.y : HIWORD(lParam);

				g_rect.right = start.x > LOWORD(lParam) ? start.x : LOWORD(lParam);
				g_rect.bottom = start.y > HIWORD(lParam) ? start.y : HIWORD(lParam);

				InvalidateRect(hwnd,0,TRUE);
			}
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			Rectangle(hdc,g_rect.left,g_rect.top,g_rect.right,g_rect.bottom);

			HFONT f1 = CreateFontIndirect(&lf);

			HFONT f2 = (HFONT)SelectObject(hdc,f1);

			SetTextColor(hdc,c);

			DrawTextA(hdc,s.c_str(),s.length(),&g_rect,DT_WORDBREAK);

			SelectObject(hdc,f2);

			DeleteObject(f1);


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
	wc.lpszMenuName = 0;
	wc.lpszClassName = "八班";
	RegisterClass(&wc);
	HWND hWnd = CreateWindow(wc.lpszClassName,
							 "字体",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	dlg = CreateDialog(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),hWnd,DialogProc);


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