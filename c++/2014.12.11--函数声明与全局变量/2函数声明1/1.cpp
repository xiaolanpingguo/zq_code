#include<iostream>

//函数的声明
//全局变量
//头文件

//函数的声明
//告知下面的代码，在整个工程中有一个返回值为
//int，名字为add,形式参数表为(int,int)的函数可以使用
int add(int,int);//函数声明中的形式参数表可以不写参数名称
//函数声明在工程中可以有任意次
int add(int,int);
int add(int,int);
int add(int,int);
int add(int,int);
int add(int,int);
int add(int,int);

int add1(int a,int b);

//函数定义在工程中只能有一次
//int add1(int a,int b)
//{
//	return a + b;
//}
//int add1(int a,int b)
//{
//	return a + b;
//}

void main()
{
	add1(1,2);
	system("pause");
}

int add1(int a,int b)
{
	return a + b;
}

float add1(float a,float b)
{
	return a + b;
}
//
//float add1(float a,float b)
//{
//	return a + b;
//}
//函数的定义：
//编译器一旦发现函数的定义，就会开辟内存空间，然后
//将函数中的每句代码通过一定的规则变为CPU可以识别的
//机器指令，并把这些指令放入到刚刚开辟的内存空间中，
//这个内存区称为指令内存区
//同一个名字的函数的定义只能有一次，如果可以函数重载
//则同一个名字，形式参数表的函数的定义只能有一次

