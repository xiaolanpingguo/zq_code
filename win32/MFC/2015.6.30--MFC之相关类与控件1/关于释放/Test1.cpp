// Test1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "vector"

class A
{
public:
	A(){std::cout<<"A构造"<<std::endl;}
	~A(){std::cout<<"A析构"<<std::endl;}
};
class C
{
public:
	C(){std::cout<<"C构造"<<std::endl;}
	~C(){std::cout<<"C析构"<<std::endl;}
};
class B
{
public:
	A a;
	C c;
	B(){std::cout<<"B构造"<<std::endl;}
	~B(){std::cout<<"B析构"<<std::endl;}
};

void f()
{
	B b;

	//分配sizeof(B)大小的内存
	//执行b.a、b.c、b的构造
	//使用这个类对象
	//执行b、b.c、b.a的析构
	//释放内存
}

int _tmain(int argc, _TCHAR* argv[])
{
	f();

	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	std::vector<int*> u;
	u.push_back(new int[3]);
	u.push_back(new int[2]);
	u.push_back(new int[1]);
	for (int i = 0; i < u.size(); ++i)
		delete [] u[i];

	//class CTestDlg
	//{
	//	std::vector<_TX> tx1;
	//	std::vector<_TX> tx2;
	//	std::vector<_TX> tx3;
	//};
	//在销毁上面CTestDlg的时候，会执行上面的所有
	//的tx1到tx3的析构，然后再一次性释放CTestDlg
	//所占据的内存

	return 0;
}

//假设有类B中包含了类A的对象，那么产生B对象的时候，B
//中的A对象也会被执行构造，在销毁B对象之前，A对象也会
//被析构

