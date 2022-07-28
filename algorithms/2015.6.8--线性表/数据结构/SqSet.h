#ifndef _SET_H_
#define _SET_H_

//顺序集合中的所有数据都是按照一定的大小顺序排序
//的（从小到大），查找的时候进行折半查找即可

template <typename T> //T必须支持<运算符（标准库中对可以比较大小的数据都要求具有<运算符）
class CSet
{
	int m_Capacity; //容量
	int m_Size; //长度
	T* m_Data; //数据

public:
	CSet();
	CSet(const CSet& that);
	CSet& operator = (const CSet& that);
	~CSet();

	//集合中，数据是唯一的，也就是说
	//不能有相同的数据，使用顺序存储
	//实现的集合，主要用于进行查找

	bool Insert(T data); //插入
	bool Erase(T data); //删除
	T* Find(T data); //通过数据来得到数据地址
	T* At(int i); //通过下标得到数据地址
	void Clear(); //清空
	int Size(); //长度
};

template <typename T>
CSet<T>::CSet()
:
m_Capacity(8),
m_Size(0),
m_Data(new T[m_Capacity])
{}

template <typename T>
CSet<T>::CSet(const CSet& that)
:
m_Capacity(that.m_Capacity),
m_Size(that.m_Size),
m_Data(new T[m_Capacity])
{
	for (int i = 0; i < m_Size; ++i)
		m_Data[i] = that.m_Data[i];
}
template <typename T>
CSet<T>& CSet<T>::operator = (const CSet& that)
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
CSet<T>::~CSet()
{
	delete [] m_Data;
}

template <typename T>
bool CSet<T>::Insert(T data)
{
	//折半插入法即通过折半查找得到应该插入的位置p，在
	//这个p上面插入数据，可以保证这个顺序存储的数组还
	//是排列好的
	int begin = 0, end = m_Size - 1;
	while (begin <= end)
	{
		int half = (begin + end) / 2;
		if (data < m_Data[half])
			end = half - 1;
		else if (m_Data[half] < data)
			begin = half + 1;
		else
			//不能有相同的数据
			return false;
	}

	//begin就是应该放入新数据的位置

	if (m_Size == m_Capacity)
	{
		T* p = new T[m_Capacity *= 2];
		for (int i = 0; i < m_Size; ++i)
			p[i] = m_Data[i];
		delete [] m_Data;
		m_Data = p;
	}

	int m = m_Size - begin;

	//顺序实现的集合的瓶颈就是下面的代码
	for (int i = 0; i < m; ++i)
		m_Data[m_Size - i] = m_Data[m_Size - 1 - i];

	m_Data[begin] = data;
	m_Size += 1;

	return true;
}

template <typename T>
bool CSet<T>::Erase(T data)
{
	int begin = 0, end = m_Size - 1;
	while (begin <= end)
	{
		int half = (begin + end) / 2;
		if (data < m_Data[half])
			end = half - 1;
		else if (m_Data[half] < data)
			begin = half + 1;
		else
		{
			int m = m_Size - half - 1;

			//顺序实现的集合的瓶颈就是下面的代码
			for (int i = 0; i < m; ++i)
				m_Data[half + i] = m_Data[half + 1 + i];

			m_Size -= 1;
			return false;
		}
	}

	return false;
}

template <typename T>
T* CSet<T>::Find(T data)
{
	int begin = 0, end = m_Size - 1;
	while (begin <= end)
	{
		int half = (begin + end) / 2;
		if (data < m_Data[half])
			end = half - 1;
		else if (m_Data[half] < data)
			begin = half + 1;
		else
			return m_Data + half;
	}

	return 0;
}

template <typename T>
T* CSet<T>::At(int i)
{
	return pos >= 0 && pos < m_Size ? m_Data + pos : 0;
}

template <typename T>
void CSet<T>::Clear()
{
	m_Size = 0;
}

template <typename T>
int CSet<T>::Size()
{
	return m_Size;
}

#endif