#include <iostream>
#include <assert.h>

class A
{
	int a;
public:
	A(int x)
	{
		a = x;
		std::cout<<"构造"<<a<<std::endl;
	}
	~A()
	{
		std::cout<<"析构"<<a<<std::endl;
	}
};

void f1()
{
	A a3(3);
	static A a5(5);
}
void f2()
{
	A a4(4);
	static A a6(6);
}
void main()
{
	//int a = 1; //完全等同于auto int a = 1;
	//short x = 1; //完全等同于auto short int x = 1;
	//long y = 1; //完全等同于auto long int y = 1;
	f2();
	A a1(1);
	f2();
	system("pause");
}
A a2(2);