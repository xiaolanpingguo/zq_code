#ifndef _LINKLIST_H_
#define _LINKLIST_H_

template <typename T>
class CLinkList
{
	struct _NODE//节点结构体
	{
		T data;
		_NODE* pre;
		_NODE* next;
	};

	_NODE* m_Head;//头节点-指向头节点的指针
	int m_Length;//长度
	_NODE* _Get(int pos);//获取
	void _Copy(const CLinkList& that);
public:	
	CLinkList();
	CLinkList(const CLinkList& that);
	CLinkList& operator = (const CLinkList& that);
	~CLinkList();
	
	void Clear();
	void Push(T data);
	bool Insert(T data,int pos);
	bool Erase(int pos);
	T* Get(int pos);
};
//CLinkList<T>::
template <typename T>
typename CLinkList<T>::_NODE* CLinkList<T>::_Get(int pos)
{
	_NODE* p = m_Head;
	if(pos < m_Length / 2)
	{
		for(int i = -1; i < pos; ++i)
			p = p->next;
	}
	else
	{
		for(int i = m_Length - pos; i > 0; --i)
			p = p->pre;
	}
	return p;
}

template <typename T>
void CLinkList<T>::_Copy(const CLinkList& that)
{
	_NODE* p = that.m_Head->next;
	_NODE* q = m_Head;
	for(;p != that.m_Head; p = p->next)
	{
		_NODE* r = new _NODE;
		r->data = p->data;
		r->pre = q;
		q->next = r;
		q = r;
	}

	q->next = m_Head;
	m_Head->pre = q;
	m_Length = that.m_Length;
}

template <typename T>
CLinkList<T>::CLinkList()
:
m_Head(new _NODE),
m_Length(0)
{
	m_Head->pre = m_Head->next = m_Head;
}

template <typename T>
CLinkList<T>::CLinkList(const CLinkList& that)
:
m_Head(new _NODE),
m_Length(0)
{
	m_Head->pre = m_Head->next = m_Head;
	_Copy(that);
}

template <typename T>
CLinkList<T>& CLinkList<T>::operator = (const CLinkList& that)
{
	if(this != &that)
	{
		Clear();
		_Copy(that);
	}
	return *this;
}

template <typename T>
CLinkList<T>::~CLinkList()
{
	Clear();
	if(m_Head)
		delete m_Head;
}

template <typename T>
void CLinkList<T>::Clear()
{
	_NODE* p = m_Head->next;
	while(p != m_Head)
	{
		_NODE* q = p->next;
		delete p;
		p = q;
	}
	m_Head->pre = m_Head->next = m_Head;
	m_Length = 0;
}

template <typename T>
bool CLinkList<T>::Insert(T data,int pos)
{
	if(pos < 0 || pos > m_Length)	
		return false;
	_NODE* p = _Get(pos);
	_NODE* q = new _NODE;
	//不管返回的节点是前还是后，都强制的将
	//新节点插入到该节点前面
	q->data = data;
	q->pre = p->pre;
	q->next = p;
	p->pre->next = q;
	p->pre = q;
	m_Lenght += 1;
	return true;
}

template <typename T>
void CLinkList<T>::Push(T data)
{
	_NODE* q = new _NODE;
	//由于push操作都是插入表的尾上
	//但由于是双向链表，其头节点很明确
	//而且头节点的前序节点就是尾节点
	q->data = data;
	q->pre = m_Head->pre;
	q->next = m_Head;
	m_Head->pre->next = q;
	m_Head->pre = q;
	m_Lenght += 1;
}

template <typename T>
bool CLinkList<T>::Erase(int pos)
{
	if(pos < 0 || pos >= m_Length)	
		return false;
	_NODE* p = _Get(pos);
	p->pre->next = p->next;
	p->next->pre = p->pre;
	delete p;
	m_Length -= 1;
	return  true;
}

template <typename T>
T* CLinkList<T>::Get(int pos)
{
	if(pos < 0 || pos >= m_Length)	
		return 0;
	return &(_Get(pos)->data);
}

#endif