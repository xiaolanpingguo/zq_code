#include <iostream>
#include <assert.h>

//设计模式是面向对象编程的经典使用方法，有23种，最常
//用的比如有单件、工厂、迭代器、监听

//单件：单件的目的是使得某个类的对象在程序运行过程中只有一份，因为
//很多东西在程序中只需要一份，比如引擎、管理器等等内容，其实它的本
//质就是对以前的C代码中的全局变量的一种面向对象的方式的替代
class A1
{
	static A1* pObj; //静态指针
	A1(){} //构造写为私有可以避免外部随意生成本类的对象
	//~A1(){} //可以把析构也写成是私有
	A1(const A1& that){} //可以把拷贝构造也写成是私有
public:
	static A1* getObj() //必须是静态的，如果不是静态就必须用对象来.访问，但是这个类又直接生成不了对象
	{
		if (pObj == 0)
			pObj = new A1; //getObj是A1类中静态成员函数，当然可以调用私有的构造
		return pObj;
	}
	static void releaseObj()
	{
		if (pObj)
		{
			delete pObj;
			pObj = 0;
		}
	}
};
A1* A1::pObj; //静态指针的显式定义

class A2
{
	A2(){}
	A2(const A1& that){}
public:
	static A2* getObj()
	{
		//也可以直接定义在静态中，这样的话其析构的执行也是自动的
		static A2 a2;
		return &a2;
	}
};

void main()
{
	//A1 x1, y1; //不能通过这种方式来得到A1的对象
	A1* p1 = A1::getObj(); //只能通过A1提供的getObj函数来得到A1的对象
	A1* p2 = A1::getObj();
	//A1 p3 = *p1; //调用的是编译系统给我们类中的拷贝构造函数，为了避免这种情况可以把拷贝构造或析构写成私有

	//当我们不使用了的话，就调用这个函数进行释放
	A1::releaseObj();

	A2* q1 = A2::getObj();
	A2* q2 = A2::getObj();
	
	system("pause");
}