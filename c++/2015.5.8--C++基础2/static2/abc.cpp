#include <iostream>
#include <assert.h>
#include "1.h"

//用法1：修饰局部变量
//1）被修饰的局部变量被放在静态内存区
//2）初次执行静态局部变量的定义语句时候分配内存
//3）退出入口点函数之后释放内存
//4）相当于就是一个只被某个函数访问的全局变量
int f1()
{
	static int a;
	++a;
	return a;
}

void main()
{
	for (int i = 0; i < 5; ++i)
		std::cout<<f1()<<std::endl;

	a1 = 1;
	b1();

	//a2、b2只能被1.cpp中的函数访问，abc.cpp中的函数不能访问
	//a2 = 1;
	//b2();
	f(); //但是可以通过类型这种方式间接访问被static修饰的全局变量和全局函数

	A x1, x2;
	x1.a1 = 1;
	x2.a1 = 2; //非静态成员变量是每个类对象各自都有一份
	std::cout<<x2.a1<<std::endl;
	x1.a2 = 3; //静态成员变量是每个类对象共享一份
	std::cout<<x2.a2<<std::endl;
	std::cout<<A::a2<<std::endl;
	//std::cout<<A::a1<<std::endl; //非静态成员变量是不能直接用类名::来访问的

	system("pause");
}

//因为1.cpp中的a2无法被abc这个文件看到，所以再在abc中定义
//一个全局变量a2是可以的，而且在abc.cpp中访问a2那么一定是
//下面的a2，在1.cpp中访问的a2就是1.cpp中定义的a2，相当于
//工程中有下面两个a2
//1.cpp中的全局变量a2
//全局变量a2
int a2;