#include <windows.h>
#include <iostream>

//事件消息:
//EN_UPDATE
//EN_CHANGE
//BN_CLICKED
//控制消息:
//EM_GETLINECOUNT
//EM_GETLINE
//EM_LINEINDEX
//EM_LINEFROMCHAR
//BM_CLICK
HWND g_hWnd[5];
HWND g_hButton[4];
int i;

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
	case WM_DESTROY:
		{
			//投递一个WM_QUIT消息到本线程的消息队列中
			PostQuitMessage(0);
			//一般我们处理了某个消息都要直接返回0.
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			//如果多行编辑框，则得到的字符串以0x0d,0x0a换行
			for(int i = 1; i < 5; ++i)
			{
				int len = GetWindowTextLength(g_hWnd[i]);
				char* str = new char[len + 1];

				//GetWindowText得到的字符串都有结束符0
				GetWindowText(g_hWnd[i],str,len + 1);

				MessageBox(hwnd,str,"文字",MB_OK);

				delete []str;
			}
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			i += 1;
			char buf[32];
			sprintf_s(buf,32,"%d",i);
			SetWindowTextA(g_hWnd[2],buf);
			return 0;
		}
	case WM_COMMAND:
		{
			//EN_UPDATE:编辑框中文字被修改之前
			//EN_CHANGE:编辑框中文字被修改之后
			if(HIWORD(wParam) == EN_UPDATE)
			{
				//switch(LOWORD(wParam))
				//{
				//case 1:MessageBoxA(hwnd,"单行编辑框即将修改",0,0);break;
				//case 2:MessageBoxA(hwnd,"只读编辑框即将修改",0,0);break;
				//case 3:MessageBoxA(hwnd,"密码编辑框即将修改",0,0);break;
				//case 4:MessageBoxA(hwnd,"多行编辑框即将修改",0,0);break;
				//}
			}
			else if(HIWORD(wParam) == EN_CHANGE)
			{
				//switch(LOWORD(wParam))
				//{
				//case 1:MessageBoxA(hwnd,"单行编辑框修改",0,0);break;
				//case 2:MessageBoxA(hwnd,"只读编辑框修改",0,0);break;
				//case 3:MessageBoxA(hwnd,"密码编辑框修改",0,0);break;
				//case 4:MessageBoxA(hwnd,"多行编辑框修改",0,0);break;
				//}
			}
			else if(HIWORD(wParam) == BN_CLICKED)//有键被按下
			{
				switch(LOWORD(wParam))//一个int值，这里是按钮的id
				{
				case 5:
					{
						//EM_GETLINECOUNT:获取多行编辑框中的行数
						int r = SendMessage(g_hWnd[4],EM_GETLINECOUNT,0,0);
						char buf[32];
						sprintf_s(buf,32,"有%d行",r);
						MessageBoxA(g_hWnd[0],buf,0,MB_OK);
						break;
					}
				case 6:
					{
						//EM_GETLINE:获取单行编辑框中的字符串
						//获取多行编辑框中指定行的字符串
						char buf[256] = {};
						*((short*)buf) = 256;//前2个字节是数组的大小
						int r = SendMessage(g_hWnd[4],EM_GETLINE,
							1,//多行编辑框中的指定行的下标(0开始),如果是单行，则忽略本参数
							(__w64 long)buf);//用于得到字符串的字符数组
						
						MessageBoxA(g_hWnd[0],buf,0,MB_OK);
						break;
					}
				case 7:
					{
						//EM_LINEINDEX:得到指定行的首字符在整个字符串中的下标
						int r = SendMessage(g_hWnd[4],EM_LINEINDEX,
							-1,//指定的行数，若为-1则为当前正在编辑的行
							0);
						char buf[256] = {};
						sprintf_s(buf,256,"当前正在编辑的行的首字符在整个字符串中的下标%d",r);
						MessageBoxA(g_hWnd[0],buf,0,MB_OK);
						break;
					}
				case 8:
					{
						//EM_LINEFROMCHAR:得到指定下标的字符所在的行的行数
						int r = SendMessage(g_hWnd[4],EM_LINEFROMCHAR,
							-1,//指定的下标，若为-1则为当前正在编辑的行
							0);
						char buf[256] = {};
						sprintf_s(buf,256,"当前正在编辑的行数%d",r);
						MessageBoxA(g_hWnd[0],buf,0,MB_OK);
						break;
					}
				}
			}
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

	g_hWnd[0] = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 "编辑框",//窗口标题栏文字
							 WS_OVERLAPPEDWINDOW,//窗口风格
							 CW_USEDEFAULT,//窗口的左上角x坐标
							 CW_USEDEFAULT,//窗口的左上角y坐标
							 CW_USEDEFAULT,//窗口的宽（像素）
							 CW_USEDEFAULT,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0

	//编辑框的风格
	//ES_AUTOHSCROLL:自动水平卷动
	//ES_AUTOVSCROLL:自动垂直卷动
	//ES_MULTILINE:多行
	//ES_WANTRETURN:回车换行
	//ES_PASSWORD:密码
	//ES_READONLY:只读

	//单行编辑框
	g_hWnd[1] =  CreateWindow("edit",//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 "1:单行编辑框",//窗口标题栏文字
							 WS_VISIBLE | WS_CHILD | WS_BORDER,//WS_BORDER:细边框
							 0,//窗口的左上角x坐标
							 0,//窗口的左上角y坐标
							 200,//窗口的宽（像素）
							 30,//窗口的高（像素）
							 g_hWnd[0],//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 (HMENU)1,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);

	//只读
	g_hWnd[2] =  CreateWindow("edit",//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 "2:只读编辑框",//窗口标题栏文字
							 ES_READONLY | WS_VISIBLE | WS_CHILD | WS_BORDER,//WS_BORDER:细边框
							 0,//窗口的左上角x坐标
							 40,//窗口的左上角y坐标
							 200,//窗口的宽（像素）
							 30,//窗口的高（像素）
							 g_hWnd[0],//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 (HMENU)2,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);

	//密码
	g_hWnd[3] =  CreateWindow("edit",//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 "3:密码编辑框",//窗口标题栏文字
							 ES_PASSWORD | WS_VISIBLE | WS_CHILD | WS_BORDER,//WS_BORDER:细边框
							 0,//窗口的左上角x坐标
							 80,//窗口的左上角y坐标
							 200,//窗口的宽（像素）
							 30,//窗口的高（像素）
							 g_hWnd[0],//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 (HMENU)3,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);

	//多行
	//WS_HSCROLL:窗口自带的水平滚动条
	//WS_VSCROLL:窗口自带的垂直滚动条
	g_hWnd[4] =  CreateWindow("edit",//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 "4:多行编辑框",//窗口标题栏文字
							 ES_WANTRETURN | ES_AUTOVSCROLL | ES_MULTILINE| ES_AUTOHSCROLL
							 |WS_HSCROLL|WS_VSCROLL
							 | WS_VISIBLE | WS_CHILD | WS_BORDER,//WS_BORDER:细边框
							 0,//窗口的左上角x坐标
							 120,//窗口的左上角y坐标
							 200,//窗口的宽（像素）
							 100,//窗口的高（像素）
							 g_hWnd[0],//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 (HMENU)4,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);

	char* bn[] = {"EM_GETLINECOUNT","EM_GETLINE","EM_LINEINDEX","EM_LINEFROMCHAR"};

	for(int i = 0; i < 4;++i)
	{
		g_hButton[i] =  CreateWindow("button",//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 bn[i],//窗口标题栏文字
							 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,//WS_BORDER:细边框
							 250,//窗口的左上角x坐标
							 i * 60,//窗口的左上角y坐标
							 200,//窗口的宽（像素）
							 30,//窗口的高（像素）
							 g_hWnd[0],//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 (HMENU)(i + 5),//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);
	}
	ShowWindow(g_hWnd[0],nCmdShow);
	UpdateWindow(g_hWnd[0]);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}


////获取当前窗口的父窗口
//HWND parentHwnd = GetParent(hwnd);

//SentMessage(parentHwnd,WM_COMMAND,)//通知父窗口响应某个事件WM_COMMAND