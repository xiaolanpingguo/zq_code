#include <iostream>

class A
{
	int a;
	friend class B;

public:
	A();
	
};

class B
{
	int b;
public:
	B()
	{
		A x;
		x.a = 1;
	}

	void f()
	{
		A x;
		x.a = 1;
	}
};

//A::A()
//{
//	{
//		B b;
//		b.b = 1;
//	}
//}
void main()
{
	//友元是单向的，B是A的友元，A不是B的友元
	//所以B中成员函数能访问A中私有成员，但A
	//中的成员不能访问B中的私有成员
	system("pause");
}