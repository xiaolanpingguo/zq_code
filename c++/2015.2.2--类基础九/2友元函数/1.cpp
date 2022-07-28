#include <iostream>

//友元
//友元是一种打破封装性的做法，即破坏原有
//的私有访问权限，
//当我们的类中的成员希望对部分函数是公有
//对另外部分函数是私有的话，那么我们就可以使用
//友元。
//友元函数可以设置多个
class A
{
	int a;

	friend void f();
	friend void f1();
	friend void f2();
	friend void f3();

};

void f()
{
	A x;
	x.a = 1;
}


void main()
{
	A x;
	//x.a= 1;
	f();
	system("pause");
}