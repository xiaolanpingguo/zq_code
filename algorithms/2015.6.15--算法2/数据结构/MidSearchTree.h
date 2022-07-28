#ifndef _MID_SEARCH_TREE_H_
#define _MID_SEARCH_TREE_H_

//搜索树
//1）首先二叉树
//2）所有的节点都遵循左小右大的规则

template <typename T> //T必须支持<运算符，且数据不能有重复
class CMidSearchTree
{
	struct NODE
	{
		T data;
		NODE* left;
		NODE* right;
		NODE* parent;
		NODE* pre; //前序节点指针
		NODE* next; //后序节点指针
	};
	NODE* m_Root; //根（二叉树）
	NODE* m_Head; //头（循环双向链表）
	int m_Size;

	NODE* _Copy(NODE* p, NODE* parent);
	void _Clear(NODE* p);

public:

	CMidSearchTree();
	CMidSearchTree(const CMidSearchTree& that);
	CMidSearchTree& operator = (const CMidSearchTree& that);
	~CMidSearchTree();

	bool Insert(T data); //插入
	bool Erase(T data); //删除
	T* Find(T data); //通过数据来得到数据地址
	void Clear(); //清空
	int Size(); //长度

	void PrintLink(); //打印

	//迭代器
};

template <typename T>
void CMidSearchTree<T>::PrintLink()
{
	for (NODE* p = m_Head->next; p != m_Head; p = p->next)
		std::cout<<p->data<<" ";
	std::cout<<std::endl;
}

template <typename T>
typename CMidSearchTree<T>::NODE* CMidSearchTree<T>::_Copy(NODE* p, NODE* parent)
{
	if (p)
	{
		NODE* q = new NODE;
		q->data = p->data;
		q->left = _Copy(p->left, q);
		q->right = _Copy(p->right, q);
		q->parent = parent;
		return q;
	}
	else
		return 0;
}

template <typename T>
void CMidSearchTree<T>::_Clear(NODE* p)
{
	if (p)
	{
		_Clear(p->left);
		_Clear(p->right);
		delete p;
	}
}

template <typename T>
CMidSearchTree<T>::CMidSearchTree()
:
m_Root(0),
m_Head(new NODE),
m_Size(0)
{
	//设置链表头节点
	m_Head->pre = m_Head->next = m_Head;
}

template <typename T>
CMidSearchTree<T>::CMidSearchTree(const CMidSearchTree& that)
:
m_Root(_Copy(that.m_Root, 0)),
m_Size(that.m_Size)
{
	//m_Root = _Copy(that.m_Root, 0);

	//中序遍历设置链表指针即可
}

template <typename T>
CMidSearchTree<T>& CMidSearchTree<T>::operator = (const CMidSearchTree& that)
{
	if (this != &that)
	{
		Clear();
		m_Root = _Copy(that.m_Root, 0);
		m_Size = that.m_Size;
		
		//中序遍历设置链表指针即可
	}

	return *this;
}

template <typename T>
CMidSearchTree<T>::~CMidSearchTree()
{
	Clear();
	delete m_Head;
}

template <typename T>
bool CMidSearchTree<T>::Insert(T data)
{
	//没有根节点，就生成根节点
	if (!m_Root)
	{
		m_Root = new NODE;
		m_Root->data = data;

		//设置二叉树指针
		m_Root->left = m_Root->right = m_Root->parent = 0;

		//设置链表指针
		m_Head->pre = m_Head->next = m_Root;
		m_Root->pre = m_Root->next = m_Head;

		m_Size += 1;
		return true;
	}

	//设置指针指向根节点
	NODE* p = m_Root, * q;
	while (p)
	{
		q = p;
		if (data < p->data)
			p = p->left;
		else if (p->data < data)
			p = p->right;
		else
			//如果找到的数据和传入的数据相等则返回失败
			return false;
	}

	//跳出上面的循环的时候q就指向了要插入节点的父节点
	NODE* n = new NODE;
	n->data = data;
	n->left = n->right = 0;

	//根据左右设置指针
	if (data < q->data)
	{
		q->left = n;
		
		//设置链表指针
		n->pre = q->pre;
		n->next = q;
		q->pre->next = n;
		q->pre = n;
	}
	else
	{
		q->right = n;

		//设置链表指针
		n->pre = q;
		n->next = q->next;
		q->next->pre = n;
		q->next = n;
	}
	n->parent = q;

	//长度递增
	m_Size += 1;

	return true;
}

template <typename T>
bool CMidSearchTree<T>::Erase(T data)
{
	NODE* p = m_Root;
	while (p)
	{
		if (data < p->data)
			p = p->left;
		else if (p->data < data)
			p = p->right;
		else
			break;
	}
	//如果跳出循环p为假则意味着当前
	//搜索树中没有指定的数据
	if (!p)
		return false;

	//左右都无
	if (!p->left && !p->right)
	{
		//如果是根
		if (p == m_Root)
		{
			m_Head->pre = m_Head->next = m_Head;
			delete m_Root;
			m_Root = 0;
		}
		//不是根
		else
		{
			//是父节点左子树
			if (p->parent->left == p)
				p->parent->left = 0;
			//是父节点右子树
			else
				p->parent->right = 0;
			p->pre->next = p->next;
			p->next->pre = p->pre;
			delete p;
		}
	}
	//有左无右
	else if (p->left && !p->right)
	{
		//如果是根
		if (p == m_Root)
		{
			m_Root = p->left;
			m_Root->parent = 0;
			p->pre->next = p->next;
			p->next->pre = p->pre;
			delete p;
		}
		//不是根
		else
		{
			//是父节点左子树
			if (p->parent->left == p)
				p->parent->left = p->left;
			//是父节点右子树
			else
				p->parent->right = p->left;
			p->left->parent = p->parent;
			p->pre->next = p->next;
			p->next->pre = p->pre;
			delete p;
		}
	}
	//有右无左
	else if (!p->left && p->right)
	{
		//如果是根
		if (p == m_Root)
		{
			m_Root = p->right;
			m_Root->parent = 0;
			p->pre->next = p->next;
			p->next->pre = p->pre;
			delete p;
		}
		//不是根
		else
		{
			//是父节点左子树
			if (p->parent->left == p)
				p->parent->left = p->right;
			//是父节点右子树
			else
				p->parent->right = p->right;
			p->right->parent = p->parent;
			p->pre->next = p->next;
			p->next->pre = p->pre;
			delete p;
		}
	}
	//左右都有
	else
	{
		//找到要删除节点p的中序遍历顺序下的后序
		//节点q，然后将q的数据直接赋值p的数据，
		//然后问题就变为删除q了，那么删除q一定是
		//左右都无或有右无左的情况

		//找到中序遍历下的后序节点
		//NODE* q = p->right;
		//while (q->left)
		//	q = q->left;

		//加入了链式结构之后，上面的代码
		//可以用下面一句来替代
		NODE* q = p->next;

		//赋值数据
		p->data = q->data;

		//左右都无
		if (p == m_Root)
		{
			if (q->parent->left == q)
				q->parent->left = 0;
			else
				q->parent->right = 0;
			q->pre->next = q->next;
			q->next->pre = q->pre;
			delete q;
		}
		//有右无左
		else
		{
			if (q->parent->left == q)
				q->parent->left = q->right;
			else
				q->parent->right = q->right;
			q->right->parent = q->parent;
			q->pre->next = q->next;
			q->next->pre = q->pre;
			delete q;
		}
	}

	m_Size -= 1;

	return true;
}

template <typename T>
T* CMidSearchTree<T>::Find(T data)
{
	NODE* p = m_Root;
	while (p)
	{
		if (data < p->data)
			p = p->left;
		else if (p->data < data)
			p = p->right;
		else
			return &p->data;
	}

	//退出循环之后就意味着找不到了
	return 0;
}

template <typename T>
void CMidSearchTree<T>::Clear()
{
	_Clear(m_Root);
	m_Root = 0;
	m_Size = 0;
}

template <typename T>
int CMidSearchTree<T>::Size()
{
	return m_Size;
}



#endif