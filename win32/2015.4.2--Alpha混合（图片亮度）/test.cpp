#include <windows.h>
#pragma comment(lib,"msimg32.lib")

HBITMAP hbmp[2];

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
	case WM_TIMER:
		{
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			HDC bmpdc[2];
			bmpdc[0] = CreateCompatibleDC(hdc);
			bmpdc[1] = CreateCompatibleDC(hdc);

			HBITMAP oldbmp[2];
			oldbmp[0] = (HBITMAP)SelectObject(bmpdc[0],hbmp[0]);
			oldbmp[1] = (HBITMAP)SelectObject(bmpdc[1],hbmp[1]);

			BitBlt(hdc,0,0,640,480,bmpdc[0],0,0,SRCCOPY);

			static unsigned char x = 0;
			x += 5;

			//Alpha混合
			BLENDFUNCTION bf;
			bf.BlendOp = AC_SRC_OVER;
			bf.BlendFlags = 0;
			bf.SourceConstantAlpha = x;//0完全透明，255完全不透明
			bf.AlphaFormat = 0;

			AlphaBlend(hdc,100,50,150,100,bmpdc[1],0,0,150,100,bf);

			BitBlt(hdc,300,250,150,100,bmpdc[1],0,0,SRCCOPY);

			SelectObject(bmpdc[0],oldbmp[0]);
			SelectObject(bmpdc[1],oldbmp[1]);

			DeleteDC(bmpdc[0]);
			DeleteDC(bmpdc[1]);

			EndPaint(hwnd,&ps);
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
	hbmp[0] = (HBITMAP)LoadImage(0,"0.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	hbmp[1] = (HBITMAP)LoadImage(0,"1.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
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
							 "第一个窗口程序",//窗口标题栏文字
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
	SetTimer(hWnd,0,40,0);
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		//如果发现有WM_KEYDOWN和WM_KEYUP消息就根据当前的输入法
		//在产生一个WM_CHAR消息并投递到消息队列中
		TranslateMessage(&msg);
		//派发消息回操作系统(估计就是下面DispatchMessage来调用窗口消息函数)
		DispatchMessage(&msg);
	}
	KillTimer(hWnd,0);

	DeleteObject(hbmp[0]);
	DeleteObject(hbmp[1]);

	return 1;
}