//#pragma comment(lib,"User.lib")命令包含
//静态库文件。
//其中：lib是指引用的是静态库文件，
//"User.lib"是指要用的库文件的名称

#include <iostream>
#include "UseLib.h"

//是在链接阶段去指定的库中查找需要的东西的定义
#pragma comment(lib,"User.lib")

void main()
{
	 x = 1;
	 y();
	 a = 500;
	 b = 5000;
	 c();
	 system("pause");
}

//system是C语言的库函数,它的定义
//不是以源代码的形式提供的，而是放在
//库中,它所在的库是一个比较特殊的库，
//这个库称为C语言运行时库，只要C.C++
//工程都会自动去链接这个C语言运行时库，
//这个库中是所有的C语言库函数，全局变
//量的定义
//运行时库放置的目录：
//C:\Program Files\Microsoft Visual Studio 8\VC\lib
//它是一种隐藏具体代码实现的方法