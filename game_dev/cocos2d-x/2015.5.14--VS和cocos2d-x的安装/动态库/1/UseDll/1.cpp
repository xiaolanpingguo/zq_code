#include <iostream>

int add(int, int);
#pragma comment(lib, "TestDll.lib")

//add的定义是在动态库中，但是要链接的时候必须
//用引入库进行链接，引入库中有一些和动态相关联
//的信息

//声明是必要的，用于编译
//引入库是必要的，用于链接
//动态库是必要的，用于运行

//每个exe程序中都包含有自己调用
//那些动态库的信息，系统会在当前
//exe所在目录、Windows目录、System32
//目录下面去寻找这些需要的动态库，找
//不到就报错

void main()
{
	std::cout<<add(1, 2)<<std::endl;

	system("pause");
}

