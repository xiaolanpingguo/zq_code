#include <iostream>

//告知编译器TestLib.lib要参与本工程的链接
#pragma comment(lib, "TestLib.lib")

//下面的这些东西的定义都在TestLib.lib，我们只能
//用而无法查看其源代码
extern int a;
extern int x;
void b();
void y();

void main()
{
	a = 1;
	b();
	x = 2;
	y();

	system("pause");
}