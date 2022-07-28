// TestAuto.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//单件是设计模式之一，其作用就是为了把一个类规定为
//在内存中只有一个类对象，无法生成多个类对象
class A
{
	//1）构造、拷贝构造设置为私有
private:
	A(){}
	A(const A& that){}

	//2）有静态成员变量指针，类型为指向本类型的指针
	static A* m_Instance;

public:
	//3）有公有的、静态的得到本类对象地址的函数
	static A* getInstance();
};

A* A::m_Instance;
A* A::getInstance()
{
	if (!m_Instance)
		m_Instance = new A;
	return m_Instance;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//A a; //调用构造
	A* p1 = A::getInstance();
	A* p2 = A::getInstance();
	A* p3 = A::getInstance();
	//A b = *p1; //调用拷贝构造

	return 0;
}

