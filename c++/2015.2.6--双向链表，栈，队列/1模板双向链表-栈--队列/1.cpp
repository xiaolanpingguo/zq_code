#include <iostream>
#include "SqStack.h"
//顺序表v
//链表v
//映射v
//集合v
//树v

//模板顺序表 v
//模板链表 V
//
//模板双向链表V

//模板映射 V
//模板集合 V
//模板树 V

//模板顺序栈 V
//模板顺序队列  V

//vector
//A星寻路

//顺序循环队列
//顺序优先队列

//二叉树
//完全二叉树
//满二叉树

//搜索树(查找树)
//红黑树
//哈希表

void main()
{
	CSqStack<int> ssq;
	ssq.Push(1);
	ssq.Push(2);
	ssq.Push(3);
	ssq.Push(4);
	ssq.Push(5);
	int b;
	ssq.Pop(&b);
	ssq.Pop(&b);
	ssq.Pop(&b);
	ssq.Pop(&b);
	ssq.Pop(&b);

	std::cout<<ssq.Length()<<std::endl;
	system("pause");
}

