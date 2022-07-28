#include <iostream>

class A
{
public:
	A()
	{
		std::cout<<"无参构造"<<std::endl;
	}
	A(int a)
	{
		std::cout<<"带参构造"<<std::endl;
	}
	~A()
	{
		std::cout<<"析构"<<std::endl;
	}
};

//在静态区中调用带参构造
A  a2(2);

void main()
{
	{
	//栈中的带参构造调用
	A a1(1);

	//在静态区中调用带参构造
	static A a3(3);
	}

	A* a4 = new A;//堆中执行无参构造

	A* a5 = new A(5);//堆中执行带参构造

	delete a4;
	delete a5;

	A* a6 = new A[5];//堆中的数组无参构造
	system("pause");
}