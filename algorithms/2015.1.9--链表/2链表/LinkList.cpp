#include<iostream>
#include"LinkList.h"
//所有的pos值都是要找到的那个节点的前序节点
//创建Head(头)节点
LINKLIST createLINKLIST()
{
	LINKLIST p = (LINKLIST)malloc(sizeof(_LINK_LIST) + sizeof(int));
	p->next = 0;
	*((int*)(p + 1)) = 0;//记录长度,可以没有
	return p;
}
//销毁(链表)
void destroyLINKLIST(LINKLIST linklist)
{
	clearLINKLIST(linklist);
	free(linklist);
}
//插入(链表，数据，位置)
bool insertLINKLIST(LINKLIST linklist,LLDATA data,int pos)
{
	if(pos < 0 || pos > lengthLINKLIST(linklist))
		return false;
	//找到前序节点
	LINKLIST p = linklist;
	for(int i = 0; i < pos; ++i)
		p = p->next;

	//创建新节点
	LINKLIST n = (LINKLIST)malloc(sizeof(_LINK_LIST));
	//获取数据
	n->data = data;
	//设置指针指向
	n->next = p->next;
	p->next = n;
	*((int*)(linklist + 1)) += 1;
	return true;
}
//推入(链表，数据)
void pushLINKLIST(LINKLIST linklist,LLDATA data)
{
	insertLINKLIST(linklist,data,lengthLINKLIST(linklist));
}
//删除(链表，位置)
bool eraseLINKLIST(LINKLIST linklist,int pos)
{
	if(pos < 0 || pos > lengthLINKLIST(linklist) - 1)
		return false;
	//找到前序节点
	LINKLIST p = linklist;
	for(int i = 0; i < pos; ++i)
		p = p->next;
	//设置指针指向
	LINKLIST q = p->next;
	p->next = q->next;
	free(q);
	*((int*)(linklist + 1)) -= 1;
	return true;
}
//清空(链表)
void clearLINKLIST(LINKLIST linklist)
{
	//方法1
	//int length = lengthLINKLIST(linklist);
	//for(int i = 0; i < length;++i)
	//	eraseLINKLIST(linklist,0);
	//方法2
	LINKLIST p = linklist->next;
	while(p)
	{
		LINKLIST q = p->next;
		free(p);
		p = q;
	}
	linklist->next = 0;
	*((int*)(linklist + 1)) = 0;
}
//长度(链表)
int lengthLINKLIST(LINKLIST linklist)
{
	return *((int*)(linklist + 1));
}
//获取(链表，位置)
LLDATA* getLINKLIST(LINKLIST linklist,int pos)
{
	if(pos < 0 || pos > lengthLINKLIST(linklist) - 1)
		return 0;
	//找到前序节点
	LINKLIST p = linklist;
	for(int i = 0; i <= pos; ++i)
		p = p->next;
	return &p->data;
}
//查找(链表，数据，开始位置，相等函数)
int findLINKLIST(LINKLIST linklist,LLDATA data,int begin, bool (*equal)(LLDATA,LLDATA))
{
	if(begin < 0 || begin > lengthLINKLIST(linklist) - 1)
		return -2;
	//找到前序节点
	LINKLIST p = linklist;
	for(int i = 0; i <= begin; ++i)
		p = p->next;
	for(;p;p = p->next,++begin)
	{
		if((*equal)(data,p->data))
			return begin;
	}
	return -1;
}
//排序
void sortLINKLIST(LINKLIST linklist,bool increase,bool (*greater)(LLDATA,LLDATA))
{
	int length = lengthLINKLIST(linklist);
	if(increase)
	{
		LINKLIST p;
		for(int i = length - 1; i >= 0;--i)
		{
			p = linklist;
			for(int j = 0; j < i;++j)
			{
				if((*greater)(p->next->data,p->next->next->data))
				{
					LINKLIST q[] = {p,p->next,p->next->next};
					q[0]->next = q[2];
					q[1]->next = q[2]->next;
					q[2]->next = q[1];
				}
				p = p->next;
			} 
		}
	}
	else
	{
		LINKLIST p,q,r;
		for(int i = 0; i < length - 1; ++i)
		{
			p = linklist->next;
			for(int ii = 0; ii < i;++i)
			{
				p = p->next;
				int j = i;
				q = p;
				r = q->next;
				for(int k = j + 1; k < length;++k)
				{
					if((*greater)(r->data,q->data))
						q = r;
					r = r->next;
				}
				if(q != p)
				{
					LLDATA d = q->data;
					q->data = p->data;
					p->data = d;
				}
			}
		}
	}
}