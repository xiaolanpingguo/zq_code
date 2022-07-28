#include <windows.h>
#include <vector>

#pragma comment(lib,"MSIMG32.lib")

HDC GetBmpDC(HWND hwnd,const char* bmpfile)
{
	HBITMAP hbmp = (HBITMAP)LoadImage(0,bmpfile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(!hbmp)
		return 0;
	//窗口主显示设备
	//HDC maindc = GetDC(HWND_DESKTOP);
	//得到主设备
	HDC maindc = GetDC(hwnd);

	//创建兼容显示设备
	HDC bmpdc = CreateCompatibleDC(maindc);

	//将新位图选入兼容设备中
	HBITMAP oldbmp = (HBITMAP)SelectObject(bmpdc,hbmp);

	//删除新位图，新位图选入到兼容设备后，兼容设备内部就完整的
	//复制了一份新位图的数据
	DeleteObject(hbmp);

	//删除老位图
	DeleteObject(oldbmp);

	//释放主设备
	ReleaseDC(hwnd,maindc);

	return bmpdc;
}

void DeleteBmpDC(HDC hdc)
{
	DeleteDC(hdc);
}

HDC bmpdc[2];
struct _SHIJIAN
{
	POINT p;
	int f;//帧
};
struct _BAOZHA
{
	POINT p;
	int f;
};

std::vector<_SHIJIAN> g_sj;
std::vector<_BAOZHA> g_baozha;

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
	case WM_LBUTTONDOWN:
		{
			_SHIJIAN shijian = {{LOWORD(lParam),HIWORD(lParam)},50};

			g_sj.push_back(shijian);

			return 0;
		}
	case WM_TIMER:
		{
			for(std::vector<_SHIJIAN>::iterator i = g_sj.begin();i != g_sj.end();)
			{
				if(i->f > 0)
				{
					i->f -=1;
					++i;
				}
				else
				{
					_BAOZHA baozha = {{i->p.x,i->p.y},0};
					g_baozha.push_back(baozha);
					i = g_sj.erase(i);
				}
			}

			for(std::vector<_BAOZHA>::iterator i = g_baozha.begin();i != g_baozha.end();)
			{
				if(i->f < 10)
				{
					i->f +=1;
					++i;
				}
				else
				{
					i = g_baozha.erase(i);
				}
			}
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			//根据客户区的变化绘制背景图片
			RECT clientRect;
			GetClientRect(hwnd,&clientRect);
			StretchBlt(hdc,clientRect.left,clientRect.top,clientRect.right - clientRect.left,clientRect.bottom - clientRect.top,bmpdc[0],0,0,640,480,SRCCOPY);

			for(std::vector<_BAOZHA>::iterator i = g_baozha.begin();i != g_baozha.end();++i)
			{
				TransparentBlt(hdc,i->p.x,i->p.y,54,54,bmpdc[1],i->f * 54,0,54,54,RGB(0,0,0));
			}

			SetBkMode(hdc,TRANSPARENT);

			for(std::vector<_SHIJIAN>::iterator i = g_sj.begin();i != g_sj.end();++i)
			{
				char buf[32];
				sprintf_s(buf,32,"%d",i->f);
				TextOutA(hdc,i->p.x,i->p.y,buf,(int)strlen(buf));
			}

	

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
							 "炸弹",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	bmpdc[0] = GetBmpDC(hWnd,"bmp\\0.bmp");
	bmpdc[1] = GetBmpDC(hWnd,"bmp\\1.bmp");

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
	DeleteBmpDC(bmpdc[0]);
	DeleteBmpDC(bmpdc[1]);

	return 1;
}