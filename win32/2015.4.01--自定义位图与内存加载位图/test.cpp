#include <windows.h>

//从内存中加载位图
HBITMAP CreateColorBmp(int w,int h,unsigned int c)
{
	HDC dc = GetDC(HWND_DESKTOP);
	BITMAPINFOHEADER bin = {};
	bin.biSize = sizeof(bin);
	bin.biWidth = w;
	bin.biHeight = h;
	bin.biPlanes = 1;
	bin.biBitCount = 24;
	//得到一行的字节数
	int rowbyte = w * 3;
	
	if(rowbyte % 4 != 0)
		rowbyte += 4 - rowbyte % 4;
	
	//得到总字节数
	int allbyte = rowbyte * h;

	//生成颜色数据
	char* p = new char[allbyte];
	struct _BGR
	{
		unsigned char b,g,r;
	}* pBGR;

	for(int i = 0; i < h; ++i)
	{
		pBGR = (_BGR*)(p + i * rowbyte);
		for(int j = 0; j < w;++j)
		{
			pBGR->b = GetBValue(c);
			pBGR->g = GetGValue(c);
			pBGR->r = GetRValue(c);
			pBGR += 1;
		}
	}
	//
	HBITMAP hbmp = CreateDIBitmap(
		dc,&bin,CBM_INIT,
		p,(BITMAPINFO*)(&bin),
		DIB_RGB_COLORS);
	delete []p;
	ReleaseDC(HWND_DESKTOP,dc);
	return hbmp;
}

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
	}
	//我们不关心的消息就调用DefWindowProc(windows对所有消息的默认处理函数)来帮助我们处理
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//应用程序实例句柄
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	hbmp[0] = CreateColorBmp(640,480,RGB(0,127,127));
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
							 "内存中加载位图",//窗口标题栏文字
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

	return 1;
}