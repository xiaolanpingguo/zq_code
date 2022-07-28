#include <iostream>
#include <windows.h>

//类和结构体一样，都直接支持初始化和赋值两种运算

//除了构造和析构，其实每个类都有拷贝构造和同类赋值两个成员函数，这两个
//成员函数都会被隐藏调用，用同类型对象初始化同类型对象那么会调用拷贝构
//造，用同类型对象赋值同类型对象那么调用同类赋值

class A
{
public:
	A()
	{
		std::cout<<"无参构造"<<std::endl;
	}
	A(const A& that)
	{
		std::cout<<"拷贝构造"<<std::endl;
	}
	A& operator = (const A& that)
	{
		std::cout<<"同类赋值"<<std::endl;
		return *this;
	}
};

void f1(A x)
{}

A f2()
{
	A x;
	return x;
}

void f();
void f6();

void main()
{
	f6();

	//如果构造函数只有一个参数，那么可以使用下面两种调用方法
	//A x(y);
	//A x = y; //完全等同于上面的代码

	A a1; //无参构造
	A a2(a1); //拷贝构造
	A a3 = a1; //拷贝构造
	a1 = a2; //同类赋值
	f1(a1); //拷贝构造（实参初始化形参，而不是实参赋值给形参）
	f2(); //拷贝构造（表达式x初始化临时的返回值）

	f();

	//[][][][]:这4个字节的名字叫b，也叫c
	int b;
	int& c = b; //引用就是一个变量的别名
	
	system("pause");
}

//1）编译器对拷贝构造、同类赋值的处理？

//如果一个类没有写拷贝构造，那么编译器会自动为这个类添加一个
//公有的、按字节拷贝的拷贝构造，同理如果一个类没有写同类赋值
//，那么编译器会自动为这个类添加一个公有的、按字节拷贝的同类
//赋值，比如下面的B类
//class B
//{};
//上面的B类型会被编译器处理成下面的样子
//class B
//{
//public:
//	B(){}
//	~B(){}
//	B(const B& that)
//	{
//		memcpy(this, &that, sizeof(B));
//	}
//	B& operator = (const B& that)
//	{
//		memcpy(this, &that, sizeof(B));
//		return *this;
//	}
//}

//2）什么时候应该重写拷贝构造、同类赋值？
//如果类对象中有指向堆内存的指针，且要在析构中进行释放，那么
//这种类（顺序表、链表、二叉树...）一般都要重写拷贝构造和同类
//赋值，以免在同类初始化或同类赋值之后产生释放同一片堆内存的情况
class C
{
	int* p;
public:
	C()
	{
		p = new int;
	}
	~C()
	{
		delete p;
	}
	//	C(const C& that)
	//	{
	//		memcpy(this, &that, sizeof(C));
	//	}
	//	C& operator = (const C& that)
	//	{
	//		memcpy(this, &that, sizeof(C));
	//		return *this;
	//	}
};
void f()
{
	C c0; //无参构造
	C c1; //无参构造
	C c2 = c1; //拷贝构造（系统给的）
	C c3; //无参构造
	c3 = c1; //同类赋值（系统给的）
}

//3）同类赋值的返回值为什么是引用？
//凡是一个函数希望放在=左侧的话，这个函数应该返回一个引用
int t;
int f3(int T)
{
	t = T;
	return t; //返回的是被变量t初始化的一个临时量
}
int& f4(int T)
{
	t = T;
	return t; //返回的是t
}
void f5()
{
	//f3(2) = 1;
	f4(3) = 1; //完全等同于t = 1;
}
//赋值运算表达式的结果是一个变量不是一个临时量，比如
//(a = b) = c的的代码，a = b的结果是a变量本身，而我们
//在写赋值运算符重载的时候，还是需要使得我们的运算符的
//使用方式尽量和C++原有的使用方式一样，所以我们的同类赋
//值运算符的结果应该是一个变量，一般就是=左侧的变量，就
//是*this

//4）为什么同类赋值中一般要加上if(this != &that)这句判断
//主要是为了避免自己给自己赋值的情况，比如下面的代码
class X
{
public:
	X& operator = (const X& that)
	{
		//如果下面的表达式为假就什么都不做
		if (this != &that)
		{
			//真正的处理
			Beep(500, 200);
		}
		return *this;
	}
};
void f6()
{
	X x1, x2;
	
	//this是x1的地址
	//&that是x2的地址
	x1 = x2;

	//this是x1的地址
	//&that是x1的地址
	x1 = x1; //自己跟自己赋值没有任何意义，最好就什么都不做，如果
	         //同类赋值中的this和&that是同一个地址，那么可以判断
	         //出来当前是自己赋值自己
}

//WZQ1应该重写拷贝构造和同类赋值
class WZQ1
{
	char* qp;
public:
	WZQ1()
	{
		qp = new char[19 * 19];
	}
	~WZQ1()
	{
		delete [] qp;
	}
};
//WZQ2不用写拷贝构造和同类赋值
class WZQ2
{
	char qp[19 * 19];
};