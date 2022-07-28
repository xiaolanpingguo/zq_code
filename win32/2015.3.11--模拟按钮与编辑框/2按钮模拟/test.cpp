#include <windows.h>
#include <iostream>

//窗口关系
//子窗口
//{
//01）子窗口被父窗口裁剪
//02）子窗口不能有菜单
//03）随着父窗口的销毁被销毁
//}
//从属窗口
//{
//01）从属窗口不被父窗口裁剪
//02）随着父窗口的销毁被销毁
//}

//基本的控件
//01)本质是窗口
//{
//	操作系统预先设置了所有的控件的WNDCLASS
//  所有的控件都拥有自己的窗口过程处理函数
//	事件消息通过WM_COMMAND发送给父窗口
//  往往通过SendMessage发送控制消息来控制某些控件
//}
//02)类型
//按钮
//{  
//	窗口文本：显示在按钮上的文本
//  标志字符串:button
//  风格：一般用下压式 
//  消息： 事件消息-》BN_CLICKED
//		   控制消息-》BM_CLICK
//}
//编辑框
//{
//	窗口文本
//  {
//		显示的文本内容
//		每行以0x0d,0x0a换行
//      最后有结束符0x00
//  }
//  类型：
//	{
//		单行
//		回车多行
//	}
//	消息
//	{
//		事件消息:EN_UPDATE,EN_CHANGE
//		控制消息:EM_GETLINECOUNT,EM_GETLINE,EM_LINEINDEX,EM_LINEFROMCHAR
//	}
//}

//相关函数
//EnableWindow
//GetWindowText
//GetWindowTextLength

//每种控件都有自己的窗口消息函数以及WNDCLASS

HWND g_hWnd[2];
//窗口消息函数，本函数将被操作系统调用
__w64 long __stdcall ButtonProc(HWND hwnd,//产生消息的窗口
								unsigned int uMsg,//消息类型
								__w64 unsigned int wParam,//消息附加参数1
								__w64 long lParam)//消息附加参数2
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			//获取父窗口的句柄
			HWND parenthWnd = GetParent(hwnd);
			//获取菜单句柄
			HMENU hmenu = GetMenu(hwnd);

			//向父窗口发送一个WM_COMMAND消息
			SendMessage(parenthWnd,WM_COMMAND,MAKELONG((DWORD)hmenu,BN_CLICKED),(__w64 long)hwnd);

			SetFocus(hwnd);
			return 0;
		}
	case WM_KEYDOWN:
		{
			MessageBoxA(0,"2",0,0);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			char buf[256];

			GetWindowTextA(hwnd,buf,256);
			TextOutA(hdc,0,0,buf,(int)strlen(buf));

			EndPaint(hwnd,&ps);
			return 0;
		}
	}
	//我们不关心的消息就调用DefWindowProc(windows对所有消息的默认处理函数)来帮助我们处理
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

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
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
				Beep(500,500);
			return 0;
		}
	case WM_KEYDOWN:
		{
			MessageBoxA(0,"1",0,0);
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
							 L"模拟按钮",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	WNDCLASS Button_wc;
	Button_wc.style = CS_HREDRAW|CS_VREDRAW;
	Button_wc.lpfnWndProc = ButtonProc;
	Button_wc.cbClsExtra = 0;
	Button_wc.cbWndExtra = 0;
	Button_wc.hInstance = hInstance;
	Button_wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	Button_wc.hCursor = LoadCursor(0,IDC_ARROW);
	Button_wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	Button_wc.lpszMenuName = 0;
	Button_wc.lpszClassName = L"MyButton";
	RegisterClass(&Button_wc);
	g_hWnd[1] = CreateWindow(L"MyButton",//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 L"我的按钮",//窗口标题栏文字
							 WS_BORDER | WS_VISIBLE | WS_CHILD,//窗口风格
							 0,//窗口的左上角x坐标
							 0,//窗口的左上角y坐标
							 100,//窗口的宽（像素）
							 30,//窗口的高（像素）
							 g_hWnd[0],//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 (HMENU)1,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0
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