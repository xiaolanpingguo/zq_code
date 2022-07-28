#include<iostream>


//静态
//static：
//01)修饰局部变量

int f1()
{
	int a = 0;//分配a的内存
	a += 1;
	return a;
}//释放a的内存

int f2()
{
	//static 用法1:修饰局部变量的定义
	//01)被修饰的局部变量是开辟在静态内存区(全局变量所在)
	//02)其定义语句(可以有初始化)只是在最初执行一次，其后将
	//不被执行
	//03)其分配内存是在最初执行其定义语句的时候分配,在退出入口点
	//函数之后释放内存，也就是说其分配释放都只有一次。和全局变量
	//相同,和局部变量不同
	//04)被static修饰的局部变量相当于只是被其所在的函数访问的全局
	//变量,就比如下面的a相当于只是被f2函数访问的全局变量
	//05)被static修饰的局部变量默认初始化为0
	static int a = 0;
	a += 1;
	return  a;
}

void main()
{
	for(int i = 0; i < 5; ++i)
		std::cout<<f1()<<" ";
	std::cout<<std::endl;

	for(int i = 0; i < 5; ++i)
		std::cout<<f2()<<" ";
	std::cout<<std::endl;
	system("pause");
}
