#include<iostream>

extern int a;

//全局变量可以初始化
int a = 2;

void f()
{
	a = 1;
}

void main()
{
	std::cout<<a<<std::endl;
	f();
	std::cout<<a<<std::endl;
	system("pause");
}