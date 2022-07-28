#include <iostream>

int add(int a,int b)
{
	return a + b;
}
class A
{
public:
	int sub(int a,int b)
	{
		return a - b;
	}
	int mul(int a,int b)
	{
		return a * b;
	}
};

void main()
{
	int (*p)(int,int) = add;
	//p = A::mul;
	//A中的mul和sub都含有一个隐藏的指针this
	//实际会被编译为
	//int sub(A* this,int a,int b);
	//p指针要求指向的是形式参数为(int,int)，
	//返回值为int的函数,所以不能指向A中这两个函数
	
	// 无法从“int (__thiscall A::* )(int,int)”
	//转换为“int (__cdecl *)(int,int)”
	
	//int (*p1)(A*,int,int) = &A::mul;
	//类中的成员函数的地址的写法
	// &类名::成员函数名


	//类中的成员函数指针的定义如下
	//返回值(类名::*指针名)(形式参数表)

	//这里的p1是指向一个A类中的成员函数的指针，
	//且该成员函数必须是返回值为int ，形式参数表
	//为(int,int)的函数
	int (A::*p1)(int,int) = &A::mul;

	p1 = &A::sub;
	//p1 = add;
	//成员函数指针不能指向普通函数
	//普通函数指针不能指向成员函数


	A a;

	(a.*p1)(3,4);

	A* a1 = &a;

	(a1->*p1)(1,2);
	system("pause");
}
