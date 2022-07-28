#include <windows.h>
#include <vector>

std::vector<POINT> g_vPoint;
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
			g_vPoint.push_back(p);
			InvalidateRect(hwnd,//窗口句柄
				          0,//区域的矩形地址，为0表示整个客户区
						  TRUE);//是否让操作系统绘制窗口背景色
							//(如果是，则WM_PAINT消息中的绘制会在系统用白色填充
			               //整个客户区之后，如果否，则WM_PAINT消息之前操作系统
							//不会用白色填充客户区)
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			if(g_vPoint.size() > 0)
			{
				g_vPoint.pop_back();
				InvalidateRect(hwnd,0,TRUE);
			}
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			if(g_vPoint.size() >= 2)
			{
				for(std::vector<POINT>::iterator i = g_vPoint.begin(); i != g_vPoint.end() - 1;++i)
				{
					POINT p;
					MoveToEx(hdc,i->x,i->y,&p);
					LineTo(hdc,(i + 1)->x,(i + 1)->y);
				}
			}
			
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
							 L"划线",//窗口标题栏文字
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