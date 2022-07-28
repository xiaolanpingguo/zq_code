#include <iostream>

class A
{
public:
	//此处的f1,f2函数是纯虚函数，拥有一个或者
	//多个纯虚函数的类称为抽象类，抽象类是不能
	//定义对象，只能定义指针或者引用
	virtual void f1() = 0;//
	virtual void f2() = 0;
	//[0][0]
};

class B : public A
{
public://[&B::f1][0]
	//B中实现类继承自A的纯虚函数f1,但没有实现f2
	//所以B仍然是一个抽象类
	void f1()
	{
		std::cout<<"B::f1"<<std::endl;
	}
};

class C : public B
{
public://[&B::f1][&C::f2]
	//C继承自B，B中实现A的纯虚函数f1.
	//C本身实现了B的纯虚函数f2
	//所以C不是抽象类
	void f2()
	{
		std::cout<<"C::f2"<<std::endl;
	}
};


void main()
{
	//A a;//不能实例化抽象类
	A* pA;
	B* pB;
	C c;

	pB = &c;
	pB->f1();
	pB->f2();

	pA = &c;
	pA->f1();
	pA->f2();

	//B b;
	//pA = &b;
	//pA->f1();
	//pA->f2();
	system("pause");
}

//抽象类其实就是虚函数表中有没有被赋值
//的函数指针的类，这种类是不能定义对象
//的，但可以作为父类指针去指向实现了所有
//纯虚函数的子类对象的，所以纯虚函数是种
//强制继承和多态的手段
