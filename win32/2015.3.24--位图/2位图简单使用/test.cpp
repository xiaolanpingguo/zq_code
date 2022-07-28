#include <windows.h>
#include "resource.h"


HBITMAP hbmp[2];
HBITMAP hbmp1[2];

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
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			//创建兼容的设备DC
			HDC bmpdc[4];
			bmpdc[0] = CreateCompatibleDC(hdc);
			bmpdc[1] = CreateCompatibleDC(hdc);
			bmpdc[2] = CreateCompatibleDC(hdc);
			bmpdc[3] = CreateCompatibleDC(hdc);
			
		
			//将BITMAP选入到兼容设备中并获取老的位图
			HBITMAP oldhbmp[4];
			oldhbmp[0] = (HBITMAP)SelectObject(bmpdc[0],hbmp[0]);
			oldhbmp[1] = (HBITMAP)SelectObject(bmpdc[1],hbmp[1]);
			oldhbmp[2] = (HBITMAP)SelectObject(bmpdc[2],hbmp1[0]);
			oldhbmp[3] = (HBITMAP)SelectObject(bmpdc[3],hbmp1[1]);

			//位图传输
			BitBlt(
				hdc,//目标设备
				0,//目标矩形左上角x坐标
				0,//目标矩形左上角y坐标
				640,//目标矩形的宽和高
				480,
				bmpdc[0],//源设备
				0,//源矩形左上角的x,y坐标
				0,
				SRCCOPY);//SRCCOPY表示原封不动的拷贝
	
			BitBlt(hdc,100,50,75,100,bmpdc[1],75,0,SRCCOPY);

			BitBlt(hdc,100,250,75,100,bmpdc[1],75,0,SRCCOPY);
			BitBlt(hdc,300,250,150,100,bmpdc[1],0,0,SRCCOPY);

			BitBlt(hdc,100,250,75,100,bmpdc[2],0,0,SRCCOPY);
			BitBlt(hdc,300,250,150,100,bmpdc[3],0,0,SRCCOPY);

			SelectObject(bmpdc[0],oldhbmp[0]);
			SelectObject(bmpdc[1],oldhbmp[1]);
			SelectObject(bmpdc[2],oldhbmp[2]);
			SelectObject(bmpdc[3],oldhbmp[3]);

			DeleteDC(bmpdc[0]);
			DeleteDC(bmpdc[1]);
			DeleteDC(bmpdc[2]);
			DeleteDC(bmpdc[3]);
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
	hbmp[0] = (HBITMAP)LoadImage(
		0,//如果使用资源中的位图此次必须填写应用程序实例句柄，否则填0即可
		"1.bmp",//位图文件的名称
		IMAGE_BITMAP,//类型
		0,//希望加载的位图的宽(像素宽),为0则表示x方向全部加载
		0,//希望加载的位图的高(像素高),为0则表示y方向全部加载
		LR_LOADFROMFILE);//LR_LOADFROMFILE表示从外部文件加载

	hbmp[1] = (HBITMAP)LoadImage(
		0,//如果使用资源中的位图此次必须填写应用程序实例句柄，否则填0即可
		"2.bmp",//位图文件的名称
		IMAGE_BITMAP,//类型
		0,//希望加载的位图的宽(像素宽),为0则表示x方向全部加载
		0,//希望加载的位图的高(像素高),为0则表示y方向全部加载
		LR_LOADFROMFILE);//LR_LOADFROMFILE表示从外部文件加载

	hbmp1[0] = (HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_BITMAP1),IMAGE_BITMAP,0,0,0);
	hbmp1[1] = (HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_BITMAP2),IMAGE_BITMAP,0,0,0);
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
							 "位图简单使用",//窗口标题栏文字
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
		//如果发现有WM_KEYDOWN和WM_KEYUP消息就根据当前的输入法
		//在产生一个WM_CHAR消息并投递到消息队列中
		TranslateMessage(&msg);
		//派发消息回操作系统(估计就是下面DispatchMessage来调用窗口消息函数)
		DispatchMessage(&msg);
	}

	DeleteObject(hbmp[1]);
	DeleteObject(hbmp[0]);

	DeleteObject(hbmp1[1]);
	DeleteObject(hbmp1[0]);
	return 1;
}