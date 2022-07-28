#include <iostream>

int a;
class X
{
public:
	int a;
	void f(int a)
	{
		a = 1; //形参a
		this->a = 1; //成员变量a
		::a = 1; //全局变量a
	}
};

void ff()
{
	std::cout<<"ff"<<std::endl;
}
class B
{
public:
	void ff()
	{
		std::cout<<"B::ff"<<std::endl;
	}
	void y()
	{
		ff();
		::ff();
	}
};

void main()
{
	B b;
	b.y();

	system("pause");
}