#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

//二叉树：binary tree

template <typename T>
struct _BTN
{
	T data;
	_BTN* left; //左子树
	_BTN* right; //右子树
	_BTN* parent; //父节点
};

template <typename T>
_BTN<T>* createBTN()
{
	_BTN<T>* p = new _BTN<T>;
	p->left = p->right = p->parent = 0;
	return p;
}

//断开p和其父节点的联系
template <typename T>
_BTN<T>* cutBTN(_BTN<T>* p)
{
	//p必须为真且p必须有父节点
	if (p && p->parent) //不能写成if (p->parent && p)
	{
		//p是它的父节点的左子树
		if (p == p->parent->left)
			p->parent->left = 0;
		else
			p->parent->right = 0;
		p->parent = 0;
	}
	return p;
}

//下面的函数是将s插入到p的左边或右边作为左子树或右子树
//注意：
//1）p的左右原来就有节点，函数应该将s拿去替换原来的节点，并返回
//   原来的节点
//2）p本身可能不是一个根节点，那么必须先断开s和它的原父节点之间
//   的联系
template <typename T>
_BTN<T>* insertBTN(_BTN<T>* p, _BTN<T>* s, bool left = true)
{
	cutBTN(s);
	if (left)
	{
		//得到p原来的左子树（有可能是0）
		_BTN<T>* q = p->left;
		cutBTN(q);
		p->left = s;
		s->parent = p;
		return q;
	}
	else
	{
		//得到p原来的右子树（有可能是0）
		_BTN<T>* q = p->right;
		cutBTN(q);
		p->right = s;
		s->parent = p;
		return q;
	}
}

//template <typename T>
//void pre_printBTN(_BTN<T>* p)
//{
//	//先序遍历打印
//	if (p)
//	{
//		std::cout<<p->data<<' ';
//		pre_printBTN(p->left);
//		pre_printBTN(p->right);
//	}
//}
//
//template <typename T>
//void mid_printBTN(_BTN<T>* p)
//{
//	//中序遍历打印
//	if (p)
//	{
//		mid_printBTN(p->left);
//		std::cout<<p->data<<' ';
//		mid_printBTN(p->right);
//	}
//}
//
//template <typename T>
//void post_printBTN(_BTN<T>* p)
//{
//	//后序遍历打印
//	if (p)
//	{
//		post_printBTN(p->left);
//		post_printBTN(p->right);
//		std::cout<<p->data<<' ';
//	}
//}

template <typename T>
int sizeBTN(_BTN<T>* p)
{
	if (p)
		return 1 + sizeBTN(p->left) + sizeBTN(p->right);
	else
		return 0;
}

template <typename T>
int heightBTN(_BTN<T>* p)
{
	if (p)
	{
		//先得到左右两边子树的高度
		int left_h = heightBTN(p->left);
		int right_h = heightBTN(p->right);

		//返回左右两边子树较高的那
		//一边子树的高度加一
		return (left_h > right_h ? left_h : right_h) + 1;
	}
	else
		return 0;
}

template <typename T>
void _eraseBTN(_BTN<T>* p)
{
	if (p)
	{
		_eraseBTN(p->left);
		_eraseBTN(p->right);
		delete p;
	}
}

template <typename T>
void eraseBTN(_BTN<T>* p)
{
	//先断开p和父节点的联系
	cutBTN(p);

	//递归删除p的所有节点
	_eraseBTN(p);
}

template <typename T>
_BTN<T>* _copyBTN(_BTN<T>* p, _BTN<T>* parent)
{
	if (p)
	{
		//生成新节点
		_BTN<T>* n = new _BTN<T>;

		//得到数据
		n->data = p->data;

		//递归左、右子树进行拷贝，并
		//设置新节点的父节点
		n->left = _copyBTN(p->left, n);
		n->right = _copyBTN(p->right, n);
		n->parent = parent;

		return n;
	}
	else
		return 0;
}

template <typename T>
_BTN<T>* copyBTN(_BTN<T>* p)
{
	return _copyBTN(p, 0);
}

//如果两棵二叉树p和q完全一
//样（结构一样还有数据也一
//样），那么返回真
template <typename T>
bool equalBTN(_BTN<T>* p, _BTN<T>* q)
{
	
}

//层序遍历打印
template <typename T>
void level_printBTN(_BTN<T>* p)
{
	
}

#endif