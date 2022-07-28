#ifndef _STACK_H_
#define _STACK_H_

template <typename T>
class CStack
{
	int m_Capacity; //容量
	int m_Size; //长度
	T* m_Data; //数据
	
public:

	CStack(int Capacity = 8);
	CStack(const CStack& that);
	CStack& operator = (const CStack& that);
	~CStack();

	void Push(T data);
	bool Pop(T* pdata);

	bool GetTop(T* pdata);
	void Clear();
	int Size();
};

template <typename T>
CStack<T>::CStack(int Capacity)
:
m_Capacity(Capacity),
m_Size(0),
m_Data(new T[m_Capacity])
{}

template <typename T>
CStack<T>::CStack(const CStack& that)
:
m_Capacity(that.m_Capacity),
m_Size(that.m_Size),
m_Data(new T[m_Capacity])
{
	for (int i = 0; i < m_Size; ++i)
		m_Data[i] = that.m_Data[i];
}

template <typename T>
CStack<T>& CStack<T>::operator = (const CStack& that)
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
CStack<T>::~CStack()
{
	delete [] m_Data;
}

template <typename T>
void CStack<T>::Push(T data)
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
bool CStack<T>::Pop(T* pdata)
{
	if (0 == m_Size)
		return false;
	else
	{
		*pdata = m_Data[--m_Size];
		return true;
	}
}

template <typename T>
bool CStack<T>::GetTop(T* pdata)
{
	if (0 == m_Size)
		return false;
	else
	{
		*pdata = m_Data[m_Size - 1];
		return true;
	}
}

template <typename T>
void CStack<T>::Clear()
{
	m_Size = 0;
}

template <typename T>
int CStack<T>::Size()
{
	return m_Size;
}

#endif