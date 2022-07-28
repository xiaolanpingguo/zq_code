#include <iostream>
#include <assert.h>

//成员初始化列表
//1）只有构造函数可以使用成员初始化列表
//2）成员初始化列表的执行顺序是按照类中成员变量的定义顺序来的
class A
{
	char* p;
	int len;
	
public:
	A()
		: //下面的初始化列表中，先执行p(new char[len])，再执行len(10)
	len(10),
	p(new char[len])
	{}

	~A(){delete [] p;}
};

//3）形如下面的C中的B的构造需要参数的话，就必须通过成员初始化列表提供
class B
{
public:
	B(int x){}
};
class C //C中包含B
{
	B b1;
	B b2;
public:
	C():b1(1),b2(2) //写对象名，后面加上()进行初始化
	{}
};

//4）形如下面的D继承自B而B的构造需要参数，也必须通过成员初始
//   化列表为父类B提供构造需要的参数
class D : public B //D继承自B
{
	int x;
	int y;
public:
	D():y(2),x(1),B(1) //写父类名，后面加上()填入构造所需的参数
	{} //首先执行父类构造、再执行x的初始化、最后执行y的初始化
};

void main()
{
	//A x;
	C c;
	D d;
	
	system("pause");
}