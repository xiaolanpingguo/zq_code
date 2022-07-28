#include <windows.h>
#include<vector>
#include"resource.h"

#define JX true
#define YX false

struct Rect
{
	RECT r;
	int pc;//画笔的颜色
	int bc;//画刷的颜色
	bool isJx;
};
Rect r;
std::vector<Rect> g_vRect;
bool flag = JX;
int PC  =  RGB(0,0,0);
int BC  =  RGB(255,255,255);


//GDI (Graphics Device Interface):图形设备接口，就是windows中
//用于绘制图形的各种函数，结构体，宏的总称.
//画笔
//窗口消息函数，本函数将被操作系统调用
__w64 long __stdcall WindowProc(HWND hwnd,//产生消息的窗口
								unsigned int uMsg,//消息类型
								__w64 unsigned int wParam,//消息附加参数1
								__w64 long lParam)//消息附加参数2
{
	switch(uMsg)
	{
	//销毁消息触发方式
	//1)点击系统菜单的关闭菜单项（Alt + F4）
	//2)右上角的X按钮
	case WM_CREATE:
		{
			char buf[256]={};
			sprintf_s(buf,256,"矩形、画笔(0,0,0),画刷(255,255,255)");
			SetWindowTextA(hwnd,buf);
			return 0;
		}
	case WM_DESTROY:
		{
			//投递一个WM_QUIT消息到本线程的消息队列中
			PostQuitMessage(0);
			//一般我们处理了某个消息都要直接返回0.
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);
			
			for(std::vector<Rect>::iterator i = g_vRect.begin();i!=g_vRect.end();i++)
			{
				HBRUSH oldb =(HBRUSH)GetCurrentObject(hdc,OBJ_BRUSH);
				HPEN oldp = (HPEN)GetCurrentObject(hdc,OBJ_PEN);
				HPEN newpen = CreatePen(
				PS_SOLID,//风格
				1,//宽度，如果宽度大于1，那么风格只能是PS_SOLID
				i->pc);//颜色
				HBRUSH newbrush = CreateSolidBrush(i->bc);
				SelectObject(hdc,newpen);
				SelectObject(hdc,newbrush);
				if(i->isJx)
				{
					Rectangle(hdc,i->r.left,i->r.top,i->r.right,i->r.bottom);
				}else
				{
					Ellipse(hdc,i->r.left,i->r.top,i->r.right,i->r.bottom);
				}
				SelectObject(hdc,oldp);
				SelectObject(hdc,oldb);
				DeleteObject(newbrush);
				DeleteObject(newpen);
			}
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			r.r.left=LOWORD(lParam);
			r.r.top=HIWORD(lParam);
			return 0;
		}
	case WM_LBUTTONUP:
		{
			r.r.right=LOWORD(lParam);
			r.r.bottom=HIWORD(lParam);
			r.isJx=flag;
			r.pc =PC;
			r.bc =BC;
			g_vRect.push_back(r);
			InvalidateRect(hwnd,0,TRUE);
			return 0;
			
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam)==0)
			{
				switch(LOWORD(wParam))
				{
				case ID_40001:
					{
						flag = JX;
						break;
					}
				case ID_40002:
					{
						flag =YX;
						break;
					}
				case ID_40003:
					{
						COLORREF custColor[16] =
						{
							//这里的项是最初我们自定义颜色的值
							RGB(255,0,0),RGB(255,255,255)
						};

						CHOOSECOLOR cc = {};
						cc.lStructSize = sizeof(cc);
						cc.hwndOwner = hwnd;
						cc.lpCustColors = custColor;

						//颜色是由R G B 三原色混合而成的
						// 而三原色的取值范围是 0-255
						//所以一般用unsigned char来记录我们的每个颜色分量
						//打开颜色对话框
						if(IDOK == ChooseColor(&cc))
						{
							COLORREF color = cc.rgbResult;

							unsigned char r =  GetRValue(color);
							unsigned char g =  GetGValue(color);
							unsigned char b =  GetBValue(color);
							PC =RGB(r,g,b);
							char buf[256]={};
							sprintf_s(buf,256,"矩形、画笔(%d,%d,%d),画刷(%d,%d,%d)",
									GetRValue(PC),GetGValue(PC),GetBValue(PC),
									GetRValue(BC),GetGValue(BC),GetBValue(BC));
							SetWindowTextA(hwnd,buf);
						}
						break;
					}
				case ID_40004:
					{
						COLORREF custColor[16] =
						{
							//这里的项是最初我们自定义颜色的值
							RGB(255,0,0),RGB(255,255,255)
						};

						CHOOSECOLOR cc = {};
						cc.lStructSize = sizeof(cc);
						cc.hwndOwner = hwnd;
						cc.lpCustColors = custColor;

						//颜色是由R G B 三原色混合而成的
						// 而三原色的取值范围是 0-255
						//所以一般用unsigned char来记录我们的每个颜色分量
						//打开颜色对话框
						if(IDOK == ChooseColor(&cc))
						{
							COLORREF color = cc.rgbResult;

							unsigned char r =  GetRValue(color);
							unsigned char g =  GetGValue(color);
							unsigned char b =  GetBValue(color);
							BC =RGB(r,g,b);
							char buf[256]={};
							sprintf_s(buf,256,"矩形、画笔(%d,%d,%d),画刷(%d,%d,%d)",
									GetRValue(PC),GetGValue(PC),GetBValue(PC),
									GetRValue(BC),GetGValue(BC),GetBValue(BC));
							SetWindowTextA(hwnd,buf);
						}
						break;
					}	
				}
				return 0;
			}
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
	//窗口结构体类别风格（所有被本窗口类别结构体创建出的窗口都具有）
	//CS_HREDRAW : 窗口水平尺寸发生改变就会重绘(投递WM_PAINT消息)
	//CS_VREDRAW : 窗口竖直尺寸发生改变就会重绘(投递WM_PAINT消息)
	wc.style = CS_HREDRAW|CS_VREDRAW;
	//窗口消息函数的地址
	wc.lpfnWndProc = WindowProc;
	//窗口类别的额外字节，一般不使用
	wc.cbClsExtra = 0;
	//窗口的额外字节，一般不使用
	wc.cbWndExtra = 0;
	//应用程序实例句柄
	wc.hInstance = hInstance;
	//图标
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);

	//光标
	wc.hCursor = LoadCursor(0,IDC_ARROW);

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//菜单字符串ID，如果没有则填0
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	//窗口的名字
	wc.lpszClassName = L"八班";

	//02)注册填充好的窗口
	RegisterClass(&wc);
	
	HWND hWnd = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 L"画笔",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	//04)显示窗口
	SetTimer(hWnd,1,200,0);
	ShowWindow(hWnd,nCmdShow);

	//05)更新窗口
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
	KillTimer(hWnd,1);

	return 1;
}