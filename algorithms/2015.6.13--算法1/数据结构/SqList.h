#ifndef _SQ_LIST_H_
#define _SQ_LIST_H_

//C++把几乎所有的C语言头文件都做了一次再包装，去掉了.h，然后
//再前面加上c以表示这个文件是标准C语言的文件
//#include <assert.h>
#include <cassert>

template <typename T>
class CSqList
{
	int m_Capacity; //容量
	int m_Size; //长度
	T* m_Data; //数据

public:
	
	CSqList();
	CSqList(const CSqList& that);
	CSqList& operator = (const CSqList& that);
	~CSqList();

	//顺序表可以进行后推入
	void Push_Back(T data);

	//顺序表可以进行后弹出
	bool Pop_Back();

	//大小
	int Size();

	//链表是没有下面的操作的
	T* At(int pos);

	void Clear();

	//迭代器作为一个类中的类要设置为公有，才能
	//在外部用本类::引出
	class Iterator
	{
		template <typename T>
		friend class CSqList;

		//迭代器要知道自己和哪个顺序表建立了
		//联系，所以要存储一个指向顺序表的指针
		CSqList* p;

		//作为顺序存储的顺序表迭代器，内部要
		//包含一个下标
		int i;

	public:

		//构造
		Iterator();

		//不等判断
		bool operator != (const Iterator& that);

		//前置自增
		Iterator& operator ++ ();

		//解引用
		T& operator * ();

		//地址引出
		T* operator -> ();
	};

	//迭代器相关
	Iterator Insert(T data, Iterator it);
	Iterator Erase(Iterator it);
	Iterator Begin();
	Iterator End();
};

template <typename T>
CSqList<T>::CSqList()
:
m_Capacity(8),
m_Size(0),
m_Data(new T[m_Capacity])
{}

template <typename T>
CSqList<T>::CSqList(const CSqList& that)
:
m_Capacity(that.m_Capacity),
m_Size(that.m_Size),
m_Data(new T[m_Capacity])
{
	for (int i = 0; i < m_Size; ++i)
		m_Data[i] = that.m_Data[i];
}

template <typename T>
CSqList<T>& CSqList<T>::operator = (const CSqList& that)
{
	if (this != &that)
	{
		delete [] m_Data;

		m_Capacity = that.m_Capacity;
		m_Size = that.m_Size;
		m_Data = new T[m_Capacity];

		for (int i = 0; i < m_Size; ++i)
			m_Data[i] = that.m_Data[i];
	}
	return *this;
}

template <typename T>
CSqList<T>::~CSqList()
{
	//delete运算符如果发现后面的地址是0则什么都不做
	delete [] m_Data;
}

template <typename T>
void CSqList<T>::Push_Back(T data)
{
	if (m_Size == m_Capacity)
	{
		T* p = new T[m_Capacity *= 2];
		for (int i = 0; i < m_Size; ++i)
			p[i] = m_Data[i];
		delete [] m_Data;
		m_Data = p;
	}
	m_Data[m_Size++] = data;
}

template <typename T>
bool CSqList<T>::Pop_Back()
{
	if (m_Size > 0)
	{
		m_Size -= 1;
		return true;
	}
	else
		return false;
}

template <typename T>
int CSqList<T>::Size()
{
	return m_Size;
}

template <typename T>
void CSqList<T>::Clear()
{
	m_Size = 0;
}

template <typename T>
T* CSqList<T>::At(int pos)
{
	return pos >= 0 && pos < m_Size ? m_Data + pos : 0;
}

template <typename T>
CSqList<T>::Iterator::Iterator()
:
p(0),
i(-1)
{}

template <typename T>
bool CSqList<T>::Iterator::operator != (const Iterator& that)
{
	return p != that.p || i != that.i;
}

template <typename T>
typename CSqList<T>::Iterator& CSqList<T>::Iterator::operator ++ ()
{
	//断言（必须有指向，下标必须大于等于0小于长度）
	assert(p && i >= 0 && i < p->m_Size);
	i += 1;
	return *this;
}

template <typename T>
T& CSqList<T>::Iterator::operator * ()
{
	assert(p && i >= 0 && i < p->m_Size);
	return p->m_Data[i];
}

template <typename T>
T* CSqList<T>::Iterator::operator -> ()
{
	assert(p && i >= 0 && i < p->m_Size);
	return &p->m_Data[i];
}

//[begin,end]
//
//push_back(1);
//
//[begin,1][end]
//
//push_back(2);
//
//[begin,1][2][end]
//
//push_back(3);
//
//[begin,1][2][3][end]

template <typename T>
typename CSqList<T>::Iterator CSqList<T>::Insert(T data, Iterator it)
{
	//插入之后应该返回代表插入位置的迭代器

	assert(it.p == this && it.i >= 0 && it.i <= m_Size);

	if (m_Size == m_Capacity)
	{
		T* p = new T[m_Capacity *= 2];
		for (int i = 0; i < m_Size; ++i)
			p[i] = m_Data[i];
		delete [] m_Data;
		m_Data = p;
	}

	int m = m_Size - it.i;
	for (int i = 0; i < m; ++i)
		m_Data[m_Size - i] = m_Data[m_Size - 1 - i];
	m_Data[it.i] = data;
	m_Size += 1;

	return it;
}

template <typename T>
typename CSqList<T>::Iterator CSqList<T>::Erase(Iterator it)
{
	assert(it.p == this && it.i >= 0 && it.i < m_Size);

	int m = m_Size - it.i - 1;
	for (int i = 0; i < m; ++i)
		m_Data[it.i + i] = m_Data[it.i + 1 + i];
	m_Size -= 1;

	return it;
}

template <typename T>
typename CSqList<T>::Iterator CSqList<T>::Begin()
{
	Iterator it;
	it.p = this;
	it.i = 0;
	return it;
}

template <typename T>
typename CSqList<T>::Iterator CSqList<T>::End()
{
	Iterator it;
	it.p = this;
	it.i = m_Size;
	return it;
}

#endif