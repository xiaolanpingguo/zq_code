#include<iostream>
#include "2.h"

//内联函数
//内联函数的写法和普通函数有区别
//不能再h文件写声明，cpp写定义。
//内联函数应该直接写在cpp中
//内联函数有点像宏但不是宏

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

//比如有些三维引擎里面，调用频繁的函数会被写成内联函数。
//引擎是追求效率第一