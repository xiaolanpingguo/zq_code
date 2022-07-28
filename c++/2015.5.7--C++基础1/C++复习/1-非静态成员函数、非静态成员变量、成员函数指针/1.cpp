#include <iostream>

//非静态成员变量、非静态成员函数
//访问权限、非静态成员函数指针
//构造、析构
//拷贝构造、同类赋值

//运算符重载、隐式转换
//静态成员、常量成员
//成员初始化列表
//继承
//多态
//模板

class A
{
public:
	int a; //非静态成员变量
	void set(int x) //非静态成员函数，有隐藏形参this指针
	{
		a = x;
	}
	int get() //非静态成员函数，有隐藏形参this指针
	{
		return a;
	}
	void set2(int x)
	{
		a = x;
	}
};
//void set(A* this, int x)
//{
//	a = x;
//}
//int get(A* this)
//{
//	return a;
//}

void set1(int x)
{}

void main()
{
	//非静态成员变量的调用，必须有类对象或者类地址通过.或->来调用

	A t1, t2;
	t1.set(1); //set(&t1, 1);
	t1.get(); //get(&t1);
	t2.set(1); //set(&t2, 1);
	t2.get(); //get(&t2);

	//定义一个函数指针指向类的非静态成员函数
	//void (* p)(int) = &A::set; //不行，p是一个指向全局函数的函数指针

	void (* p)(int) = set1; //p指向set1是可以的

	//q是一个指向A类中的返回值为void，形参表为(int)的成员函数的指针
	void (A::* q)(int) = &A::set;

	//(*q)(1); //不能平白无故地直接用这种成员函数指针来调用指向的函数

	(&t1->* q)(1); //完全等同于t1.set(1);
	(t2.* q)(1); //完全等同于t2.set(1);

	//让q指向A类中的成员函数set2
	q = &A::set2;
	(&t1->*q)(1); //完全等同于t1.set2(1);
	(t2.*q)(1); //完全等同于t2.set2(1);
	
	system("pause");
}