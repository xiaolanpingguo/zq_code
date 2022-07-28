#include <windows.h>

#define _CLIENT_W 640
#define _CLIENT_H 480

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
	case WM_PAINT: //绘制消息
		{
			//凡是在窗口客户区中出现了无效区域
			//就会导致本消息被投递到消息对立中
			//无效区域的产生可以通过下面几种途径
			//1）本窗由被覆盖变为不被覆盖
			//2）尺寸发生变化（由CS_HREDRAW、CS_VREDRAW决定的）
			//3）InvalidateRect可以设置无效区域

			//在WM_PAINT消息中，BeginPaint和EndPaint
			//是必须写的，不写会出错，这对函数是本消
			//息的专用函数，BeginPaint用于得到绘图设
			//备，EndPaint用于释放绘图设备，我们必须
			//拥有绘图设置才可以使用各种绘图函数（绘
			//图函数的第一个参数往往都是绘图设备，绘
			//图设备的类型是HDC），绘图设备中保留有
			//用什么颜色绘制物体，在哪个地方绘制物体
			//，这些重要信息将指示绘图函数进行具体的
			//绘制
			PAINTSTRUCT ps; //可以得到一些和绘图有关的信息，但是一般都没有用
			HDC dc = BeginPaint(hwnd, &ps); //通过指定窗口创建的绘图设备，那么绘制的坐标就是制定窗口的客户区

			//绘图代码必须写在BeginPaint和EndPaint之间

			//线段绘制

			//设置起始点
			MoveToEx(
				dc, //绘图设备
				100, //线段起始点x坐标
				100, //线段起始点y坐标
				0); //用于得到上一次绘制线段的终止点的POINT对象地址，如果不想得到填0即可

			//根据已经设置的起始点和指定的终止点绘制线段
			LineTo(
				dc, //绘图设备
				300, //线段终止点x坐标
				200); //线段终止点y坐标

			POINT p;
			MoveToEx(dc, 150, 150, &p); //此处的p可以得到(300,200)
			LineTo(dc, p.x, p.y);

			//矩形绘制
			Rectangle(
				dc, //绘图设备
				200, //矩形左上角x
				300, //矩形左上角y
				400, //矩形右下角x
				400); //矩形右下角y

			//圆形绘制
			Ellipse(
				dc, //绘图设备
				200, //椭圆的外切矩形左上角x
				300, //椭圆的外切矩形左上角y
				400, //椭圆的外切矩形右下角x
				400); //椭圆的外切矩形右下角y

			Ellipse(dc, 250, 350, 400, 400);

			//文字绘制，文字区域是一个矩形区域，默认是白色
			TextOutA(
				dc, //绘图设备
				0, //文字区域左上角x
				0, //文字区域左上角y
				"123abc你好", //文字
				(int)strlen("123abc你好")); //要绘制的文字长度

			EndPaint(hwnd, &ps);

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
	wc.hbrBackground = (HBRUSH)COLOR_MENU;
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