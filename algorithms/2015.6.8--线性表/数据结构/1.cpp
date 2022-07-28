#include <iostream>
#include "SqList.h"
#include "LinkList.h"
#include "SqStack.h"
#include "SqQueue.h"
#include "SqSet.h"
#include "SqMap.h"

//线性
//{
	//顺序表（vector）√
	//链式表（list）√
	//顺序队列√、顺序循环队列
	//顺序栈√
	//顺序集合√
	//顺序映射√
	//顺序哈希表
//}

//树型
//{
	//顺序最大堆
	//链式树
	//链式二叉树
	//搜索树
	//AVL树
	//红黑树（set、map）
//}

//其它
//{
//	内存池
//}

//算法
//排序：冒泡√、选择√、最大堆、快速、归并
//查找：折半√、KMP
//寻路：广度、深度、A星

class ZuoBiao
{
	int x, y;
public:
	ZuoBiao& operator ++()
	{
		++x;
		++y;
		return *this;
	}
	ZuoBiao operator ++(int)
	{
		ZuoBiao zb = *this;
		++x;
		++y;
		return zb;
	}
};

#include <assert.h>

class A
{
public:
	class B
	{};
};
A::B f1()
{
	A::B b;
	return b;
}

//如果一个函数返回一个模板类中的类，那么这个返回值前面必须带上typename

template <typename T>
class C
{
public:
	class D
	{};
};
template <typename T>
typename C<T>::D f2()
{
	C::D d;
	return d;
}

#include <stack>
#include <queue>

void main()
{
	//s.

	//assert里面可以填写任何一个有结果的表达式，若
	//这个表达式的结果为真，则什么都不做，若干这个
	//表达式的结果为假，则系统直接强制使用exit退出
	//程序并给出详细的出错信息，assert称之为断言，
	//常常用在调试
	//assert(0);

	//int a = 0;
	//++a = 1; //前置自增表达式的结果可以放在=左侧，也就是说前置自增表达式的结果就是一个变量
	//a++ = 1; //后置自增表达式的结果不能放在=左侧，也就是说后置自增表达式的结果不是一个变量而是一个临时量

	CLinkList<int> sqlist1;
	sqlist1.Push_Back(1);
	sqlist1.Push_Back(2);
	sqlist1.Push_Back(3);
	sqlist1.Push_Back(4);

	//顺序表是允许用整数相当于下标进行遍历操作的
	//for (int i = 0; i < sqlist1.Size(); ++i)
	//{
	//	int* p = sqlist1.At(i);
	//	std::cout<<*p<<std::endl;
	//}

	CLinkList<int>::Iterator it;

	for (it = sqlist1.Begin(); it != sqlist1.End(); )
	{
		if (*it == 3)
			it = sqlist1.Erase(it);
		else
			++it;
	}
	
	for (it = sqlist1.Begin(); it != sqlist1.End(); ++it)
	{
		std::cout<<*it<<std::endl;
	}

	CSqQueue<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	while (!s.Empty())
	{
		int data;
		s.Front(&data);
		s.Pop();
		std::cout<<data<<std::endl;
	}

	CMap<int, char> map;
	map.Insert(0, 'A');
	map.Insert(3, 'B');
	map.Insert(2, 'D');
	map.Insert(1, 'E');
	map.Insert(-2, 'C');
	for (int i = 0; i < map.Size(); ++i)
	{
		std::cout<<map.At(i)->data<<std::endl;
	}

	system("pause");
}