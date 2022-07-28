#include<iostream>

class A
{
public:
	A()
	{
		std::cout<<"无参"<<std::endl;
	}
	A(int a)
	{
		std::cout<<"带参"<<std::endl;
	}
	A(int a,int b)
	{
		std::cout<<"带参1"<<std::endl;
	}
	A(const char* c)
	{
		std::cout<<"带参2"<<std::endl;
	}
};

void main()
{
	A a1;
	A a2(1);
	A a3(1,2);
	//如果一个构造函数只有一个形参,那么
	//该构造函数的调用可以用 = 替代
	A a4 = 3;

	A a5("abc");

	A a6 = "abc";

	system("pause");
}