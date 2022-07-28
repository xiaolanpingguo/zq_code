#ifndef _MAX_HEAP_H_
#define _MAX_HEAP_H_

template <typename T>
class CMaxHeap //也叫优先队列
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
	for (int i = 1; i <= m_Size; ++i)
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
		for (int i = 1; i <= m_Size; ++i)
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
	//当前没有数据或只
	//有一个数据的情况
	if (m_Size == 0)
		return false;
	else if (m_Size == 1)
	{
		m_Size -= 1;
		return true;
	}

	//至少2个数据

	//得到当前被拿走的数据位置
	int index0 = 1;

	//循环调整
	while (1)
	{
		int left_index = index0 * 2;
		int right_index = left_index + 1;

		//左右子节点都有
		if (right_index <= m_Size)
		{
			//如果右边子节点的数据优先级大于左边子节点
			//的数据优先级的话，那么把右侧的子节点数据
			//赋值给父节点数据
			if (m_Data[left_index] < m_Data[right_index])
			{
				m_Data[index0] = m_Data[right_index];
				index0 = right_index;
			}
			else
			{
				m_Data[index0] = m_Data[left_index];
				index0 = left_index;
			}
		}
		//有左子节点无右子节点
		else if (left_index <= m_Size)
		{
			//这种情况下它的左子节点一定是当前的最大堆
			//的最后一个节点，此时只需要把左子节点补上
			//即可
			m_Data[index0] = m_Data[left_index];
			m_Size -= 1;
			return true;
		}
		//左右都无，跳出本循环
		else
			break;
	}

	//Ctrl + ]命令可以在匹配的大括号之间跳转
	//Ctrl + K + F（一般需要先选中要处理的文
	//本）可以自动帮助我们对其文本

	//拿最后位置的数据放入到index0位置

	//当index0就是最后位置的时候
	if (index0 == m_Size)
	{
		m_Size -= 1;
		return true;
	}

	//当index0不是最后位置的时候，将
	//最后位置的数据补充道index0上面
	//并得到index0的父节点下标
	m_Data[index0] = m_Data[m_Size];
	int index1 = index0 / 2;

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

	m_Size -= 1;

	return true;
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