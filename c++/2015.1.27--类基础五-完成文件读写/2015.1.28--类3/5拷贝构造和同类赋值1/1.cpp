#include<iostream>

class A
{
public:
	A& operator = (const A& that)
	{
		std::cout<<"同类赋值"<<std::endl;
		return *this;
	}
};

class B
{
	int x;
public:
	B(int X)
	:
	x(X)
	{}

	B operator = (const B& that)
	{
		x = that.x;
		return *this;
	}
};

class C
{
	int x;
public:
	C(int X)
	:
	x(X)
	{}

	C& operator = (const C& that)
	{
		std::cout<<"C同类赋值"<<std::endl;
		x = that.x;
		return *this;
	}
};

void main()
{
	//同类赋值本质上还是一个函数
	A a1;
	A a2;
	a1 = a2;//完全等同于a1.operator = (a2);

	int x = 1,y = 2,z = 3;
	(x = y) = z;
	//赋值运算符表达式的结果是赋值完毕之后左边的变量
	
	//同类赋值运算符的返回值类型设置为引用的原因
	//就在于可以让赋值运算符表达式的结果继续放在
	// = 的左边
	//B 类的同类赋值的运算符的结果不是一个变量
	//而是一个临时量，就达不到和C++的习惯用法
	//一致
	B b1(1),b2(2),b3(3);
	(b1 = b2) = b3;

	C c1(1),c2(2),c3(3);
	(c1 = c2) = c3;
	system("pause");
}