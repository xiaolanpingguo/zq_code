#include <windows.h>

RECT r = {100,200,200,400};

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
		//InvalidateRect,InvalidateRgn函数
	case WM_LBUTTONDOWN:
		{
			POINT p = {LOWORD(lParam),HIWORD(lParam)};
			
			//if(p.x >= r.left && p.x <= r.right 
			//&& p.y >= r.top && p.y <= r.bottom)
			//	MessageBoxA(hwnd,"点中了",0,0);

			//判断一个点是否在一个矩形内
			if(PtInRect(&r,p))
				MessageBoxA(hwnd,"点中了",0,0);

			//lprcSrc1和lprcSrc2如果相交返回真
			//且lprcDst填充为交集
			//lprcSrc1和lprcSrc2如果不相交返回假
			//IntersectRect(
			//	LPRECT lprcDst,//矩形地址
			//	CONST RECT *lprcSrc1,//矩形地址1
			//	CONST RECT *lprcSrc2);//矩形地址2
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			Rectangle(hdc,r.left,r.top,r.right,r.bottom);
			
			EndPaint(hwnd,&ps);

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
	
	HWND hWnd = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 L"简单碰撞",//窗口标题栏文字
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
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

//WM_PAINT触发方法
//绘制结构体
//PAINTSTRUCT ps;
//HDC:显示设备句柄
//BeginPaint:获取指定的窗口的客户区的显示设备
//EndPaint:释放获取的指定的窗口的客户区的显示设备
//只能在WM_PAINT中使用
//GetDC ReleaseDC

//POINT p;
//MoveToEx;
//LineTo
//Rectangle
//Ellipse
//TextOut
//PtInRect
//IntersectRect
