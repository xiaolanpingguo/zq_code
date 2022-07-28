#include<iostream>

int c1;

void f1(int a1)
{
	int b1;//普通函数可以访问全局变量，形参，局部变量
	a1 = 1;
	b1 = 1;
	c1 = 1;
}

int c2;
class XYZ
{
public:
	int d2;
	void f2(int a2)
	{
		//成员函数可以访问形参，局部变量，全局变量，成员变量.
		int b2;
		a2 = 2;
		b2 = 2;
		c2 = 2;
		d2 = 2;
	}
};

void main()
{
	f1(3);

	XYZ xyz;
	xyz.f2(2);
	system("pause");
}