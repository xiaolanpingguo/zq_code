#include <iostream>

int x1;
void y1()
{
	std::cout<<x1<<std::endl;
}
//static用法2:修饰全局变量和函数
//01)被static修饰的全局变量和函数在链接的时候
//并不是整个工程可见,只是在其源文件可见,也就是
//说下面的x2,y2的定义在链接的时候不能被1.cpp中
//的函数发现，只能被2.cpp中的函数发现
//02)简单的说就是被static修饰的全局变量，函数只
//能被其所在的源文件中的函数访问.

static int x2;

static void y2()
{
	std::cout<<x1<<std::endl;
}

void z()
{
	x2 = 200;
	y2();
}

//通过static来保护数据
static int a[10];
int* GetNum(int index)
{
	if(index < 0 || index >= 10)
		return 0;
	else
		return a + index;
}

void SetNum(int index,int Number)
{
	if(index < 0 || index >= 10)
		return;
	else
		a[index] = Number;
}



