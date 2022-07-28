#include <iostream>

class A1
{
};

class B1
{
public:
	A1 a1;
};

//class A2
//{
//public:
//	A2(int q)
//	{}
//};
//
//class B2
//{
//public :
//	A2 a2;
//};

class A3
{
	public:
	A3(int q)
	{}
};

class B3
{
public :
	A3 a3;

	//下面的语法结构称之为成员初始化列表
	//我们可以通过成员初始化列表为只有带参
	//构造的成员变量传递构造它需要的参数
	B3()
	:
	a3(1)
	{}
};


class A4
{
public:
	A4(int q)
	{}
};

class B4
{
public:
	A4 a4;
	B4(int t)
	:
	a4(t)
	{
	
	}
};

void main()
{
	B1 x1;

	//B2中的A2类型的成员变量a2必须要传参才能
	//调用其带参的构造函数，而我们这种写法无法
	//给a2传参
	//B2 x2;

	B3 x3;

	//2传递给t，之后又传递给x4中的a4进行构造
	B4 x4(2);
	system("pause");
}
