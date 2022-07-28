#include<iostream>

int a;
int f1()
{
	return a;
}

//返回值是被全局变量a初始化的引用
int& f2()
{
	return a;
}

int& f3()
{
	//用局部的a初始化引用
	//得到一个已经结束的函数的栈内存中的变量没有意义
	int a = 0;
	return a;
}


int& f4()
{
	int* a = new int;
	*a = 0;
	return *a;
}
void main()
{
	//f1() = 1;
	f2() = 1;
	f3() = 2;

	delete &(f4() = 3);
	system("pause");
}