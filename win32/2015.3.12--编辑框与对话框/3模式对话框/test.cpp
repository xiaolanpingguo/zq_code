#include <windows.h>
#include "resource.h"

//非模式对话框
//模式对话框
//通用对话框

INT_PTR __stdcall f(HWND hwndDlg,
					UINT uMsg,
					WPARAM wParam,
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
			//EndDialog退出对话框并且设置DialogBox的返回值
			if(HIWORD(wParam) == BN_CLICKED)
			{
				if(LOWORD(wParam) == IDOK)
				{
					EndDialog(hwndDlg,100);
				}
				else if(LOWORD(wParam) == IDCANCEL)
				{
					EndDialog(hwndDlg,101);
				}
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
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

	case WM_RBUTTONDOWN:
		{
			//ShowWindow(g_hWnd[1],SW_SHOW);
			return 0;
		}
	case WM_KEYDOWN:
		{
			//if(wParam == VK_F1)
			//	ShowWindow(g_hWnd[1],SW_SHOW);
			return 0;
		}
	}
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//应用程序实例句柄
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{


	//WNDCLASS wc;
	//wc.style = CS_HREDRAW|CS_VREDRAW;
	//wc.lpfnWndProc = WindowProc;
	//wc.cbClsExtra = 0;
	//wc.cbWndExtra = 0;
	//wc.hInstance = hInstance;
	//wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	//wc.hCursor = LoadCursor(0,IDC_ARROW);
	//wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	//wc.lpszMenuName = 0;
	//wc.lpszClassName = L"八班";
	//RegisterClass(&wc);
	//
	//HWND hwnd = CreateWindow(wc.lpszClassName,
	//						 L"模式对话框",//窗口标题栏文字
	//						 WS_OVERLAPPEDWINDOW,//窗口风格
	//						 CW_USEDEFAULT,//窗口的左上角x坐标
	//						 CW_USEDEFAULT,//窗口的左上角y坐标
	//						 CW_USEDEFAULT,//窗口的宽（像素）
	//						 CW_USEDEFAULT,//窗口的高（像素）
	//						 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
	//						 0,//窗口菜单句柄，不使用菜单填0
	//						 wc.hInstance,//应用程序实例句柄
	//						 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	//产生一个模式对话框
	INT_PTR r = DialogBox(hInstance,
						  MAKEINTRESOURCE(IDD_DIALOG1),
						  HWND_DESKTOP,
						  f);


	MessageBoxA(0,r == 100 ? "[确定]退出" : "[取消]退出",0,MB_OK);
	

	//ShowWindow(hwnd,nCmdShow);
	//UpdateWindow(hwnd);
	//
	//MSG msg;
	//while(GetMessage(&msg,0,0,0))
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}

	return 1;
}