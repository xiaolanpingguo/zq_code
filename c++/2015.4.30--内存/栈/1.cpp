#include <iostream>
#include <windows.h>

//x分配
//b分配
//a分配
//c分配
//c释放
//a释放
//b释放
//y分配
//b分配
//a分配
//c分配
//c释放
//a释放
//b释放
//b分配
//a分配
//c分配
//c释放
//a释放
//b释放
//y释放
//x释放

int f(int a, int b)
{
	//我们定义非静态局部变量的时候，默认都是auto类型
	auto int c = a + b;
	return c;
}

void main()
{
	int x = f(1, 2);
	int y = f(x, f(4, 5));
	
	system("pause");
}