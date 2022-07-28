#include <windows.h>
#include "resource.h"

//非模式对话框
//模式对话框
//通用对话框

char buf[256];

INT_PTR __stdcall f(HWND hwndDlg,
					UINT uMsg,
					WPARAM wParam,
					LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
			HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
			SetWindowTextA(hwnd,"请输入要修改的窗口标题栏文字");
			return 1;
		}
	case WM_COMMAND:
		{
			
			if(HIWORD(wParam) == BN_CLICKED)
			{
				if(LOWORD(wParam) == IDC_BUTTON1)
				{
					HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);

					GetWindowTextA(hwnd,buf,256);

					EndDialog(hwndDlg,100);
				}
				else if(LOWORD(wParam) == IDC_BUTTON2)
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
			
			//产生一个模式对话框
			INT_PTR r = DialogBox(GetModuleHandle(0),
								  MAKEINTRESOURCE(IDD_DIALOG1),
								  hwnd,
								  f);

			if(r == 100)
				SetWindowTextA(hwnd,buf);

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
	wc.lpszClassName = L"八班";
	RegisterClass(&wc);
	
	HWND hwnd = CreateWindow(wc.lpszClassName,
							 L"模式对话框1",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);
	
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

//01)模式对话框：对话框不消失，其他窗口无法响应
//02)非模式对话框：对话框消失与否，不影响其他窗口的响应

//好处:可以非常方便的添加，编辑控件
//处理对话框实际上是对对话框上面的控件的操作(即控件的消息的处理)，
//其消息主要是初始化消息，事件消息,这些消息主要是在对话框
//对应的消息处理函数中响应