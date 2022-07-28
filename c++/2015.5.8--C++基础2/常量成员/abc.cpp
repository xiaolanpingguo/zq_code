#include <iostream>
#include <assert.h>

class A
{
public:
	//一旦类中有符号常量，那么这个类就必须写
	//构造，并且要在构造中使用成员初始化列表
	//去对这些符号常量进行初始化
	const int a;
	A():a(1) //初始化
	{
		//a = 1; //赋值
	}

	int b;

	void f1()
	{
		b = 1;
		int x = b;
	}

	//常量成员函数，这种函数中是
	//不能对成员变量进行写入操作
	void f2() const
	{
		//b = 1; //不允许
		int x = b; //可以
	}
};

void main()
{
	A x;
	
	system("pause");
}