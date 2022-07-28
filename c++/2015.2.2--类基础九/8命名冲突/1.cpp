#include <iostream>
int a;
class A
{
public:
	int a;
	void f(int a)
	{
		a = 1;
		this->a = 1;
		::a = 2;
	}
};

class B : public A
{
public:
	int a;
	void b(int a)
	{
		a = 1;
		this->a = 2;//B的成员变量a
		A::a = 4;//A的成员变量a
		::a = 4;
	}
};

void main()
{
	A x;
	x.a = 1;
	B y;
	y.a = 1;
	y.A::a = 3;//访问A中定义的a

	B* y1 = &y;
	y1->A::a = 5;//访问A中定义的a
	system("pause");
}