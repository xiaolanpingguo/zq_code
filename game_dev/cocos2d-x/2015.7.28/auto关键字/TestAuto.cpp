// TestAuto.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	auto int a = 1; //等同于int a = 1;
	//auto b = 2; //c99不支持
	//与auto（自动的）相反的关键字是static
	//auto定义栈
	//static定义静态

	//其它的简写
	short int x = 1; //等同于short x = 1;
	long int y = 2; //等同于long y = 2;
	signed int z = 3; //等同于int z = 3; signed表示有符号

	return 0;
}

