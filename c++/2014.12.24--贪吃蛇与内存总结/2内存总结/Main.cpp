#include <iostream>

void f(char** a)
{
	*a = (char*)malloc(10);
}

//栈
//常量内存区
//静态内存区(全局，static修饰的局部变量)
//堆

//数据内存区
//指令内存区

void main()
{
	char* p = 0;
	f(&p);
	strcpy_s(p,4,"abc");
	std::cout<<p<<std::endl;
	system("pause");
}