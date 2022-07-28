#include <iostream>

class A
{
	const int x;
	//类的常量成员必须被初始化，
	//只能用成员初始化列表进行初始化
public:
	A()
		:
	x(0)
	{}

	int y;
	//常量成员函数
	void f2() const
	{
		//常量成员函数对于成员变量只能进行
		//读操作
		//y = 1;
		int z = y;
	}

	void f3() const;

	void f()
	{}
};

void A::f3() const
{

}

class B
{
public:
	//a是A的常量引用
	//所以潜在的意思就是a不能被修改,
	//那么下面a.f()调用a的成员函数可能
	//会改掉a中的数据,所以很常量引用会产生
	//矛盾。所以报错
	void f(const A& a)
	{
		//a.f();

		//f2是a的常量成员函数，不可能修改到a中
		//的数据的，所以这里可以用
		a.f2();
	}

	void f1(A& a)
	{
		a.f();
	}
};

void main()
{
	A a;
	system("pause");
}