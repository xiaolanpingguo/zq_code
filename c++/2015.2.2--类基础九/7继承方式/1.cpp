#include <iostream>

//访问权限		public		private		protected
//本类成员函数	√			√			√
//子类成员函数	√			×			√
//外部函数		√			×			×	

//
//继承方式	父类的公有成员		父类的保护成员		父类的私有成员
//公有继承	变为子类的公有成员	变为子类的保护成员	子类无法访问
//保护继承	变为子类的保护成员	变为子类的保护成员	子类无法访问
//私有继承	变为子类的私有成员	变为子类的私有成员	子类无法访问
class A
{
public: //公有
	int a1;
protected://保护
	int a2;
private://私有
	int a3;
	void f1()
	{
		a1 = 1;
		a2 = 2;
		a3 = 3;
	}
};

class B : public A //公有继承
{
	void f2()
	{
		a1 = 1;
		a2 = 2;
		//a3 = 3;//子类函数无法访问私有成员
	}
};

class C : protected A //保护继承
{
	void c()
	{
		a1 = 1;
		a2 = 2;
		//a3 = 3;
	}
};

class D : private A  //私有继续
{
	void d()
	{
		a1 = 1;
		a2 = 2;
		//a3 = 3;
	}
};


void f()
{
	A a;
	a.a1 = 2;
	//a.a2 = 4;//外部函数无法访问保护成员
	//a.a3 = 3;//外部函数无法访问私有成员
}
//一般来说，我们在使用继承时大部分时间是使用public继承
void main()
{
	B b;
	b.a1 = 1;
	//b.a2 = 2;
	//C c;
	//c.a1 = 1;
	//c.a2 = 2;
	//c.a3 = 3;
	//D d;
	//d.a1 = 1;
	//d.a2 = 2;
	//d.a3 = 3;
	system("pause");
}