#include <windows.h>
#include<vector>

#pragma comment(lib,"MSIMG32.lib")

HDC GetBmpDC(HWND hwnd,const char* bmpfile)
{
	HBITMAP hbmp = (HBITMAP)LoadImageA(0,bmpfile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
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

struct boom
{
	POINT p;
	int time;
	int PictureChange;
};

HDC bmpdc[2];

std::vector<boom> g_vBoom;



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
			POINT p;
			p.x = LOWORD(lParam);
			p.y = HIWORD(lParam);
			boom b = {p,50,0};
			g_vBoom.push_back(b);
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			BitBlt(hdc,0,0,640,480,bmpdc[0],0,0,SRCCOPY);

			SetTextColor(hdc,RGB(255,0,0));
			SetBkMode(hdc,TRANSPARENT);

			//透明
			for(std::vector<boom>::iterator i =g_vBoom.begin();i!=g_vBoom.end();)
			{
				if(i->time!=0)
				{
					char buf[256];
					sprintf_s(buf,256,"%d",i->time);
					TextOutA(hdc,i->p.x,i->p.y,buf,strlen(buf));
				}else
				{
					TransparentBlt(
						hdc,//目标设备
						i->p.x,//目标矩形
						i->p.y,
						54,
						54,
						bmpdc[1],//源设备
						i->PictureChange*54,//源矩形
						0,
						54,
						54,
						RGB(0,255,0));//要透明的颜色
				}
				if(i->PictureChange==9)
				{
					i=g_vBoom.erase(i);
				}else
					i++;
			}
			
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_TIMER:
		{
			for(std::vector<boom>::iterator i =g_vBoom.begin();i!=g_vBoom.end();i++)
			{
				if(i->time!=0)
				{
					i->time--;
				}else
				{
					i->PictureChange++;
				}
			}
			InvalidateRect(hwnd,0,TRUE);
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
	wc.lpszClassName = L"八班";
	RegisterClass(&wc);
	//RECT r1={300,300,400,500};
	//AdjustWindowRect(&r1,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,//窗口风格
	//FALSE);
	HWND hWnd = CreateWindow(wc.lpszClassName,
							 L"位图使用",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 400,//窗口的左上角x坐标
							 200,//窗口的左上角y坐标
							 640,//窗口的宽（像素）
							 460,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0


	bmpdc[0] = GetBmpDC(hWnd,"0.bmp");
	bmpdc[1] = GetBmpDC(hWnd,"1.bmp");

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