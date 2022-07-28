#include <windows.h>

HPEN newp;
HBRUSH newb;
HFONT newf;

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

			HPEN oldp = (HPEN)SelectObject(hdc,newp);
			HBRUSH oldb = (HBRUSH)SelectObject(hdc,newb);
			HFONT oldf = (HFONT)SelectObject(hdc,newf);

			//-------------------点相关

			//设置某个像素为指定颜色(与画笔画刷无关)
			SetPixel(hdc,1,1,RGB(255,0,0));

			SetPixel(hdc,1,2,RGB(0,255,0));

			//获取指定的某个像素的颜色
			COLORREF c = GetPixel(hdc,1,2);

			unsigned char r = GetRValue(c);

			//--------------画线(画笔起作用)
			MoveToEx(hdc,5,5,0);
			LineTo(hdc,100,50);
			//---------------矩形(画笔，画刷)
			Rectangle(hdc,150,200,280,400);
			//---------------椭圆(画笔，画刷)
			Ellipse(hdc,300,200,480,400);
			//---------------文字
			//设置字体的颜色
			SetTextColor(hdc,RGB(100,100,100));

			//设置背景模式
			SetBkMode(hdc,TRANSPARENT);

			//单行文字输出
			TextOutA(hdc,200,0,"123abc",6);


			const char* s = "hellosdafsdfs撒旦反对撒犯得上发生";

			RECT rect = {200,50,380,250};

			Rectangle(hdc,rect.left,rect.top,rect.right,rect.bottom);

			//绘制多行文字--最后一个参数是断行标志
			DrawTextA(hdc,s,(int)strlen(s),&rect,DT_WORDBREAK);

			SelectObject(hdc,oldp);
			SelectObject(hdc,oldb);
			SelectObject(hdc,oldf);
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
	newp = CreatePen(PS_SOLID,1,RGB(255,0,0));
	newb = CreateSolidBrush(RGB(255,255,0));
	newf = CreateFont(18,12,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,
		"宋体");

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

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		//如果发现有WM_KEYDOWN和WM_KEYUP消息就根据当前的输入法
		//在产生一个WM_CHAR消息并投递到消息队列中
		TranslateMessage(&msg);
		//派发消息回操作系统(估计就是下面DispatchMessage来调用窗口消息函数)
		DispatchMessage(&msg);
	}

	DeleteObject(newf);
	DeleteObject(newp);
	DeleteObject(newb);

	return 1;
}