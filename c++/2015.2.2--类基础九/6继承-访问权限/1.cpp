#include <iostream>

//访问权限		public		private		protected
//本类成员函数	√			√			√
//子类成员函数	√			×			√
//外部函数		√			×			×	

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
	friend class C;
};

class B : public A
{
	void f2()
	{
		a1 = 1;
		a2 = 2;
		//a3 = 3;//子类函数无法访问私有成员
	}
};

class C
{
	void f()
	{
		A a;//友元可以访问保护，私有和公有成员
		a.a1 = 1;
		a.a2 = 2;
		a.a3 = 5;
	}
};
void f()
{
	A a;
	a.a1 = 2;
	//a.a2 = 4;//外部函数无法访问保护成员
	//a.a3 = 3;//外部函数无法访问私有成员
}

void main()
{
	
	system("pause");
}