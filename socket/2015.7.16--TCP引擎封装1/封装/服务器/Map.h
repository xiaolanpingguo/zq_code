#ifndef _MAP_H_
#define _MAP_H_

template <typename KEY, typename DATA>
class CMap
{
public:
	struct PAIR //键值对
	{
		KEY key; //key值必须是唯一的
		DATA data;
	};

private:
	int m_Capacity; //容量
	int m_Size; //长度
	PAIR* m_Data; //数据

public:
	CMap();
	CMap(const CMap& that);
	CMap& operator = (const CMap& that);
	~CMap();

	bool Insert(KEY key, DATA data); //插入
	bool Erase(KEY key); //删除
	PAIR* Find(KEY key); //键值查找
	PAIR* At(int i); //下标查找
	void Clear(); //清空
	int Size(); //长度
};

template <typename KEY, typename DATA>
CMap<KEY, DATA>::CMap()
:
m_Capacity(8),
m_Size(0),
m_Data(new PAIR[m_Capacity])
{}

template <typename KEY, typename DATA>
CMap<KEY, DATA>::CMap(const CMap& that)
:
m_Capacity(that.m_Capacity),
m_Size(that.m_Size),
m_Data(new PAIR[m_Capacity])
{
	for (int i = 0; i < m_Size; ++i)
		m_Data[i] = that.m_Data[i];
}

template <typename KEY, typename DATA>
CMap<KEY, DATA>& CMap<KEY, DATA>::operator = (const CMap& that)
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

template <typename KEY, typename DATA>
CMap<KEY, DATA>::~CMap()
{
	delete [] m_Data;
}

template <typename KEY, typename DATA>
bool CMap<KEY, DATA>::Insert(KEY key, DATA data)
{
	int begin = 0, end = m_Size - 1;
	while (begin <= end)
	{
		int half = (begin + end) / 2;
		if (key < m_Data[half].key)
			end = half - 1;
		else if (m_Data[half].key < key)
			begin = half + 1;
		else
			//不能有相同的数据
			return false;
	}

	if (m_Size == m_Capacity)
	{
		PAIR* p = new PAIR[m_Capacity *= 2];
		for (int i = 0; i < m_Size; ++i)
			p[i] = m_Data[i];
		delete [] m_Data;
		m_Data = p;
	}

	int m = m_Size - begin;

	//顺序实现的集合的瓶颈就是下面的代码
	for (int i = 0; i < m; ++i)
		m_Data[m_Size - i] = m_Data[m_Size - 1 - i];

	m_Data[begin].key = key;
	m_Data[begin].data = data;

	m_Size += 1;

	return true;
}

template <typename KEY, typename DATA>
bool CMap<KEY, DATA>::Erase(KEY key)
{
	int begin = 0, end = m_Size - 1;
	while (begin <= end)
	{
		int half = (begin + end) / 2;
		if (key < m_Data[half].key)
			end = half - 1;
		else if (m_Data[half].key < key)
			begin = half + 1;
		else
		{
			int m = m_Size - half - 1;
			for (int i = 0; i < m; ++i)
				m_Data[half + i] = m_Data[half + 1 + i];
			m_Size -= 1;
			return false;
		}
	}

	return false;
}

template <typename KEY, typename DATA>
typename CMap<KEY, DATA>::PAIR* CMap<KEY, DATA>::Find(KEY key)
{
	int begin = 0, end = m_Size - 1;
	while (begin <= end)
	{
		int half = (begin + end) / 2;
		if (key < m_Data[half].key)
			end = half - 1;
		else if (m_Data[half].key < key)
			begin = half + 1;
		else
			return m_Data + half;
	}

	return 0;
}

template <typename KEY, typename DATA>
typename CMap<KEY, DATA>::PAIR* CMap<KEY, DATA>::At(int i)
{
	return i >= 0 && i < m_Size ? m_Data + i : 0;
}

template <typename KEY, typename DATA>
void CMap<KEY, DATA>::Clear()
{
	m_Size = 0;
}

template <typename KEY, typename DATA>
int CMap<KEY, DATA>::Size()
{
	return m_Size;
}

#endif