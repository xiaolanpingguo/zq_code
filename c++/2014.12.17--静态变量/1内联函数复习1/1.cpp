#include<iostream>

//普通函数
//01）会被编译器处理为单独的指令内存区，
//并将指令区的首地址命名为这个函数的名称.
//无论调用多少次，其指令只有一份.
//02)普通函数的执行一定有入栈和出栈的过程
int add1(int a,int b)
{
	return a + b;
}

//内联函数(用inline修饰的函数)
//01)没有单独的指令内存区，它将被
//展开在调用它的函数中,有多少次调用就
//有多少份指令
//02）内联函数没有出入栈的过程
//03)调用频繁，指令又较少的函数适合写成内联函数
inline int add2(int a,int b)
{
	return a + b;
}
void main()
{
	int x1 = add1(1,2);
	int x2 = add2(2,3);
	int y1 = add1(3,4);
	int y2 = add2(4,5);
	system("pause");
}