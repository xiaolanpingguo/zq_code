#include <iostream>

//被virtual关键字修饰的成员函数就是虚函数
//如果子类中也有相同的返回值，名字，形式参数
//表的函数，那么子类的这个函数也是虚函数
//其virtual关键字可以写也可以不写

class A
{
public:
	void f1()
	{
		std::cout<<"A的f1"<<std::endl;
	}
	
	virtual void f2()
	{
		std::cout<<"A的f2"<<std::endl;
	}

};

class B : public A
{
public:
	void f1()
	{
		std::cout<<"B的f1"<<std::endl;
	}
	void f2()
	{
		std::cout<<"B的f2"<<std::endl;
	}
};

//普通函数的调用
//对象调用普通函数，则对象是什么类型就调用什么
//类型的普通函数
//指针调用普通函数。则指针是什么类型的就调用什
//么类型的普通函数
//引用调用普通函数。则引用是什么类型的就调用什
//么类型的普通函数

//虚函数的调用
//对象调用虚函数，则对象是什么类型就调用什么
//类型的虚函数
//指针调用虚函数。则指针指向什么类型就调用什么
//类型的虚函数(多态)
//引用调用虚函数。则引用被什么类型初始化就调用
//什么类型的虚函数(多态)
void main()
{
	A x;
	B y;

	x = y;

	x.f1();//A::f1
	x.f2();//A::f2
	
	A* p = &y;
	p->f1();//A::f1
	p->f2();//B::f2

	A& r = y;
	r.f1();//A::f1
	r.f2();//B::f2
	
	system("pause");
}