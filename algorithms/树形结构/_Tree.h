#ifndef _TREE_H_
#define _TREE_H_

#include <list>
#include <iostream>

//template<typename T>
//struct _TREE_NODE
//{
//	T data; //数据
//	_TREE_NODE* left_child; //左孩子
//	_TREE_NODE* right_brother; //右兄弟
//	_TREE_NODE* parent; //父节点
//};
//把下面的所有函数重新按照上面的树节点重新完成

template<typename T>
struct _TREE_NODE
{
	T data; //数据
	std::list<_TREE_NODE<T>*> child; //子节点
	_TREE_NODE<T>* parent; //父节点
};

template<typename T> //创建
_TREE_NODE<T>* createTN()
{
	_TREE_NODE<T>* t = new _TREE_NODE<T>;
	t->parent = 0;
	return t;
}

template<typename T> //断开
_TREE_NODE<T>* cutTN(_TREE_NODE<T>* t)
{
	if (t && t->parent)
	{
		std::list<_TREE_NODE<T>*>::iterator it;
		for (it = t->parent->child.begin(); it != t->parent->child.end(); ++it)
		{
			if (*it == t)
				break;
		}
		t->parent->child.erase(it);
		t->parent = 0;
	}
	return t;
}

template<typename T> //插入
_TREE_NODE<T>* insertTN(_TREE_NODE<T>* p, _TREE_NODE<T>* c, bool back = true)
{
	cutTN(c);
	if (back)
		p->child.push_back(c);
	else
		p->child.push_front(c);
	c->parent = p;

	return c;
}

template<typename T> //删除
void _eraseTN(_TREE_NODE<T>* t)
{
	if (t)
	{
		std::list<_TREE_NODE<T>*>::iterator it;
		for (it = t->child.begin(); it != t->child.end(); )
		{
			_eraseTN(*it);
			it = t->child.erase(it);
		}
		delete t;
	}
}

template<typename T> //删除
void eraseTN(_TREE_NODE<T>* t)
{
	_eraseTN<T>(cutTN<T>(t));
}

template<typename T> //大小
int sizeTN(_TREE_NODE<T>* t)
{
	if (t)
	{
		int child_num = 0;
		std::list<_TREE_NODE<T>*>::iterator it;
		for (it = t->child.begin(); it != t->child.end(); ++it)
			child_num += sizeTN(*it);
		return child_num + 1;
	}
	else
		return 0;
}

template<typename T> //高度
int heightTN(_TREE_NODE<T>* t)
{
	if (t)
	{
		int child_max_height = 0;
		std::list<_TREE_NODE<T>*>::iterator it;
		for (it = t->child.begin(); it != t->child.end(); ++it)
		{
			int child_height = heightTN(*it);
			if (child_max_height < child_height)
				child_max_height = child_height;
		}
		return child_max_height + 1;
	}
	else
		return 0;
}

template<typename T> //打印
void _printTN(_TREE_NODE<T>* t, int level)
{
	if (t)
	{
		if (level > 0)
		{
			if (level > 1)
			{
				std::cout<<"┃";
				for (int i = 0; i < level - 2; ++i)
					std::cout<<"  ";

				//如果当前节点就是父节点的最后一个孩子
				if (t == t->parent->child.back())
					std::cout<<"┗";
				else
					std::cout<<"┣";
			}
			else
			{
				if (t == t->parent->child.back())
					std::cout<<"┗";
				else
					std::cout<<"┣";
			}
		}
		
		std::cout<<t->data<<std::endl;
		std::list<_TREE_NODE<T>*>::iterator it;
		for (it = t->child.begin(); it != t->child.end(); ++it)
			_printTN(*it, level + 1);
	}
}

template<typename T> //打印
void printTN(_TREE_NODE<T>* t)
{
	//	  1
	//	/ | \
	//	4 2 3
	//	  |
	//	  5
	//   / \
	//	6   7
	//上面的树打印为
	//1
	//┣4
	//┣2
	//┃┗5
	//┃  ┣6
	//┃  ┗7
	//┗3

	//树的遍历
	//先根遍历：首先访问根节点，再先根遍历每个子树
	//后根遍历：首先后根遍历每个子树，再访问根节点

	_printTN(t, 0);
}

#endif