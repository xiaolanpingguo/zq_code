#ifndef _TREE_H_
#define _TREE_H_

#include <list>
#include <iostream>

template<typename T>
struct _TREE_NODE
{
	T data; //数据
	_TREE_NODE* left_child; //左孩子
	_TREE_NODE* right_brother; //右兄弟
	_TREE_NODE* parent; //父节点
};


template<typename T>
_TREE_NODE<T>* CreateTree()
{
	_TREE_NODE<T>* t = new _TREE_NODE<T>;
	t->parent = t->left_child = t->right_brother = NULL;
	return t;
}

template<typename T>
_TREE_NODE<T>* CutTree(_TREE_NODE<T>* t)
{
	if (t && t->parent)
	{
		if (t->parent->left_child == t)
		{
			t->parent->left_child = t->right_brother;
		}
		else
		{
			_TREE_NODE<T>* p = t->parent->left_child;
			while (p->right_brother != t)
			{	
				p = p->right_brother;
			}
			p->right_brother = t->right_brother;
		}
		t->right_brother = t->parent = NULL;
	}
	return t;
}

template<typename T>
_TREE_NODE<T>* InsertTree(_TREE_NODE<T>* p, _TREE_NODE<T>* c)
{
	CutTree(c);
	c->parent = p;
	c->right_brother = p->left_child;
	p->left_child = c;
	return c;
}

template<typename T>
void _EraseTree(_TREE_NODE<T>* t)
{
	if (t)
	{
		_EraseTree(t->left_child);
		_EraseTree(t->right_brother);
		delete t;
	}
}

template<typename T>
void EraseTree(_TREE_NODE<T>* t)
{
	_EraseTree<T>(CutTree<T>(t));
}

template<typename T>
int SizeTree(_TREE_NODE<T>* t)
{
	if (t)
	{
		int n = 1;
		for (_TREE_NODE<T>* p = t->left_child; p; p = p->right_brother)
			n += SizeTree(p);
		return n;
	}
	return  0;
}

template<typename T>
int HeightTree(_TREE_NODE<T>* t)
{
	if (t)
	{
		int h = 0;
		for (_TREE_NODE<T>* p = t->left_child; p; p = p->right_brother)
		{
			int child_h = HeightTree(p);
			if (h < child_h)
				h = child_h;
		}
		return h + 1;
	}
	return 0;
}

#endif