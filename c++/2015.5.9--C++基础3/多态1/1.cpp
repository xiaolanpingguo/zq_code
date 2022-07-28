#include <iostream>

//一般类似下面这种比较简单的处理是不用多态的
//struct ITEM
//{
//	int hp_add;
//	int mp_add;
//	int att_add;
//	int def_add;
//};
//const ITEM 低级体力剂 = {10, 0, 0, 0};
//const ITEM 中级体力剂 = {30, 0, 0, 0};
//const ITEM 高级体力剂 = {60, 0, 0, 0};
//const ITEM 低级魔力剂 = {0, 10, 0, 0};
//const ITEM 中级魔力剂 = {0, 30, 0, 0};
//const ITEM 高级魔力剂 = {0, 60, 0, 0};

class A
{
public:
	void f1(){std::cout<<"A::f1"<<std::endl;}
	virtual void f2(){std::cout<<"A::f2"<<std::endl;}
};
class B : public A
{
public:
	void f1(){std::cout<<"B::f1"<<std::endl;}
	/*virtual */void f2(){std::cout<<"B::f2"<<std::endl;}
};

//普通成员函数
//对象调用：对象是什么类型就调用什么类型的普通成员函数
//地址调用：地址是什么类型就调用什么类型的普通成员函数
//引用调用：引用是什么类型就调用什么类型的普通成员函数

//虚成员函数
//对象调用：对象是什么类型就调用什么类型的虚成员函数
//地址调用：地址指向什么类型就调用什么类型的虚成员函数（多态！）
//引用调用：引用被什么类型对象初始化就调用什么类型的虚成员函数（多态！）

void main()
{
	A a;
	B b;

	a = b;
	a.f1(); //调用A::f1，相当于a.f1();
	a.f2(); //调用A::f2，相当于a.f2();

	A* p = &b;
	p->f1(); //调用A::f1，相当于a.f1();
	p->f2(); //调用B::f2，相当于b.f2();多态！

	A& r = b;
	r.f1(); //调用A::f1，相当于a.f1();
	r.f2(); //调用B::f2，相当于b.f2();多态！

	b.f1(); //B::f1
	b.f2(); //B::f2
	b.A::f1(); //A::f1
	b.A::f2(); //A::f2

	system("pause");
}