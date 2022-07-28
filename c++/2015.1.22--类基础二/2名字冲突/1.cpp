#include<iostream>

int a;
void f1()
{
	int a;
	a = 1;//局部a
	::a = 2;//全局a
}

class A
{
	int a;
public:
	void f2()
	{
		int a;
		a = 1;//局部
		this->a = 2;//成员
		::a = 3;//全局
	}
};


void main()
{
	A x;
	x.f2();
	system("pause");
}
