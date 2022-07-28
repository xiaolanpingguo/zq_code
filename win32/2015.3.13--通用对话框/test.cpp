#include <windows.h>

//通用对话框
//文件打开
//文件保存
//颜色对话框
//字体对话框

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
	case WM_KEYDOWN:
		{
			if(wParam == VK_F1)
			{
				//这里的[]中的值是最终能存多少个自定义颜色的数量
				//由于对话框中自定义颜色的框只有16个，所以这里设置16
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
				}
			}
			else if(wParam == VK_F2)
			{
				LOGFONT lf;
				CHOOSEFONT cf = {};
				cf.lStructSize = sizeof(cf);
				cf.hwndOwner = hwnd;
				cf.lpLogFont = &lf;
				cf.Flags = CF_SCREENFONTS;

				if(IDOK == ChooseFont(&cf))
				{
					int a = 0;
					//lf就被填写上我们选择的字体的属性，
					//配合CreateFontIndirect就能创建字体了
				}
			}
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			char buf[MAX_PATH]	= {};
			OPENFILENAME ofn = {};
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = buf;
			ofn.nMaxFile = MAX_PATH;

			//打开保存文件对话框
			//如果选择确定，则对OPENFILENAME对象的某些项进行了设置
			//if(IDOK == GetSaveFileName(&ofn))
			//{
			//	SetWindowText(hwnd,buf);
			//}
			//打开文件打开对话框
			if(IDOK == GetOpenFileName(&ofn))
			{
				SetWindowText(hwnd,buf);
			}


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
	wc.lpszClassName = "八班";
	RegisterClass(&wc);
	HWND hWnd = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 "通用对话框-文件保存与打开对话框",//窗口标题栏文字
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