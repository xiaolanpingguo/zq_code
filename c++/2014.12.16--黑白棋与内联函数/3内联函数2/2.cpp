#include "1.h"
#include<iostream>

inline int add2(int a,int b)
{
	return a + b;
}

void main()
{
	add1(1,2);
	add2(1,2);
	system("pause");
}
//比如有些三维引擎里面一些调用非常频繁的函数会被写成
//内联函数，因为引擎追求的就是效率第一