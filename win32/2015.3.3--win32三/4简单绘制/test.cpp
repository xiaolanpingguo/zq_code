#include <windows.h>

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
	case WM_PAINT:
		{
			//WM_PAINT:
			//1)UpdateWindow会投递WM_PAINT到消息队列中
			//2)窗口客户区出现无效区域的时候
			// a)窗口大小改变后(必须是WNDCLASS中设置CS_HREDRAW和CS_VREDRAW标记)
			// b)窗口隐藏后重新显示或者被其他窗口遮掩的部分重新可见
			// c)调用InvalidateRect,InvalidateRgn函数
			// d)调用ScrollWindow或者ScrollDC函数滚动客户区
			//非触发情况
			//1)光标穿越客户区
			//2)图标拖过客户区
			//3)显示对话框
			//4)显示菜单后释放

			//PAINTSTRUCT:用于得到当前的一些绘制信息
			//的结构体，一般没有使用
			PAINTSTRUCT ps;

			//HDC:显示设备句柄，其代表了指定的窗口的客户区的显示设备
			//,所有的Windows的绘图函数的第一个参数都是一个HDC,这些函数
			//才知道图形往哪个窗口的客户区进行绘制,HDC中包含了当前的
			//画笔，画刷，字体等信息
			
			//BeginPaint : 得到当前指定的窗口的客户区显示设备,本
			//函数只能在WM_PAINT消息中使用
			//EndPaint:释放得到的指定的窗口的客户区的显示设备，本
			//函数只能在WM_PAINT消息中使用
			//GetDC，ReleaseDC是在除WM_PAINT消息之外的地方得到和
			//释放指定窗口的客户区的显示设备。

			//所有的绘制代码应该在BeginPaint和EndPaint之间
			HDC hdc = BeginPaint(hwnd,&ps);

			//点
			POINT p;

			//设定线段的起始点(
			//显示设备，
			//起始点x，
			//起始点y,
			//用于得到上次终止点的POINT对象地址)
			MoveToEx(hdc,0,0,&p);

			//绘制线段(
			//显示设备,
			//终止点x,
			//终止点y)
			LineTo(hdc,200,100);

			MoveToEx(hdc,200,0,&p);
			LineTo(hdc,0,100);

			//绘制矩形(//黑色绘制边线，白色填充
			//显示设备，
			//左上角的x,
			//左上角的y,
			//右下角x,
			//右下角y)
			Rectangle(hdc,300,50,500,150);

			//绘制椭圆(//黑色绘制边线，白色填充
			//显示设备，
			//椭圆外切矩形左上角的x,
			//椭圆外切矩形左上角的y,
			//椭圆外切矩形右下角x,
			//椭圆外切矩形右下角y)
			Ellipse(hdc,300,50,400,250);

			//绘制单行文字(
			//显示设备,
			//文字左上角x,
			//文字左上角y,
			//文字,
			//绘制的文字的长度
			TextOutA(hdc,100,300,"123abc你好",10);
			
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
	wc.lpszClassName = L"八班";

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
							 L"WM_PAINT",//窗口标题栏文字
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

	return 1;
}