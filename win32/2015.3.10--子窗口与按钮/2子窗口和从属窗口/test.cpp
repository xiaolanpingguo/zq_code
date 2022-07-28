#include <windows.h>

HWND g_hWnd[3];

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
	case WM_CLOSE:
		{
			if(hwnd == g_hWnd[0])
				DestroyWindow(hwnd);
			else
				ShowWindow(hwnd,SW_HIDE);
			return 0;
		}
	case WM_KEYDOWN:
		{
			if(wParam == VK_F1)
				ShowWindow(g_hWnd[1],SW_SHOW);
			if(wParam == VK_F2)
				ShowWindow(g_hWnd[2],SW_SHOW);
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

	g_hWnd[0] = CreateWindow(wc.lpszClassName,
							 L"父窗口",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	//WS_VISIBLE 使窗口一开始可见，当然也可以使用
	//ShowWindow(g_hWnd[2],SW_SHOW)使其可见.

	//窗口节点之间的关系
	//1)父窗口<---->子窗口(要带WS_CHILD,要被父窗口裁剪)
	//2)父窗口<---->从属窗口(不带WS_CHILD,不被父窗口裁剪)

	//窗口的销毁是一个后根遍历，所有的当前窗口的子节点都先于当前
	//的窗口销毁，无论是子窗口还是从属窗口创建的时候hWndParent
	//是必须要填写其父窗口的句柄.
	g_hWnd[1] = CreateWindow(wc.lpszClassName,
							 L"子窗口(F1显示)",
							 WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD,
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 g_hWnd[0],
							 0,
							 wc.hInstance,
							 0);
	g_hWnd[2] = CreateWindow(wc.lpszClassName,
							 L"从属窗口(F2显示)",
							 WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 g_hWnd[0],
							 0,
							 wc.hInstance,
							 0);
	
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