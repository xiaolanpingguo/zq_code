#include <windows.h>

#define _CLIENT_W 640
#define _CLIENT_H 480

LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg, //消息值
							WPARAM wParam, //消息的附加参数1
							LPARAM lParam) //消息的附加参数2
{
	//凡是我们处理过的消息，都应该返回0

	switch (uMsg)
	{
	case WM_CREATE: //创建
		{
			//WM_CREATE是窗口刚刚被创
			//建出来的时候被触发的
			OutputDebugStringA("WM_CREATE\n"); //显示字符串到输出窗口
			return 0;
		}
	case WM_ACTIVATEAPP: //激活或反激活
		{
			//窗口有两种状态，一种是激活，另外一种是
			//非激活，所谓激活状态就是窗口位于整个桌
			//面的最上层，本消息是窗口从非激活变为激
			//活，或者从激活变为非激活的时候触发的，
			//注意wParam如果为TRUE表示从非激活变为激
			//活，如果为FALSE表示从激活变为非激活
			if (wParam == TRUE)
				OutputDebugStringA("WM_ACTIVATEAPP - 非激活->激活\n");
			else
				OutputDebugStringA("WM_ACTIVATEAPP - 激活->非激活\n");
			return 0;
		}
	case WM_CLOSE: //关闭
		{
			//点击窗口右上角[X]或者点击系统菜单的[关
			//闭]或者Alt+F4，就会触发本消息，默认消息
			//处理函数DefWindowProc对本消息的处理是调
			//用DestroyWindow来销毁窗口，并且DestroyWindow
			//函数会投递一个WM_DESTROY消息到消息队列中
			//，所以我们如果不管本消息那么我们自然会
			//收到WM_DESTROY消息，注意我们收到WM_DESTROY
			//消息的时候窗口已经被销毁

			int r = MessageBoxA(hwnd, "是否关闭？", "提示", MB_YESNO);

			//可以通过消息框的返回值来确定点击了什么按钮退出的
			if (r == IDYES)
				break; //跳出switch语句块让DefWindowProc来处理本消息
			else
				return 0;
		}
	case WM_DESTROY: //销毁
		{
			//窗口被销毁之后收到的消息，此时窗口已经不能使用了，一
			//般来说，我们会在本消息中调用PostQuitMessage，这个函数
			//的作用就是往消息队列中投递一个WM_QUIT消息，这个消息将
			//导致GetMessage函数返回假
			PostQuitMessage(0);
			return 0;
		}
	case WM_QUIT: //退出
		{
			//WM_QUIT消息会导致消息循环的退出，所以在本函数
			//中根本收不到WM_QUIT消息
			return 0;
		}
	}

	//本函数一旦遇到WM_CLOSE就会调用DestroyWindow来
	//销毁窗口，而且DestroyWindow会投递一个WM_DESTROY
	//消息到本线程的消息队列中，所以紧接着我们就会
	//在上面的switch语句块收到WM_DESTROY消息
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