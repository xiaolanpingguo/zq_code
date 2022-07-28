#ifndef _QUEUE_H_
#define _QUEUE_H_

template <typename T>
class CQueue
{
	int m_Size;//容量
	int m_Length;
	int m_Head;//头下标
	int m_Tail;//尾下标
	T* m_Data;//数组
public:
	CQueue(int size = 4);
	CQueue(const CQueue& that);
	CQueue& operator = (const CQueue& that);
	~CQueue();

	//入队列
	void Enter(T data);
	//出队列
	bool Quit(T* pdata);
	
	//获取头
	bool GetHead(T* pdata);
	void Clear();
	int Length();
};
template <typename T>
CQueue<T>::CQueue(int size)
:
m_Size(size),
m_Length(0),
m_Head(0),
m_Tail(0),
m_Data(new T[m_Size])
{
	
}

template <typename T>
CQueue<T>::CQueue(const CQueue& that)
:
m_Size(that.m_Size),
m_Length(that.m_Length),
m_Head(that.m_Head),
m_Tail(that.m_Tail),
m_Data(new T[m_Size])
{
	for(int i = 0; i < that.m_Length; ++i)
	{
		m_Data[i] = that.m_Data[i];
	}
}

template <typename T>
CQueue<T>& CQueue<T>::operator = (const CQueue& that)
{
	if(this != &that)
	{
		delete []m_Data;
		m_Size = that.m_Size;
		m_Length = that.m_Length;
		m_Head = that.m_Head;
		m_Tail = that.m_Tail;
		m_Data = new T[m_Size];
		for(int i = 0; i < that.m_Length; ++i)
		{
			m_Data[i] = that.m_Data[i];
		}
	}	
	return *this;
}

template <typename T>
CQueue<T>::~CQueue()
{
	if(m_Data)
		delete []m_Data;
}

//入队列
template <typename T>
void CQueue<T>::CQueue<T>::Enter(T data)
{
	if(m_Length == m_Size)
	{
		T* p = new T[m_Size *= 2];
		for(int i = 0; i < m_Length;++i)
		{
			p[i] = m_Data[i];
		}
		delete []m_Data;
		m_Data = p;
		m_Head = 0;
		m_Tail = m_Length;
	}
	m_Data[m_Tail] = data;
	m_Tail += 1;
	m_Length += 1;
}


//出队列
template <typename T>
bool CQueue<T>::Quit(T* pdata)
{
	if(m_Length == 0)
		return false;
	*pdata = m_Data[m_Head];
	int move=m_Length-1;
	for(int i=0;i<move;++i)
		m_Data[i]=m_Data[i+1];
	m_Tail-=1;
	m_Length-=1;
	return true;
}

//获取头
template <typename T>
bool CQueue<T>::GetHead(T* pdata)
{
	if(m_Length == 0)
		return false;
	*pdata = m_Data[m_Head];
	return true;
}

template <typename T>
void CQueue<T>::Clear()
{
	m_Head = m_Tail = m_Length = 0;
}

template <typename T>
int CQueue<T>::Length()
{
	return m_Length;
}
#endif