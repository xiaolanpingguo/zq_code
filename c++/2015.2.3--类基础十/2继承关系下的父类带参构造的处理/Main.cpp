#include <iostream>

class A
{
public:
	A(int a)
	{}
};

class B
{
	A x;
public:
	B()
		:
	x(1)
	{
	}
};

class C
{
	A x;
public:
	C(int y)
		:
	x(y)
	{
		
	}

};

class D:public A
{
public:
	D()
		:
	A(1)//使用成员初始化列表为父类构造传递参数
	{
	}
};

class E:public A
{
public:
	E(int y)
		:
	A(y)
	{}
};

//包含关系：B包含A C包含A
//继承：D继承与A，E继承A
//在这两种关系中,如果A的构造要求有参，则必须使用
//成员列表初始化列表来进行初始化，如果是包含关系
//使用被包含的（类的对象）成员变量名。如果是继承，则使用父类的类名
void main()
{
	B b;
	C c(7);
	D d;
	E e(1);
	system("pause");
}