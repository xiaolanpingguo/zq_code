#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <vector>
#include <string>

struct TN
{
	std::string data; //数据
	std::vector<TN*> child; //子节点
	TN* parent; //父节点
};
//struct TN
//{
//	std::string data; //数据
//	TN* child; //左孩子
//	TN* brother; //右兄弟
//	TN* parent; //父节点
//};

inline TN* createTN()
{
	TN* tn = new TN;
	tn->parent = 0;
	return tn;
}

inline TN* cutTN(TN* p)
{
	if (p && p->parent)
	{
		//从其父节点表中删除
		for (std::vector<TN*>::iterator it = p->parent->child.begin(); it != p->parent->child.end(); ++it)
		{
			if (*it == p)
			{
				p->parent->child.erase(it);
				break;
			}
		}
		p->parent = 0;
	}
	return p;
}

inline TN* insertTN(TN* f, TN* c)
{
	cutTN(c);
	f->child.push_back(c);
	c->parent = f;
	return c;
}

//树的先根遍历
//首先访问根节点，再依次先根遍历其所有子节点
//树的后根遍历
//首先依次后根遍历其所有子节点，再访问根节点

inline void preTN(TN* p)
{
	if (p)
	{
		//首先访问根节点
		std::cout<<p->data.c_str()<<' ';

		//再依次先根遍历其所有子节点
		for (std::vector<TN*>::iterator it = p->child.begin(); it != p->child.end(); ++it)
			preTN(*it);
	}
}

inline void postTN(TN* p)
{
	if (p)
	{
		//首先依次后根遍历其所有子节点
		for (std::vector<TN*>::iterator it = p->child.begin(); it != p->child.end(); ++it)
			postTN(*it);

		//再访问根节点
		std::cout<<p->data.c_str()<<' ';
	}
}

#endif