#include <iostream>

class A
{
public:
	A()
	{
		std::cout<<"A父类构造"<<std::endl;
	}
	~A()
	{
		std::cout<<"A父类析构"<<std::endl;
	}
};

class B : public A
{
public:
	B()
	{
		std::cout<<"B子类构造"<<std::endl;
	}
	~B()
	{
		std::cout<<"B子类析构"<<std::endl;
	}
};

class C : public B
{
public:
	C()
	{
		std::cout<<"C子类构造"<<std::endl;
	}
	~C()
	{
		std::cout<<"C子类析构"<<std::endl;
	}
};

C c;

//继承的体系下，一个类对象的生存周期
//01)分配内存
//02)执行构造：先执行最顶层的父类的构造
//，然后再执行次一层的父类构造，.....，
//  最后再执行当前子类的构造
//03)使用类对象
//04)当前类先析构，然后再析构父类......
//最后析构最顶层的父类
//05)释放内存

//子类是依赖于父类的初始化，也就是说
//子类的构造要在父类的构造之后，因为
//可能用到父类初始化后的一些结果

void main()
{
	C* p = new C;
	delete p;
	system("pause");
}