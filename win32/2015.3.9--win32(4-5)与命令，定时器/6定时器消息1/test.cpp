#include <windows.h>
#include <iostream>

int x,y;
bool z2y = true;

int second = 0;
//WM_TIMER

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
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			return 0;
		}
	case WM_TIMER:
		{
			RECT r;
			GetClientRect(hwnd,&r);
			if(z2y)
			{
				if(x + 30 >= r.right)
					z2y = false;
				else
					x += 10;
			}
			else
			{
				if(x - 30 <= 0)
					z2y = true;
				else
					x -= 10;
			}

			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);
	
			Rectangle(hdc,x - 30,y - 30,x + 30,y + 30);

			EndPaint(hwnd,&ps);
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
	//HICON LoadIcon(加载图标
	//HINSTANCE hInstance,//若要使用的图标是打包到exe文件中的资源
	//                      则此处必须填写应用程序的实例句柄，如果不是
	//                      填0即可.  
	//LPCSTR lpIconName);//图标的字符串ID，如果图标是打包到exe文件中的资源
	//                     我们拿到的图标ID是整数，必须用
	//                     MAKEINTRESOURCE宏将其转换为字符串格式
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);

	//光标
	//HCURSOR LoadCursor(加载光标
	//HINSTANCE hInstance,//若要使用的光标是打包到exe文件中的资源
	//                      则此处必须填写应用程序的实例句柄，如果不是
	//                      填0即可.  
    //LPCSTR lpCursorName);光标的字符串ID，如果图标是打包到exe文件中的资源
	//                     我们拿到的光标ID是整数，必须用
	//                     MAKEINTRESOURCE宏将其转换为字符串格式
	wc.hCursor = LoadCursor(0,IDC_ARROW);

	//HBRUSH 画刷
	//操作系统用于绘制窗口背景的背景画刷
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//菜单字符串ID，如果没有则填0
	wc.lpszMenuName = 0;

	//窗口的名字
	wc.lpszClassName = "八班";

	//02)注册填充好的窗口
	RegisterClass(&wc);
	//一个窗口类别的结构体可以用于创建任意个窗口
	//,结构体中填写的某些成员变量（比如风格，图标，光标）
	//就决定了呗结构体创建出来的所有的窗口的共性,但
	//每个窗口也有自己不一样的东西，比如说大小,位置，是否有
	//菜单等等
	
	//03)用窗口类别结构体来创建窗口
	HWND hWnd = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							 "WM_TIMER1",//窗口标题栏文字
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
	ShowWindow(hWnd,nCmdShow);

	//05)更新窗口
	UpdateWindow(hWnd);

	SetTimer(hWnd, //窗口
		     0,//定时器消息ID号
			 40,//每隔多少毫秒触发一次WM_TIMER消息
			 0);//填0即可

	//06)消息循环
	//消息结构体
	//struct MSG
	//{
	//	HWND hwnd;//发生事情的窗口
	//	UINT message;//消息类型
	//	WPARAM wParam;//消息附加参数1,不同的消息含义不同
	//	LPARAM lParam;//消息附加参数2,不同的消息含义不同
	//	DWORD time;//发生事情的时间
	//	POINT pt;//发生事情时光标所在的位置(相对于桌面而言)
	//};
	//1)windows会为每个线程维护一个消息队列<MSG>
	//2)windows会随时随地的检测每个窗口上是否发生某些特定的事件
	//  那么windows就会把这个事情填充成一个MSG结构体，并将该结构体
	//  加入到产生这个窗口的线程的消息队列中，比如我们某个窗口上面
	//  按下鼠标左键,则windows会填充一个MSG如下.
	//  MSG msg;
	//  msg.hwnd = hWnd;
	//  msg.message = WM_LBUTTONDOWN;
	//  msg.wParam = MK_LBUTTON;
	//  msg.lParam = MAKELONG(光标x坐标，光标y坐标);(相对于窗口客户区)
	//	MAKELONG(WORD1,WORD2)将WORD1和WORD2组合成一个DWORD
    //  msg.time = 发生事件的时间
	//  msg.pt = 发生事件时光标所在的位置(相对于桌面)
	//  入队列(消息队列，msg)；
	//3)程序应该用GetMessage或者是PeekMessage来从队列中
	//  取得消息，并进行相关的处理,然后报消息返还给操作系统
	//4)操作系统会调用我们在窗口类别结构体中设置的窗口消息函数
	//  来处理我们返还给操作系统的消息.
	//  从消息队列中取队头消息，如果当前没有消息就等待
	//GetMessage(
 //   LPMSG lpMsg,//用于获取消息的消息结构体地址
 //   HWND hWnd,//指定获取消息的窗口，为0则获取当前线程中所有窗口的消息
 //   UINT wMsgFilterMin,//消息过滤的下限
 //   UINT wMsgFilterMax);//消息过滤的上限

	//如果得到的消息WM_QUIT消息就返回假.
	//反之就返回真。
	//下面的例子调用就只能获取到hWnd所代表的窗口的消息，而且不会得到从
	//WM_LBUTTONDOWN到WM_RBUTTONDBLCLK之间的消息
	//GetMessage(&msg,hWnd,WM_LBUTTONDOWN,WM_RBUTTONDBLCLK);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		//如果发现有WM_KEYDOWN和WM_KEYUP消息就根据当前的输入法
		//在产生一个WM_CHAR消息并投递到消息队列中
		TranslateMessage(&msg);
		//派发消息回操作系统(估计就是下面DispatchMessage来调用窗口消息函数)
		DispatchMessage(&msg);
	}

	//关闭定时器消息(窗口，消息ID号)
	KillTimer(hWnd,0);

	return 1;
}