#include <iostream>

//继承
//就是子类自动拥有父类的成员变量和成员函数

class A
{
public:
	int a1;
	void a2()
	{
		std::cout<<"A的a2函数"<<std::endl;
	}
};

//设置类B为类A的子类，A为B的父类(基类，超类。。。)

class B : public A
{

};

//B会被编译器处理为
//class B
//{
//public:
//	int a1;
//	void a2()
//	{
//		std::cout<<"A的a2函数"<<std::endl;
//	}
//};
class C
{
public:
	int c1;
	void c2()
	{
		std::cout<<"C的c2函数"<<std::endl;
	}
};

class D : public C
{
public:
	int d1;
	void d2()
	{
		std::cout<<"D的d2函数"<<std::endl;
	}
};

//编译器处理为
//class D 
//{
//public:
//	int c1;
//	void c2()
//	{
//		std::cout<<"C的c2函数"<<std::endl;
//	}
//	int d1;
//	void d2()
//	{
//		std::cout<<"D的d2函数"<<std::endl;
//	}
//};
void main()
{
	B a;
	a.a2();
	D d;
	d.c1 = 1;
	d.c2();
	d.d1 = 1;
	d.d2();
	system("pause");
}