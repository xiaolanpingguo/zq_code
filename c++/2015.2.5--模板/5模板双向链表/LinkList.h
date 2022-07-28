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
	
}

template <typename T>
void CLinkList<T>::Push(T data)
{}

template <typename T>
bool CLinkList<T>::Insert(T data,int pos)
{}

template <typename T>
bool CLinkList<T>::Erase(int pos)
{}

template <typename T>
T* CLinkList<T>::Get(int pos)
{}

#endif