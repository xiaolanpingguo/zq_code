#include <iostream>

//拷贝构造和同类赋值的作用
//一般来说是让一个对象的内容
//等于另外一个对象的内容
//比如说我们考试中的那个链表的
//克隆函数,就可以封装为拷贝构造和
//同类赋值。

//不需要重载拷贝构造和同类赋值，因为A1类
//中没有指针指向同一片堆内存的问题.
class A1
{
public:
	int a1;
};

class A2 
{
	int* a2;
public:
	A2(int b)
	{
		a2 = new int;
		*a2 = b;
	}

	A2(const A2& that)
	{
		a2 = new int;
		*a2 = *(that.a2);
	}

	A2& operator = (const A2& that)
	{
		if(this != &that)
		{
			*a2 = *(that.a2);
		}
		return *this;
	}
	void Set()
	{
		*a2 = 1;
	}

	~A2()
	{
		delete a2;
	}
};

void main()
{
	//A1 x1;
	//x1.a1 = 1;
	//A1 x2 = x1;//默认拷贝构造
	//x1 = x2 ;//默认同类赋值
	
	A2 x1(4);
	{
	A2 x2 = x1;
	}
	x1.Set();
	system("pause");
}
