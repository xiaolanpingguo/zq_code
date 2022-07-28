#include <windows.h>

//WinMain是窗口程序的入口点函数
//hInstance：代表本程序自己的应用程序实例句柄（一个exe文件可以生成多个实例，即多个运行起来的程序）
//hPrevInstance：代表上一个被启动的应用程序实例的句柄（Win32编程中该形参不被使用了，都会被设置为0）
//lpCmdLine：传入给本实例的字符串
//nCmdShow：操作系统根据当前的情况传给我们的窗口的显示方式，可以用在ShowWindow里面

//在Windows编程中有句柄的概念，所谓句柄有两点需要注意
//1）句柄的本质都是指针
//2）句柄往往是代表了某种程序设计中的抽象事物
//3）Windows编程中有大量的句柄，这些句柄类型都以H开头
//比如在C编程中，C风格的顺序表或链表其实都用到了句柄这种概念
//typedef struct _SQLIST
//{
//	int size;
//	int length;
//	DATA* data;
//}* SQLIST;
//SQLIST createSQLIST();
//void destroySQLIST(SQLIST sqlist);
//bool insertSQLIST(SQLIST sqlist, DATA data, int pos);
//...
//SQLIST这个类型本身就是一个指针，在我们的程序中它代表了顺序
//表，某种意义上它就是一个句柄
//HINSTANCE的本质是HINSTANCE__结构体类型的指针，它代表一个应用程序实例
//struct HINSTANCE__
//{
//	int unused;
//};
//typedef struct HINSTANCE__* HINSTANCE;

//在Windows编程中，凡是成员变量有字符串的结构体、形式参数或返回值有
//字符串的函数，其实都有两个版本，一个是A版本，一个是W版本，A版本是
//多字节字符串（char*），W版本是双字节字符串（wchar_t*），我们在代码
//中比如写下MessageBox，其实这个不是一个函数而是一个宏，这个宏会根据
//当前工程中是否定义了UNICODE宏来决定具体是被MessageBoxA还是MessageBoxW
//所替换，UNICODE宏定义与否可以在[项目]->[属性]->[常规]->[字符集]中
//进行调整，如果选择了Unicode字符集，那么编译器在编译项目的时候会自动
//在所有cpp被编译之前加上UNICODE宏，这将导致函数的宏会W版本替换，反之
//如果我们选择多字节字符集，那么就没有UNICODE宏，所有的函数的宏会被A
//版本所替换，也可以在程序中显示指定具体用A还是W版本

//函数的调用方式，主要是和函数的形式参数入栈的顺序有关系，以及和
//谁来释放栈内存有关系，一般的编程中我们无需过问这些东西
//__cdecl：形式参数入栈顺序是从右到左，调用者清除栈内存（这个处理也叫出栈）
//__stdcall：形式参数入栈顺序是从右到左，被调用者清除栈内存
//__fastcall：前两个小于等于4字节的参数被放入ECX、EDX寄存器，其它形式参数入栈顺序是从右到左，被调用者清除栈内存
//我们自己写的函数是可以在[项目][属性][C\C++][高级][调用约定]中选择的

//__w64 long __stdcall WindowProc(HWND__* hwnd,
//								unsigned int uMsg,
//								__w64 unsigned int wParam,
//								__w64 long lParam)
//{
//	__w64 long ：是64位的long
//	__w64 unsigned int ：是64位的unsigned int
//}

//窗口消息处理函数是被操作系统调用的，会把消息的
//的值和消息的附加参数传递给这个函数
LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg, //消息值
							WPARAM wParam, //消息的附加参数1
							LPARAM lParam) //消息的附加参数2
{
	switch (uMsg)
	{
		//当我们点击右上角X的时候，Windows检测到这个动作之后
		//就会填充一个WM_DESTROY消息投递到消息队列中，然后被
		//我们的GetMessage取得，最后又还给操作系统，操作调用
		//本函数来处理这个消息
	case WM_DESTROY:
		{
			//投递一个WM_QUIT消息到消息队列中，这将导
			//致GetMessage返回假，退出程序
			PostQuitMessage(0);
			return 0;
		}
	}

	//我们程序中不关心的消息就用DefWindowProc来进行
	//处理，DefWindowProc函数的作用就是系统默认的对
	//所有消息的处理
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//void f1()
//{
//	int a = 1;
//}
//void f2()
//{
//	int a = 2;
//}

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	//f1();
	//f2();
	//上面的调用会使得f1和f2中的a都在一个地址上面

	//消息框
	//MessageBox(
	//	HWND_DESKTOP, //窗口句柄，HWND_DESKTOP代表了桌面
	//	"abc", //内容
	//	"123", //标题
	//	MB_OK); //类型
	//MessageBoxA(0, "abc", "123", 0);
	//MessageBoxW(0, L"abc", L"123", 0);

	//1）填充窗口类别结构体
	WNDCLASS wc;

	//窗口类别风格
	//CS_HREDRAW：表示当窗口的水平尺寸发生改变的时候那么重绘窗口
	//CS_VREDRAW：表示当窗口的垂直尺寸发生改变的时候那么重绘窗口
	wc.style = CS_HREDRAW | CS_VREDRAW;

	//窗口消息处理函数
	wc.lpfnWndProc = WindowProc;

	//如果是窗口类别、窗口使用了额外的字节，那么就意味着操作系统
	//在注册窗口类别、创建窗口的时候会帮我们生成指定字节数的堆内
	//存，我们可以通过一些函数来得到这些内存的地址进行使用（比如
	//可以通过WM_CREATE消息得到窗口的额外字节），如果不希望创建
	//额外字节那么填写0即可

	//窗口类别额外的字节
	wc.cbClsExtra = 0;

	//窗口额外的字节
	wc.cbWndExtra = 0;

	//应用程序实例句柄
	wc.hInstance = hInstance;

	//图标
	//HICON LoadIcon( //加载1个图标并返回代表该图标的句柄
	//	HINSTANCE hInstance, //如果是从资源中加载那么填写应用程序实例句柄，如果是从外部文件或Windows已有图标中加载填写0
	//	LPCTSTR lpIconName); //图标的类型
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);

	//光标
	//HCURSOR LoadCursor( //加载1个光标并返回代表该光标的句柄
	//	HINSTANCE hInstance, //如果是从资源中加载那么填写应用程序实例句柄，如果是从外部文件或Windows已有光标中加载填写0
	//	LPCTSTR lpCursorName); //光标的类型
	wc.hCursor = LoadCursor(0, IDC_ARROW);

	//背景画刷
	//操作系统会用这个画刷来填充我们窗口的客户区
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//菜单
	//填写0表示不使用菜单
	wc.lpszMenuName = 0;

	//窗口类别结构体的名字
	wc.lpszClassName = "123abc";

	//2）注册窗口类别结构体
	RegisterClass(&wc);

	//如果窗口类别结构体中使用了菜单，而创建窗口的时候也指定
	//了菜单，那么会使用创建窗口时候指定的菜单，如果创建窗口
	//的时候没有指定菜单，那么就用窗口类别结构体中指定的菜单
	//，而所有被指定的窗口类别结构体生成的窗口都会拥有窗口类
	//别结构体中指定的菜单只要创建窗口的时候菜单填0

	//3）生成窗口
	HWND hwnd = CreateWindowA(
		wc.lpszClassName, //使用的窗口类别结构体的名字
		"hello world", //窗口标题栏文字
		WS_OVERLAPPEDWINDOW, //窗口风格
		100, //窗口左上角x坐标
		100, //窗口左上角y坐标
		640, //窗口宽
		480, //窗口高
		HWND_DESKTOP, //父窗口，一般来说填写桌面窗口
		0, //菜单句柄，不用就填写0
		wc.hInstance, //应用程序实例句柄
		0); //保留参数

	//4）显示窗口
	ShowWindow(hwnd, nCmdShow);

	//5）更新窗口，本质就是往消息队列中投递一个WM_PAINT消息
	UpdateWindow(hwnd);

	//6）消息循环

	//1）Windows为每个线程维护一个消息队列queue<MSG>
	//2）Windows随时随地都在监视当前操作系统中的每个线程
	//   创建出来的每个窗口，一旦发现这个窗口上面发生了某
	//   种既定的事情（比如我们用鼠标左键在这个窗口上面按
	//   下，这些既定的事情都是Windows已经设定好的了，都是
	//   用宏WM_XXX表示），Windows就填写一个MSG结构体对象，
	//   然后将这个结构体对象入到它所属窗口所在的线程的消息
	//   队列中，而MSG结构体对象中就有对当前发生的这件事情
	//   的数据描述，比如WM_LBUTTONDOWN中它的lParam数据中就
	//   是按下鼠标左键时候光标的坐标
	//	struct MSG
	//	{
	//		HWND        hwnd;
	//		UINT        message; //此处会被设置为WM_LBUTTONDOWN
	//		WPARAM      wParam;
	//		LPARAM      lParam; //会填写入光标当前的坐标
	//		DWORD       time;
	//		POINT       pt;
	//	};
	//3）应用程序一般应该用GetMessage或者PeekMessage从消息
	//   队列中得到队头消息，然后进行必要的处理（比如一个程
	//   序中要允许输入文字，那么就应该用TranslateMessage将
	//   键盘消息翻译为字符消息），处理完毕之后，再调用DispatchMessage
	//   将消息派发回操作系统
	//4）操作系统最后会调用我们在窗口类别结构体中填写的窗口
	//   消息处理函数来处理这个消息

	//从消息队列中得到队头消息，如果没有就
	//等待，如果有就得到并返回，如果得到的
	//消息是WM_QUIT消息，则本函数返回假，反
	//之只要不是WM_QUIT消息就返回真
	//BOOL GetMessage(
	//	LPMSG lpMsg, //从消息队列中取到的消息
	//	HWND hWnd, //要得到消息的目标窗口，如果为0，则得到本线程创建的所有窗口的消息
	//	UINT wMsgFilterMin, //消息过滤下限
	//	UINT wMsgFilterMax); //消息过滤上限

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

//HINSTANCE：应用程序实例句柄
//HICON：图标句柄
//HCURSOR：光标句柄
//HBRUSH：画刷句柄
//HWND：窗口句柄