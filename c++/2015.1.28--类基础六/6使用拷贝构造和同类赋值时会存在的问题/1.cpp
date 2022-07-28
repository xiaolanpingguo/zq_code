#include<iostream>

class A
{
	char* p;
public:
	A()
	{
		p = new char;
	}
	~A()
	{
		delete p;
	}
};
void main()
{
	
	A a1;
	{
	A a2 = a1;//调用默认的编译器提供的拷贝构造
	}

	//A a1;
	//A a2;
	//a1 = a2;//调用默认的编译器提供的同类赋值


	system("pause");
}