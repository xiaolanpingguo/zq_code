#include <windows.h>
#include <string>
#include "resource.h"


std::string allfile;

INT_PTR CALLBACK DialogProc(HWND hwndDlg,//产生消息的窗口
							UINT uMsg,//消息类型
							WPARAM wParam,//消息附加参数1
							LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
			SetDlgItemText(hwndDlg,IDC_EDIT1,allfile.c_str());
			return 1;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
				EndDialog(hwndDlg,1);
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
			//投递一个WM_QUIT消息到本线程的消息队列中
			PostQuitMessage(0);
			//一般我们处理了某个消息都要直接返回0.
			return 0;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
			{
				switch(LOWORD(wParam))
				{
				case 0:
					{
						char fn[MAX_PATH] = {};
						OPENFILENAME ofn = {};
						ofn.lStructSize = sizeof(ofn);
						ofn.hwndOwner = hwnd;
						ofn.lpstrFile = fn;
						ofn.nMaxFile = MAX_PATH;

						if(IDOK == GetOpenFileName(&ofn))
						{
							allfile += fn;
							allfile += "\r\n";
						}
						break;
					}
				case 1:
					{
						DialogBox(GetModuleHandle(0),
								  MAKEINTRESOURCE(IDD_DIALOG1),
								  HWND_DESKTOP,
								  DialogProc);
						break;
					}
				case 2:
					{
						allfile.clear();
						break;
					}
				}
			}
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
	//窗口结构体类别风格（所有被本窗口类别结构体创建出的窗口都具有）
	//CS_HREDRAW : 窗口水平尺寸发生改变就会重绘(投递WM_PAINT消息)
	//CS_VREDRAW : 窗口竖直尺寸发生改变就会重绘(投递WM_PAINT消息)
	wc.style = CS_HREDRAW|CS_VREDRAW;
	//窗口消息函数的地址
	wc.lpfnWndProc = WindowProc;
	//窗口类别的额外字节，一般不使用
	wc.cbClsExtra = 0;
	//窗口的额外字节，一般不使用
	wc.cbWndExtra = 0;
	//应用程序实例句柄
	wc.hInstance = hInstance;
	//图标
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);

	//光标
	wc.hCursor = LoadCursor(0,IDC_ARROW);

	//HBRUSH 画刷
	//操作系统用于绘制窗口背景的背景画刷
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//菜单字符串ID，如果没有则填0
	wc.lpszMenuName = 0;

	//窗口的名字
	wc.lpszClassName = "八班";

	//02)注册填充好的窗口
	RegisterClass(&wc);
	
	//03)用窗口类别结构体来创建窗口
	HWND hWnd = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 "作业3",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	const char* bn[] = {"打开","查看","清空"};
	for(int  i = 0; i < 3;++i)
	{
		CreateWindow("button",//窗口类别结构体的名称，操作系统会根据
                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
					 //帮助完成创建窗口的任务
					 bn[i],//窗口标题栏文字
					 WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,//窗口风格
					 0,//窗口的左上角x坐标
					 i * 30,//窗口的左上角y坐标
					 50,//窗口的宽（像素）
					 30,//窗口的高（像素）
					 hWnd,//父窗口窗口句柄,HWND_DESKTOP表示桌面
					 (HMENU)i,//窗口菜单句柄，不使用菜单填0
					 wc.hInstance,//应用程序实例句柄
					 0);
	}

	//04)显示窗口
	ShowWindow(hWnd,nCmdShow);

	//05)更新窗口
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