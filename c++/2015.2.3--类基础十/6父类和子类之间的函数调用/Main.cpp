#include <iostream>

class A
{
public:
	void f()
	{
		std::cout<<"AµÄf"<<std::endl;
	}
};

class B : public A
{
public:
	void f()
	{
		std::cout<<"BµÄf"<<std::endl;
	}
};

void main()
{
	A x;//A::f
	B y;//A::f B::f
	x.f();//A::f
	y.f();//B::f
	y.A::f();//A::f
	x = y;
	x.f();//A::f
	//x.B::f();
	
	A* p = &y;
	p->f();//A::f
	//p->B::f();

	A& r = y;
	r.f();//A::f

	
	system("pause");
}