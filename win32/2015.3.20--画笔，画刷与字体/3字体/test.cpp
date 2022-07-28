#include <windows.h>

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
	
			//开启当前绘图设备句柄的高级绘图模式，若显卡不支持
			//则本函数无效
			SetGraphicsMode(hdc,GM_ADVANCED);

			HFONT f1 = CreateFont(
								50,//字体的高度
								50,//字体的宽度
								0,//字体底线的斜度，单位是角度/10，比如我们希望字体的底线斜度是45度，则填写450
								450,//字体本身的斜度，单位是 角度/10 ，比如我们希望字体本身的斜度45度，则填写450，必须开启高级绘图模式
								FW_NORMAL,//字体粗细程度，一般FW_NORMAL
								FALSE,//字体是否为斜体字
								FALSE,//字体是否有下划线
								FALSE,//字体是否有穿越线
								DEFAULT_CHARSET,//字体使用的编码,DEFAULT_CHARSET表示当前的系统使用的编码
								OUT_DEFAULT_PRECIS,//外观相关
								CLIP_DEFAULT_PRECIS,//裁剪相关
								DEFAULT_QUALITY,//质量相关
								DEFAULT_PITCH | FF_DONTCARE,//不管
								"华文新魏");//外观名称

			HFONT oldf = (HFONT)SelectObject(hdc,f1);

			//设置字体颜色
			SetTextColor(hdc,RGB(0,255,0));

			//设置字体背景为透明
			SetBkMode(hdc,TRANSPARENT);

			TextOutA(hdc,0,0,"123abc你好",10);


			LOGFONT logfont;
			logfont.lfHeight = 40;
			logfont.lfWidth = 20;
			logfont.lfEscapement = 0;
			logfont.lfOrientation = 0;
			logfont.lfWeight = 400;
			logfont.lfItalic = 1;
			logfont.lfUnderline = 0;
			logfont.lfStrikeOut = 0;
			logfont.lfCharSet = DEFAULT_CHARSET;
			logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
			logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
			logfont.lfQuality = DEFAULT_QUALITY;
			logfont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
			strcpy_s(logfont.lfFaceName,LF_FACESIZE,"黑体");

			HFONT f2 = CreateFontIndirect(&logfont);

			(HFONT)SelectObject(hdc,f2);

			SetTextColor(hdc,RGB(255,0,0));
			TextOutA(hdc,0,200,"456def世界",10);

			SelectObject(hdc,oldf);

			DeleteObject(f1);
			DeleteObject(f2);

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
							 "字体",//窗口标题栏文字
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