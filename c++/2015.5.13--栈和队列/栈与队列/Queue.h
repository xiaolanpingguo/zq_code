#ifndef _QUEUE_H_
#define _QUEUE_H_

template <typename T>
class CQueue
{
	int m_Capacity; //容量
	int m_Size; //长度
	T* m_Data; //数据
	
public:

	CQueue(int Capacity = 8);
	CQueue(const CQueue& that);
	CQueue& operator = (const CQueue& that);
	~CQueue();

	void Enter(T data);
	bool Quit(T* pdata);

	bool GetHead(T* pdata);
	void Clear();
	int Size();
};

template <typename T>
CQueue<T>::CQueue(int Capacity)
:
m_Capacity(Capacity),
m_Size(0),
m_Data(new T[m_Capacity])
{}

template <typename T>
CQueue<T>::CQueue(const CQueue& that)
:
m_Capacity(that.m_Capacity),
m_Size(that.m_Size),
m_Data(new T[m_Capacity])
{
	for (int i = 0; i < m_Size; ++i)
		m_Data[i] = that.m_Data[i];
}

template <typename T>
CQueue<T>& CQueue<T>::operator = (const CQueue& that)
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
CQueue<T>::~CQueue()
{
	delete [] m_Data;
}

template <typename T>
void CQueue<T>::Enter(T data)
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
bool CQueue<T>::Quit(T* pdata)
{
	if (0 == m_Size)
		return false;
	else
	{
		*pdata = m_Data[0];
		m_Size -= 1;
		for (int i = 0; i < m_Size; ++i)
			m_Data[i] = m_Data[i + 1];
		return true;
	}
}

template <typename T>
bool CQueue<T>::GetHead(T* pdata)
{
	if (0 == m_Size)
		return false;
	else
	{
		*pdata = m_Data[0];
		return true;
	}
}

template <typename T>
void CQueue<T>::Clear()
{
	m_Size = 0;
}

template <typename T>
int CQueue<T>::Size()
{
	return m_Size;
}

#endif