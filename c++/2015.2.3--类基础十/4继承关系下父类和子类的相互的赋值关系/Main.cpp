#include <iostream>

class A
{
public:
	int a;
};

class B : public A
{
public:
	int b;
};

void main()
{
	A x;
	x.a = 1;
	B y;
	y.a = 2;
	y.b = 3;

	x = y;//父类对象 = 子类对象
	//y = x;

	A* p1 = &y;//父类指针 = 子类对象的地址
	//B* p2 = &x;

	A& r1 = y;//父类引用 = 子类的对象
	//B& r2 = x;

	//写在 = 左边的只能是父类，写在
	//= 右边的只能是子类
	system("pause");
}