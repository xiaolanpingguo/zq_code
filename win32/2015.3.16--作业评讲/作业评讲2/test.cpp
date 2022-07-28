#include <windows.h>
#include <iostream>

HWND g_hWnd[5];


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
			if(HIWORD(wParam) == EN_CHANGE)
			{
				if(LOWORD(wParam) == 0)
				{
					int length = GetWindowTextLength(g_hWnd[1]);
					char* buf = new char[length + 1];

					GetWindowText(g_hWnd[1],buf,length + 1);

					SetWindowText(g_hWnd[2],buf);

					delete []buf;
				}
			}
			else if(HIWORD(wParam) == BN_CLICKED)
			{
				switch(LOWORD(wParam))
				{
				case 2:
					{
						int count = SendMessage(g_hWnd[1],EM_GETLINECOUNT,0,0);
						char buf[256];
						sprintf_s(buf,256,"%d",count);

						MessageBox(g_hWnd[0],buf,"行数",MB_OK);
						break;
					}
				case 3:
					{
						int count = SendMessage(g_hWnd[1],EM_GETLINECOUNT,0,0);

						for(int i = 0;i < count;++i)
						{
							char buf[256];
							sprintf_s(buf,256,"%d",i);
							char buf1[256] = {};
							*((short*)buf1) = 256;
							int r = SendMessage(g_hWnd[1],EM_GETLINE,i,(__w64 long)buf1);
							MessageBox(g_hWnd[0],buf1,buf,MB_OK);
						}
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
	g_hWnd[0] = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 "作业2",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	g_hWnd[1] = CreateWindow("edit",
							 "",//窗口标题栏文字
							 WS_CHILD | WS_VISIBLE | ES_MULTILINE |WS_BORDER
							 |ES_AUTOVSCROLL|ES_AUTOHSCROLL |
							 WS_HSCROLL|WS_VSCROLL|ES_WANTRETURN,//窗口风格
							 0,//窗口的左上角x坐标
							 0,//窗口的左上角y坐标
							 200,//窗口的宽（像素）
							 200,//窗口的高（像素）
							 g_hWnd[0],//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 (HMENU)0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	g_hWnd[2] = CreateWindow("edit",
							 "",//窗口标题栏文字
							 WS_CHILD | WS_VISIBLE |WS_BORDER | ES_READONLY|WS_HSCROLL,//窗口风格
							 200,//窗口的左上角x坐标
							 0,//窗口的左上角y坐标
							 200,//窗口的宽（像素）
							 30,//窗口的高（像素）
							 g_hWnd[0],//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 (HMENU)1,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	g_hWnd[3] = CreateWindow("button",
							 "行数",//窗口标题栏文字
							 WS_CHILD | WS_VISIBLE |WS_BORDER | BS_PUSHBUTTON,//窗口风格
							 0,//窗口的左上角x坐标
							 250,//窗口的左上角y坐标
							 50,//窗口的宽（像素）
							 30,//窗口的高（像素）
							 g_hWnd[0],//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 (HMENU)2,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	g_hWnd[4] = CreateWindow("button",
							 "内容",//窗口标题栏文字
							 WS_CHILD | WS_VISIBLE |WS_BORDER | BS_PUSHBUTTON,//窗口风格
							 0,//窗口的左上角x坐标
							 300,//窗口的左上角y坐标
							 50,//窗口的宽（像素）
							 30,//窗口的高（像素）
							 g_hWnd[0],//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 (HMENU)3,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);

	//04)显示窗口
	ShowWindow(g_hWnd[0],nCmdShow);

	//05)更新窗口
	UpdateWindow(g_hWnd[0]);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}