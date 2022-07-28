#ifndef _MAX_HEAP_H_
#define _MAX_HEAP_H_

template <typename T>
class CMaxHeap
{
	int m_Capacity;
	int m_Size;
	T* m_Data;

public:

	CMaxHeap(int Capacity = 8);
	CMaxHeap(const CMaxHeap& that);
	CMaxHeap& operator = (const CMaxHeap& that);
	~CMaxHeap();

	void Push(T data); //入最大堆
	bool Pop(); //出最大堆
	bool Front(T* data); //得到根节点数据
	void Clear(); //清空
	int Size(); //大小
};

template <typename T>
CMaxHeap<T>::CMaxHeap(int Capacity)
:
m_Capacity(Capacity),
m_Size(0),
m_Data(new T[m_Capacity])
{}

template <typename T>
CMaxHeap<T>::CMaxHeap(const CMaxHeap& that)
:
m_Capacity(that.m_Capacity),
m_Size(that.m_Size),
m_Data(new T[m_Capacity])
{
	for (int i = 1; i < m_Size; ++i)
		m_Data[i] = that.m_Data[i];
}

template <typename T>
CMaxHeap<T>& CMaxHeap<T>::operator = (const CMaxHeap& that)
{
	if (this !=  &that)
	{
		delete [] m_Data;

		m_Capacity = that.m_Capacity;
		m_Size = that.m_Size;
		m_Data = new T[m_Capacity];
		for (int i = 1; i < m_Size; ++i)
			m_Data[i] = that.m_Data[i];
	}

	return *this;
}

template <typename T>
CMaxHeap<T>::~CMaxHeap()
{
	delete [] m_Data;
}

template <typename T>
void CMaxHeap<T>::Push(T data)
{
	if (m_Size + 1 == m_Capacity)
	{
		T* p = new T[m_Capacity *= 2];
		for (int i = 1; i <= m_Size; ++i)
			p[i] = m_Data[i];
		delete [] m_Data;
		m_Data = p;
	}

	//按照完全二叉树进行放入，即放到最后
	m_Data[++m_Size] = data;

	//按照父节点优先级大于子节点优先级进行调整
	int index0 = m_Size; //当前放入的节点下标
	int index1 = index0 / 2; //当前放入的节点的父节点下标

	//循环调整
	while (index0 > 1 && m_Data[index1] < m_Data[index0])
	{
		T t = m_Data[index1];
		m_Data[index1] = m_Data[index0];
		m_Data[index0] = t;

		//更新当前节点下标和其父节点下标
		index0 = index1;
		index1 = index0 / 2;
	}
}

template <typename T>
bool CMaxHeap<T>::Pop()
{
	
}

template <typename T>
bool CMaxHeap<T>::Front(T* data)
{
	if (m_Size > 0)
	{
		*data = m_Data[1];
		return true;
	}
	else
		return false;
}

template <typename T>
void CMaxHeap<T>::Clear()
{
	m_Size = 0;
}

template <typename T>
int CMaxHeap<T>::Size()
{
	return m_Size;
}

#endif