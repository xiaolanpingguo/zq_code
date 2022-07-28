#include<iostream>

//类中成员都访问权限，访问权限决定了这个成员可以
//被访问的地方.
//访问权限有3个，目前掌握2个

//访问权限   外部函数    内部函数
//public:    可以访问	 可以访问
//private:   无法访问	 可以访问  

//类的默认访问权限是私有的访问权限
//一般来说，我们将成员变量设置为私有，将成员函数设为公有
class ABC
{
private://私有的访问权限
	int a;
public://公有的访问权限
	int b;
	void f()
	{
		a = 1;
		b = 2;
	}
};

void main()
{
	ABC x;
	//x.a = 1;
	x.b = 2;
	system("pause");
}
