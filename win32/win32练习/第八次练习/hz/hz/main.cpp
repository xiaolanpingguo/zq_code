#include <windows.h>
#include<vector>
#include"resource.h"
#include<string>



std::string ss;

std::vector<int> g_vStrlen;

RECT r;
//std::string str;
int color_s = RGB(0,0,0);//颜色

HWND g_hwnd[2];

LOGFONT lf;//字体属性

int flag=0;//拖动的标记

RECT changeRect;



//GDI (Graphics Device Interface):图形设备接口，就是windows中
//用于绘制图形的各种函数，结构体，宏的总称.
//画笔
//窗口消息函数，本函数将被操作系统调用
INT_PTR __stdcall f(HWND hwndDlg,
					UINT uMsg,
					WPARAM wParam,
					LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CLOSE:
		{
			ShowWindow(g_hwnd[1],SW_HIDE);
			return 1;

		}
	case WM_INITDIALOG:
		{
			return 1;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
			{
				if(LOWORD(wParam) == ID1)
				{
					COLORREF custColor[16] =
					{
						//这里的项是最初我们自定义颜色的值
						RGB(255,0,0),RGB(255,255,255)
					};

					CHOOSECOLOR cc = {};
					cc.lStructSize = sizeof(cc);
					cc.hwndOwner = g_hwnd[1];
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
						color_s =RGB(r,g,b);
						InvalidateRect(g_hwnd[0],&::r,TRUE);
					}
				}else
				if(LOWORD(wParam) == IDCANCEL)
				{
					CHOOSEFONT cf = {};
					cf.lStructSize = sizeof(cf);
					cf.hwndOwner = g_hwnd[1];
					cf.lpLogFont = &lf;
					cf.Flags = CF_SCREENFONTS;

					if(IDOK == ChooseFont(&cf))
					{
						InvalidateRect(g_hwnd[0],&::r,TRUE);
						//lf就被填写上我们选择的字体的属性，
						//配合CreateFontIndirect就能创建字体了
					}
				}
			}else
			if(HIWORD(wParam)==EN_CHANGE)
			{
				g_vStrlen.clear();
				ss.clear();
				HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
				int r = (int)SendMessage(hwnd,EM_GETLINECOUNT,0,0);
				for(int i=0;i<r;i++)
				{
					char buf[256] = {};
					*((short*)buf) = 256;//前2个字节是数组的大小
					SendMessageA(hwnd,EM_GETLINE,i,(__w64 long)buf);
					ss+=buf;
					g_vStrlen.push_back(strlen(buf));
				}
				InvalidateRect(g_hwnd[0],&::r,true);
			}
			return 1;
		}
	}
	return 0;
}


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
			r.left =200;
			r.top = 200;
			r.right =400;
			r.bottom=400;
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
			SetGraphicsMode(hdc,GM_ADVANCED);
			SetBkMode(hdc,TRANSPARENT);
			Rectangle(hdc,r.left,r.top,r.right,r.bottom);
			
			HFONT oldf =(HFONT)GetCurrentObject(hdc,OBJ_FONT);
			HFONT newfont =CreateFontIndirect(&lf);
			(HFONT)SelectObject(hdc,newfont);
			SetTextColor(hdc,(COLORREF)color_s);
			if(flag==0)
			{
				for(int i = 0; i < g_vStrlen.size(); i++)
				{
					int count = 0;
					for(int j = 0; j < i; j++)
					{
						count += g_vStrlen[j];
					}
					char buf[256] = {};

					memcpy_s(buf,255,ss.c_str() + count,g_vStrlen[i]);

					TextOutA(hdc,r.left,r.top + i * 30,buf,strlen(buf));
				}
			}
			

			SelectObject(hdc,oldf);
			DeleteObject(newfont);
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			r.left=LOWORD(lParam);
			r.top=HIWORD(lParam);
			flag=1;
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			ShowWindow(g_hwnd[1],SW_SHOW);
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			if(flag==1)
			{
				r.right=LOWORD(lParam);
				r.bottom=HIWORD(lParam);
				InvalidateRect(hwnd,0,TRUE);
			}
			return 0;
		}
	case WM_LBUTTONUP:
		{
			r.right=LOWORD(lParam);
			r.bottom=HIWORD(lParam);
			flag=0;
			InvalidateRect(hwnd,&r,TRUE);
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
	wc.lpszMenuName = 0;

	//窗口的名字
	wc.lpszClassName = L"八班";

	//02)注册填充好的窗口
	RegisterClass(&wc);
	
	g_hwnd[0] = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
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

	g_hwnd[1] = CreateDialog(GetModuleHandle(0),//获取对话框的句柄
							MAKEINTRESOURCE(IDD_DIALOG1),//对话框的ID
							g_hwnd[0],//父窗口
							f);//对话框的消息处理函数

	//04)显示窗口
	ShowWindow(g_hwnd[0],nCmdShow);
	ShowWindow(g_hwnd[1],SW_SHOW);

	//05)更新窗口
	UpdateWindow(g_hwnd[0]);

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