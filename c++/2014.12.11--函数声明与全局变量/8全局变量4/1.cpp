#include<iostream>

int x;

void f()
{
	std::cout<<x<<std::endl;
}

void main()
{
	//局部变量没有声明,在使用之前一定要
	//定义出来.
	//extern int a;
	//a = 1;
	//int a;
	int x;
	x = 1;//访问的是局部变量x
	f();
	//一旦有全局变量和局部变量发生名字冲突，
	//可以使用::放在变量名前面来访问全局的变量，
	//不加::就是表示访问局部变量.

	::x = 2;//访问的是全局变量x
	f();

	system("pause");
}