#include<iostream>

//class A
//{
//	
//};

//编译器会为一个空类自动提供4个函数
//(严格上说是3个函数，1个运算符)
//01)公有的，无参的，什么都不做的构造函数
//02)公有的，什么都不做的析构函数
//03)公有的，按字节拷贝的拷贝构造函数
//04)公有的，按字节拷贝的同类赋值运算符

//上面的空类A会被编译成
class A
{
public:
	A()
	{}
	~A()
	{}

	A(const A& that)//拷贝构造函数
	{
		memcpy(this,&that,sizeof(A));
	}

	A& operator = (const A& that)//同类赋值
	{
		memcpy(this,&that,sizeof(A));
		return *this;
	}
};

//只要我们写了拷贝构造，则编译器将不再
//提供那个公有的，按字节拷贝的拷贝构造函数
//只要我们写了同类赋值，则编译器将不再
//提供那个公有的，按字节拷贝的同类赋值运算符
//

class A1
{
public:

	A1()
	{
		std::cout<<"无参"<<std::endl;
	}
	~A1()
	{
		std::cout<<"析构"<<std::endl;
	}

	A1(const A1& that)//拷贝构造函数
	{
		std::cout<<"拷贝构造"<<std::endl;
	}

	A1& operator = (const A1& that)//同类赋值
	{
		std::cout<<"同类赋值"<<std::endl;
		return *this;
	}
};

void f(A1 x)
{

}

A1 f1()
{
	A1 a4;//无参构造
	return a4;//拷贝构造,a4作为一个表达式来初始化返回值的
}//退出f1的时候a4会被析构掉,返回值被析构掉

void main()
{
	A1 a1;
	A1 a2 = a1;//拷贝构造
	A1 a3(a1);//拷贝构造跟上面是一样的
	a2 = a1;//同类赋值
	a1 = a2;//同类赋值
	f(a1);//拷贝构造(实参初始化形参)

	f1();
	system("pause");
}
//从上面可以看出：
//拷贝构造是否调用是看是否有初始化的过程,
//必须是同一个类的对象来初始化同一个类的对象
//对象已经构造好后，进行赋值的时候 = 左右
//两边的类型必须是同一个类的对象