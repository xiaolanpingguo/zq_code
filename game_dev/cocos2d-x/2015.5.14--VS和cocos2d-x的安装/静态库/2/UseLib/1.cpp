#include <iostream>
#include "TestLib.h"

//告知编译器TestLib.lib要参与本工程的链接
#pragma comment(lib, "TestLib.lib")

void main()
{
	a = 1;
	b();
	x = 2;
	y();

	system("pause");
}

//创建静态库，一般都需要生成用于链接的lib（包含定义）
//和用于编译的h（包含声明）