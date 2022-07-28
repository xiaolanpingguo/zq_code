#include <windows.h>

#define _BUTTON1 1
#define _BUTTON2 2
HWND g_hWnd[3];
RECT rButton1;
RECT rButton2;
//窗口消息函数，本函数将被操作系统调用
__w64 long __stdcall WindowProc(HWND hwnd,//产生消息的窗口
								unsigned int uMsg,//消息类型
								__w64 unsigned int wParam,//消息附加参数1
								__w64 long lParam)//消息附加参数2
{
	switch(uMsg)
	{
	//销毁消息触发方式
	//1)点击系统菜单的关闭菜单项（Alt + F4）
	//2)右上角的X按钮
	case WM_DESTROY:
		{
			//投递一个WM_QUIT消息到本线程的消息队列中
			PostQuitMessage(0);
			//一般我们处理了某个消息都要直接返回0.
			return 0;
		}
		//如果是控件消息
		//HIWORD(wParam)是该控件上发生的事件消息
		//LOWORD(wParam)是该控件的ID号
		//lParam是该控件的窗口句柄
	case WM_COMMAND:
		{
			//按下按钮
			if(BN_CLICKED == HIWORD(wParam))
			{
				if(LOWORD(wParam) == _BUTTON1)
					MessageBoxA(hwnd,"按下1",0,0);
				else if(LOWORD(wParam) == _BUTTON2)
					MessageBoxA(hwnd,"按下2",0,0);
			}
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			POINT p = {LOWORD(lParam),HIWORD(lParam)};
			if(PtInRect(&rButton1,p))
				SendMessage(g_hWnd[1],BM_CLICK,0,0);
			if(PtInRect(&rButton2,p))
				SendMessage(g_hWnd[2],BM_CLICK,0,0);
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

	g_hWnd[0] = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 L"按钮-父",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	//Windows预先设置了一些特殊的窗口，
	//这些窗口负责与用户进行交互，比如 button 编辑框等
	//这些窗口称为控件。
	//每种Windows预先设置好的控件的WNDCLASS都对应了一个字符串名字
	//比如按钮就是button
	//控件的id号在CreateWindow的HMENU参数设置，子窗口是不能有菜单的
	//所以用菜单表示id号，但要注意从属窗口可以有自己的菜单.
	//意味着从属窗口的创建的时候HMENU不能填写ID号，所以我们一般不用从属窗口当控件
	//按钮风格
	//BS_PUSHBUTTON：下压式按钮
	//BS_RADIOBUTTON:单选框
	//BS_CHECKBOX:复选框

	//一般处理控件
	//1)用子窗口创建控件
	//2)WM_COMMAND里检测控件消息
	//3)通过SendMessage发送控件控制消息来控制控件

	//按钮的事件消息
	//BN_CLICKED:按钮被点击
	//按钮的控制消息
	//BM_CLICK:模拟用户点击按钮

	g_hWnd[1] = CreateWindow(L"button",
							 L"按钮1",//窗口标题栏文字
							 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,//窗口风格
							 0,//窗口的左上角x坐标
							 0,//窗口的左上角y坐标
							 100,//窗口的宽（像素）
							 30,//窗口的高（像素）
							 g_hWnd[0],
							 (HMENU)_BUTTON1,//ID
							 wc.hInstance,//应用程序实例句柄
							 0);
	rButton1.left = 0;
	rButton1.top = 0;
	rButton1.right = 100;
	rButton1.bottom = 30;
	g_hWnd[2] = CreateWindow(L"BUTTON",
							 L"按钮2",//窗口标题栏文字
							 WS_CHILD | BS_PUSHBUTTON,//窗口风格
							 0,//窗口的左上角x坐标
							 40,//窗口的左上角y坐标
							 100,//窗口的宽（像素）
							 60,//窗口的高（像素）
							 g_hWnd[0],
							 (HMENU)_BUTTON2,//ID
							 wc.hInstance,//应用程序实例句柄
							 0);
	rButton2.left = 0;
	rButton2.top = 40;
	rButton2.right = 100;
	rButton2.bottom = 60;
	ShowWindow(g_hWnd[2],SW_SHOW);
	ShowWindow(g_hWnd[0],nCmdShow);
	UpdateWindow(g_hWnd[0]);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}