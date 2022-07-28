#include<iostream>
#include"SXLinkList.h"
//所有的pos值都是要找到的那个节点的前序节点
//创建Head(头)节点
SXLINKLIST createSXLINKLIST()
{
	SXLINKLIST p = (SXLINKLIST)malloc(sizeof(_SXLINK_LIST) + sizeof(int));
	p->next = p->pre = 0;
	*((int*)(p + 1)) = 0;//记录长度,可以没有
	return p;
}
//销毁(链表)
void destroySXLINKLIST(SXLINKLIST sxlinklist)
{
	clearSXLINKLIST(sxlinklist);
	free(sxlinklist);
}
//插入(链表，数据，位置)
bool insertSXLINKLIST(SXLINKLIST sxlinklist,LLDATA data,int pos)
{
	if(pos < 0 || pos > lengthSXLINKLIST(sxlinklist))
		return false;
	//找到前序节点
	SXLINKLIST p = sxlinklist;
	for(int i = 0; i < pos; ++i)
		p = p->next;

	//创建新节点
	SXLINKLIST n = (SXLINKLIST)malloc(sizeof(_SXLINK_LIST));
	//获取数据
	n->data = data;
	//设置指针指向
	n->next = p->next;

	if(pos == lengthSXLINKLIST(sxlinklist))
		n->pre = p;
	else
		n->pre = n->next->pre;
	p->next = n;
	if(pos != lengthSXLINKLIST(sxlinklist))
		n->next->pre = n;

	*((int*)(sxlinklist + 1)) += 1;
	return true;
}
//推入(链表，数据)
void pushSXLINKLIST(SXLINKLIST sxlinklist,LLDATA data)
{
	insertSXLINKLIST(sxlinklist,data,lengthSXLINKLIST(sxlinklist));
}
//删除(链表，位置)
bool eraseSXLINKLIST(SXLINKLIST sxlinklist,int pos)
{
	if(pos < 0 || pos > lengthSXLINKLIST(sxlinklist) - 1)
		return false;
	//找到前序节点
	SXLINKLIST p = sxlinklist;
	for(int i = 0; i < pos; ++i)
		p = p->next;
	//设置指针指向
	SXLINKLIST q = p->next;

	p->next = q->next;
	q->next->pre = q->pre;

	free(q);
	*((int*)(sxlinklist + 1)) -= 1;
	return true;
}
//清空(链表)
void clearSXLINKLIST(SXLINKLIST sxlinklist)
{
	//方法1
	//int length = lengthSXLINKLIST(sxlinklist);
	//for(int i = 0; i < length;++i)
	//	eraseSXLINKLIST(sxlinklist,0);
	//方法2
	SXLINKLIST p = sxlinklist->next;
	while(p)
	{
		SXLINKLIST q = p->next;
		free(p);
		p = q;
	}
	sxlinklist->next = 0;
	*((int*)(sxlinklist + 1)) = 0;
}
//长度(链表)
int lengthSXLINKLIST(SXLINKLIST sxlinklist)
{
	return *((int*)(sxlinklist + 1));
}
//获取(链表，位置)
LLDATA* getSXLINKLIST(SXLINKLIST sxlinklist,int pos)
{
	if(pos < 0 || pos > lengthSXLINKLIST(sxlinklist) - 1)
		return 0;
	//找到前序节点
	SXLINKLIST p = sxlinklist;
	for(int i = 0; i <= pos; ++i)
		p = p->next;
	return &p->data;
}
//查找(链表，数据，开始位置，相等函数)
int findSXLINKLIST(SXLINKLIST sxlinklist,LLDATA data,int begin, bool (*equal)(LLDATA,LLDATA))
{
	if(begin < 0 || begin > lengthSXLINKLIST(sxlinklist) - 1)
		return -2;
	//找到前序节点
	SXLINKLIST p = sxlinklist;
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
void sortSXLINKLIST(SXLINKLIST sxlinklist,bool increase,bool (*greater)(LLDATA,LLDATA))
{
	int length = lengthSXLINKLIST(sxlinklist);
	if(increase)
	{
		SXLINKLIST p;
		for(int i = length - 1; i >= 0;--i)
		{
			p = sxlinklist;
			for(int j = 0; j < i;++j)
			{
				if((*greater)(p->next->data,p->next->next->data))
				{
					SXLINKLIST q[] = {p,p->next,p->next->next};

					q[0]->next = q[2];
					q[1]->next = q[2]->next;
					q[2]->next = q[1];

					q[2]->pre = q[0];
					q[1]->next->pre = q[1];
					q[1]->pre = q[2];
					
				}
				p = p->next;
			} 
		}
	}
	else
	{
		SXLINKLIST p,q,r;
		for(int i = 0; i < length - 1; ++i)
		{
			p = sxlinklist->next;
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