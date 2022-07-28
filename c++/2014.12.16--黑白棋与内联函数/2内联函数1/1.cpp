#include<iostream>

//内联函数
//指令内存区，数据内存区
//寄存器
//静态static
//多线程 _beginthreadex();

//内联函数  inline


//普通函数
//01)会被编译器处理成单独的指令内存区，
//并将指令区的首地址命名为这个函数的名字,
//无论有多少次调用，普通函数的指令只有一
//份
//02)普通函数的执行一定是有入栈，出栈的过程
int add1(int a,int b)
{
	return a + b;
}

//内联函数->被inline修饰的函数
//01)内联函数没有单独的指令内存区，它将被展开
//在调用它的函数中,有多少次调用就有多少份指令
//02)内联函数没有入栈和出栈的过程
//03)调用频繁，指令较少的函数适合于写成内联函数
inline int add2(int a,int b)
{
	return a + b;
}
void main()
{
	int x1 = add1(1,2);
	int y1 = add2(2,3);
	int x2 = add1(3,4);
	int y2 = add2(4,5);
	
	system("pause");
}