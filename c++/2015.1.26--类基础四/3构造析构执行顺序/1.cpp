#include <iostream>

//类对象的生存周期
//开辟内存
//执行构造
//使用该对象
//执行析构
//释放内存

class A
{
	int a;
public:
	A(int b)
	{
		a = b;
		std::cout<<a<<"构造"<<std::endl;
	}
	~A()
	{
		std::cout<<a<<"析构"<<std::endl;
	}
};

A* a4;
void f()
{
	A a2(2);
	static A a3(3);
	a4 = new A(4);
}

void main()
{
	A a5(5);
	f();
	A* a6 = new A(6);
	f();
	delete a4;
	delete a6;
	system("pause");
}

A a1(1);

//a1构造
//
//a5构造
//a2构造
//a3构造
//a4构造
//a2析构
//a6构造
//a2构造
//a4构造
//a2析构
//a4析构
//a6析构
//
//a3析构  
//a5析构  
//a1析构