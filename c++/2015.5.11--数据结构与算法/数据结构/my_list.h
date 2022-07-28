#ifndef _MY_LIST_H_
#define _MY_LIST_H_

#include <assert.h>

template <typename T>
class my_list
{
	struct _node
	{
		_node* pre;
		_node* next;
		T data;
	};
	_node* m_head; //头结点
	int m_size; //表长

	void _copy(const my_list& that);

public:

	my_list();
	my_list(const my_list& that);
	my_list& operator = (const my_list& that);
	~my_list();

	void push_back(T data);
	void push_front(T data);
	void clear();
	int size();
	
	class iterator
	{
		template <typename T>
		friend class my_list;

		my_list* p; //指向的my_list
		_node* cur; //当前表示的my_vector中的节点

	public:
		iterator();
		bool operator != (const iterator& that);
		iterator& operator ++ ();
		iterator operator ++ (int);
		iterator& operator -- ();
		iterator operator -- (int);
		T& operator * ();
		T* operator -> ();
	};

	iterator begin();
	iterator end();
	iterator insert(iterator& it, T data);
	iterator erase(iterator& it);
};

template <typename T>
void my_list<T>::_copy(const my_list& that)
{
	_node* p = that.m_head->next;
	_node* q = m_head;
	for (; p != that.m_head; p = p->next)
	{
		//生成新节点
		_node* r = new _node;

		//得到数据
		r->data = p->data;

		//设置指针
		q->next = r;
		r->pre = q;

		//更新当前指针
		q = r;
	}
	q->next = m_head;
	m_head->pre = q;
	m_size = that.m_size;
}

template <typename T>
my_list<T>::my_list()
:
m_head(new _node),
m_size(0)
{
	m_head->pre = m_head->next = m_head;
}

template <typename T>
my_list<T>::my_list(const my_list& that)
:
m_head(new _node),
m_size(0)
{
	m_head->pre = m_head->next = m_head;
	_copy(that);
}

template <typename T>
my_list<T>& my_list<T>::operator = (const my_list& that)
{
	if (this != &that)
	{
		clear();
		_copy(that);
	}
	return *this;
}

template <typename T>
my_list<T>::~my_list()
{
	clear();
	delete m_head;
}

template <typename T>
void my_list<T>::push_back(T data)
{
	_node* p = new _node;

	//设置数据
	p->data = data;
	
	//设置指针
	p->pre = m_head->pre;
	p->next = m_head;
	m_head->pre->next = p;
	m_head->pre = p;

	//长度递增
	m_size += 1;
}

template <typename T>
void my_list<T>::push_front(T data)
{
	_node* p = new _node;

	//设置数据
	p->data = data;
	
	//设置指针
	p->pre = m_head;
	p->next = m_head->next;
	m_head->next->pre = p;
	m_head->next = p;

	//长度递增
	m_size += 1;
}

template <typename T>
void my_list<T>::clear()
{
	_node* p = m_head->next;
	while (p != m_head)
	{
		_node* q = p->next;
		delete p;
		p = q;
	}
	m_head->pre = m_head->next = m_head;
	m_size = 0;
}

template <typename T>
int my_list<T>::size()
{
	return m_size;
}

template <typename T>
my_list<T>::iterator::iterator()
:
p(0),
cur(0)
{}

template <typename T>
bool my_list<T>::iterator::operator != (const iterator& that)
{
	return p != that.p || cur != that.cur;
}

template <typename T>
typename my_list<T>::iterator& my_list<T>::iterator::operator ++ ()
{
	assert(p && cur != p->m_head);
	cur = cur->next;
	return *this;
}

template <typename T>
typename my_list<T>::iterator my_list<T>::iterator::operator ++ (int)
{
	assert(p && cur != p->m_head);
	iterator it = *this;
	cur = cur->next;
	return it;
}

template <typename T>
typename my_list<T>::iterator& my_list<T>::iterator::operator -- ()
{
	assert(p && cur != p->m_head->next);
	cur = cur->pre;
	return *this;
}

template <typename T>
typename my_list<T>::iterator my_list<T>::iterator::operator -- (int)
{
	assert(p && cur != p->m_head->next);
	iterator it = *this;
	cur = cur->pre;
	return it;
}

template <typename T>
T& my_list<T>::iterator::operator * ()
{
	assert(p && cur != p->m_head);
	return cur->data;
}

template <typename T>
T* my_list<T>::iterator::operator -> ()
{
	assert(p && cur != p->m_head);
	return &cur->data;
}

template <typename T>
typename my_list<T>::iterator my_list<T>::begin()
{
	iterator it;
	it.p = this;
	it.cur = m_head->next;
	return it;
}

template <typename T>
typename my_list<T>::iterator my_list<T>::end()
{
	iterator it;
	it.p = this;
	it.cur = m_head;
	return it;
}

template <typename T>
typename my_list<T>::iterator my_list<T>::insert(iterator& it, T data)
{
	iterator r = end();

	if (it.p != this)
		return r;

	_node* p = new _node;
	p->data = data;
	p->next = it.cur;
	p->pre = it.cur->pre;
	it.cur->pre->next = p;
	it.cur->pre = p;

	r.cur = p;

	m_size += 1;

	return r;
}

template <typename T>
typename my_list<T>::iterator my_list<T>::erase(iterator& it)
{
	assert(it.p == this);

	iterator r;
	r.p = this;
	r.cur = it.cur->next;

	it.cur->pre->next = it.cur->next;
	it.cur->next->pre = it.cur->pre;
	delete it.cur;
	m_size -= 1;

	return r;
}

#endif