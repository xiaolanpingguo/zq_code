#include <iostream>

//只能是构造使用成员初始化列表
//成员初始化列表中写的成员变量被初始化
//成员初始化列表初始化的顺序是成员变量的顺序

class A
{
	int a,b;
	const int c;//类中的符号常量
	int& d;//类中的引用
public:
	A()
	:
	a(1),c(3),d(a)
	{
		b = 2;//这里是赋值
		//c = 3;//错误
		//成员变量中有符号常量的话，则必须通过成员
		//初始化列表进行初始化
	}

	//void f()
	//:
	//a(1)
	//{}
};


class B
{
	int* p;
	int a;
public:
	B()
	:
	a(5),p(new int[a])
	{}
};

class C
{
	int a;
	int* p;
public:
	C()
	:
	p(new int[a]),a(5)
	{}
};


void main()
{
	A x;
	//B b;

	C c;
	system("pause");
}
