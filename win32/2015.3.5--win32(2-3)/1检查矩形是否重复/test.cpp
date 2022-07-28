#include <windows.h>
#include <vector>

#define _MAP_W 800
#define _MAP_H 640

std::vector<RECT> g_vRect;
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
			
			RECT r
				= 
			{
				p.x - 50,
				p.y - 50,
				p.x + 50,
				p.y + 50
			};

			if(p.x - 50 < 0)
				r.left = 0;
			if(p.x + 50 > _MAP_W - 1)
				r.right = _MAP_W - 1;
			if(p.y - 50 < 0)
				r.top = 0;
			if(p.y + 50 > _MAP_H - 1)
				r.bottom = _MAP_H - 1;

			RECT lr;
			for(std::vector<RECT>::iterator i = g_vRect.begin(); i != g_vRect.end();++i)
			{
				if(IntersectRect(&lr,&(*i),&r) == TRUE)
				{
					MessageBoxA(hwnd,"矩形重复","提示",MB_OK);
					return 0;
				}
			}

			g_vRect.push_back(r);

			InvalidateRect(hwnd,//窗口句柄
				          0,//区域的矩形地址，为0表示整个客户区
						  TRUE);//是否让操作系统绘制窗口背景色
							//(如果是，则WM_PAINT消息中的绘制会在系统用白色填充
			               //整个客户区之后，如果否，则WM_PAINT消息之前操作系统
							//不会用白色填充客户区)
			return 0;
		}
	//case WM_RBUTTONDOWN:
	//	{
	//		//if(g_vPoint.size() > 0)
	//		//{
	//		//	g_vPoint.pop_back();
	//		//	InvalidateRect(hwnd,0,TRUE);
	//		//}
	//		return 0;
	//	}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);


			for(std::vector<RECT>::iterator i = g_vRect.begin(); i != g_vRect.end();++i)
			{
				Rectangle(hdc,i->left,i->top,i->right,i->bottom);
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

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	RECT wr =
	{
		(sw - _MAP_W) / 2,
		(sh - _MAP_H) / 2,
		(sw - _MAP_W) / 2 + _MAP_W,
		(sh - _MAP_H) / 2 + _MAP_H
	};
	
	AdjustWindowRect(&wr,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,FALSE	);

	HWND hWnd = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 L"矩形是否重复",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 wr.left,//窗口的左上角x坐标
							 wr.top,//窗口的左上角y坐标
							 wr.right - wr.left,//窗口的宽（像素）
							 wr.bottom - wr.top,//窗口的高（像素）
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