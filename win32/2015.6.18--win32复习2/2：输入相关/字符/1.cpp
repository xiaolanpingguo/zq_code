#include <windows.h>

#define _CLIENT_W 640
#define _CLIENT_H 480

char str[1024] = {};
int len = 0;
bool db = false; //双字节文字标志
char head; //双字节文字首字节

LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg, //消息值
							WPARAM wParam, //消息的附加参数1
							LPARAM lParam) //消息的附加参数2
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_CHAR:
		{
			//这个消息是通过WM_KEYDOWN、WM_KEYUP被
			//TranslateMessage结合现在使用的输入法
			//得到的一个字符消息，如果这个字符是单
			//字节文字，那么本消息就只会触发一次，
			//并且wParam里面就是这个字符的整数编码
			//值，如果字符是双字节文字，那么本消息
			//就被触发两次，并且两次的wParam中分别
			//是文字的首字节和尾字节

			//Windows编程是面对的C语言，而不是C++
			//语言，C语言中没有bool类型，所以微软
			//为了方便真假判断，用int表示BOOL，用
			//0和1表示TRUE和FALSE，下面这个函数是
			//判断一个字节是否是一个双字节文字的
			//首字节，如果是就返回TRUE反之返回FALSE
			//BOOL IsDBCSLeadByte(BYTE TestChar);

			//有时候我们需要详细判断一个文字是
			//单字节文字还是双字节文字，因为单
			//字节的文字中有些不是可以打印出来
			//的文字，比如回车、退格，这些我们
			//需要特殊处理，而双字节文字是一定
			//可以打印出来的

			//str[len++] = (char)wParam;
			//SetWindowTextA(hwnd, str);

			//此时应该接收双字节文字的尾字节
			if (db)
			{
				char tail = (char)wParam;
				//此时已经得到了head、tail两个首尾字节
				str[len++] = head;
				str[len++] = tail;
				db = false;
				SetWindowTextA(hwnd, str);
				return 0;
			}

			//该文字是双字节文字的首字节
			if (IsDBCSLeadByte((BYTE)wParam))
			{
				head = (char)wParam;
				db = true;
			}
			//该文字是单字节文字
			else
			{
				//退格键
				if (8 == wParam)
				{
					if (len > 0)
					{
						bool last_db; //标志最后一个文字是否是双字节
						for (int i = 0; i < len; ++i)
						{
							if (IsDBCSLeadByte(str[i]))
							{
								last_db = true;
								i += 1;
							}
							else
								last_db = false;
						}
						str[len -= (last_db ? 2 : 1)] = 0;
						SetWindowTextA(hwnd, str);
					}
				}
				else
				{
					//本函数可以判断一个单字节文
					//字是不是可打印文字
					if (isprint((int)wParam))
					{
						str[len++] = (char)wParam;
						SetWindowTextA(hwnd, str);
					}
				}
			}

			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "123abc";

	RegisterClass(&wc);

	//可以根据客户区大小来计算窗口大小
	int sw = GetSystemMetrics(SM_CXSCREEN); //得到桌面的宽
	int sh = GetSystemMetrics(SM_CYSCREEN); //得到桌面的高
	RECT cr //cr得到客户区的位置、尺寸
		=
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		(sw - _CLIENT_W) / 2 + _CLIENT_W,
		(sh - _CLIENT_H) / 2 + _CLIENT_H
	};
	//根据传入的客户区位置、尺寸来计算窗口应该有的位置、尺寸
	AdjustWindowRect(
		&cr, //客户区矩形，本函数执行完毕之后会填入窗口矩形
		WS_OVERLAPPEDWINDOW, //窗口风格
		FALSE); //有无菜单

	HWND hwnd = CreateWindowA(
		wc.lpszClassName, //使用的窗口类别结构体的名字
		"hello world", //窗口标题栏文字
		WS_OVERLAPPEDWINDOW, //窗口风格
		cr.left, //窗口左上角x坐标
		cr.top, //窗口左上角y坐标
		cr.right - cr.left, //窗口宽
		cr.bottom - cr.top, //窗口高
		HWND_DESKTOP, //父窗口，一般来说填写桌面窗口
		0, //菜单句柄，不用就填写0
		wc.hInstance, //应用程序实例句柄
		0); //保留参数

	//可以得到客户区的尺寸
	RECT r; //矩形结构体：左上角（left，top），右下角（right，bottom）
	GetClientRect(hwnd, &r);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}