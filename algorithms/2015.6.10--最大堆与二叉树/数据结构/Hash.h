#ifndef _HASH_H_
#define _HASH_H_

template <typename KEY, typename DATA>
class CHash //KEY必须有<运算符，KEY是唯一的
{
public:
	struct PAIR //键值对结构体
	{
		KEY key;
		DATA data;
	};

private:
	struct MAP //映射
	{
		int capacity;
		int size;
		PAIR* pair;
	};
	int (* m_HashFunc)(KEY); //哈希函数指针
	int m_Capacity; //哈希表容量
	int m_Size; //键值对个数
	MAP* m_Hash; //哈希表

public:

	CHash(int (* HashFunc)(KEY), int Capacity = 256);
	CHash(const CHash& that);
	CHash& operator = (const CHash& that);
	~CHash();

	bool Insert(KEY key, DATA data); //插入
	bool Erase(KEY key); //删除
	PAIR* Find(KEY key); //通过数据来得到数据地址
	void Clear(); //清空
	int Size(); //长度

	//建议写迭代器来进行Hash表的遍历
};

template <typename KEY, typename DATA>
CHash<KEY,DATA>::CHash(int (* HashFunc)(KEY), int Capacity)
:
m_HashFunc(HashFunc),
m_Capacity(Capacity),
m_Size(0),
m_Hash(new MAP[m_Capacity])
{
	//将所有的映射的容量设置为0表示为空映射
	for (int i = 0; i < m_Capacity; ++i)
		m_Hash[i].capacity = 0;
}

template <typename KEY, typename DATA>
CHash<KEY,DATA>::CHash(const CHash& that)
:
m_HashFunc(that.m_HashFunc),
m_Capacity(that.m_Capacity),
m_Size(that.m_Size),
m_Hash(new MAP[m_Capacity])
{
	for (int i = 0; i < m_Capacity; ++i)
	{
		if (0 == that.m_Hash[i].capacity)
			m_Hash[i].capacity = 0;
		else
		{
			m_Hash[i].capacity = that.m_Hash[i].capacity;
			m_Hash[i].size = that.m_Hash[i].size;
			m_Hash[i].pair = new PAIR[m_Hash[i].capacity];
			for (int j = 0; j < m_Hash[i].size; ++j)
				m_Hash[i].pair[j] = that.m_Hash[i].pair[j];
		}
	}
}

template <typename KEY, typename DATA>
CHash<KEY,DATA>& CHash<KEY,DATA>::operator = (const CHash& that)
{
	if (this != &that)
	{
		//释放
		for (int i = 0; i < m_Capacity; ++i)
		{
			if (m_Hash[i].capacity > 0)
				delete [] m_Hash[i].pair;
		}
		delete [] m_Hash;

		//创建
		m_HashFunc = that.m_HashFunc;
		m_Capacity = that.m_Capacity;
		m_Size = that.m_Size;
		m_Hash = new MAP[m_Capacity];
		for (int i = 0; i < m_Capacity; ++i)
		{
			if (0 == that.m_Hash[i].capacity)
				m_Hash[i].capacity = 0;
			else
			{
				m_Hash[i].capacity = that.m_Hash[i].capacity;
				m_Hash[i].size = that.m_Hash[i].size;
				m_Hash[i].pair = new PAIR[m_Hash[i].capacity];
				for (int j = 0; j < m_Hash[i].size; ++j)
					m_Hash[i].pair[j] = that.m_Hash[i].pair[j];
			}
		}
	}

	return true;
}

template <typename KEY, typename DATA>
CHash<KEY,DATA>::~CHash()
{
	for (int i = 0; i < m_Capacity; ++i)
	{
		if (m_Hash[i].capacity > 0)
			delete [] m_Hash[i].pair;
	}
	delete [] m_Hash;
}

template <typename KEY, typename DATA>
bool CHash<KEY,DATA>::Insert(KEY key, DATA data)
{
	//哈希查找
	int index = (*m_HashFunc)(key) % m_Capacity;

	//当前下标上的映射还没有数据
	if (0 == m_Hash[index].capacity)
	{
		m_Hash[index].capacity = 4;
		m_Hash[index].size = 1;
		m_Hash[index].pair = new PAIR[m_Hash[index].capacity];
		m_Hash[index].pair[0].key = key;
		m_Hash[index].pair[0].data = data;
	}
	//当前下标上的映射已经有数据了
	else
	{
		//折半插入
		int begin = 0, end = m_Hash[index].size - 1;
		while (begin <= end)
		{
			int half = (begin + end) / 2;
			if (key < m_Hash[index].pair[half].key)
				end = half - 1;
			else if (m_Hash[index].pair[half].key < key)
				begin = half + 1;
			else
				return false;
		}

		//扩容
		if (m_Hash[index].size == m_Hash[index].capacity)
		{
			PAIR* p = new PAIR[m_Hash[index].capacity *= 2];
			for (int i = 0; i < m_Hash[index].size; ++i)
				p[i] = m_Hash[index].pair[i];
			delete [] m_Hash[index].pair;
			m_Hash[index].pair = p;
		}

		//插入
		int m = m_Hash[index].size - begin;
		for (int i = 0; i < m; ++i)
			m_Hash[index].pair[m_Hash[index].size - i] = m_Hash[index].pair[m_Hash[index].size - 1 - i];
		m_Hash[index].pair[begin].key = key;
		m_Hash[index].pair[begin].data = data;
		m_Hash[index].size += 1;
	}

	m_Size += 1;

	return true;
}

template <typename KEY, typename DATA>
bool CHash<KEY,DATA>::Erase(KEY key)
{
	//哈希查找
	int index = (*m_HashFunc)(key) % m_Capacity;

	//当前位置没有数据
	if (m_Hash[index].capacity == 0)
		return false;

	//折半查找
	int begin = 0, end = m_Hash[index].size - 1;
	while (begin <= end)
	{
		int half = (begin + end) / 2;
		if (key < m_Hash[index].pair[half].key)
			end = half - 1;
		else if (m_Hash[index].pair[half].key < key)
			begin = half + 1;
		else
		{
			int m = m_Hash[index].size - half - 1;
			for (int i = 0; i < m; ++i)
				m_Hash[index].pair[half + i] = m_Hash[index].pair[half + 1 + i];
			m_Hash[index].size -= 1;
			m_Size -= 1;
			return true;
		}
	}

	return false;
}

template <typename KEY, typename DATA>
typename CHash<KEY,DATA>::PAIR* CHash<KEY,DATA>::Find(KEY key)
{
	//哈希查找
	int index = (*m_HashFunc)(key) % m_Capacity;

	//当前位置没有数据
	if (m_Hash[index].capacity == 0)
		return 0;

	//折半查找
	int begin = 0, end = m_Hash[index].size - 1;
	while (begin <= end)
	{
		int half = (begin + end) / 2;
		if (key < m_Hash[index].pair[half].key)
			end = half - 1;
		else if (m_Hash[index].pair[half].key < key)
			begin = half + 1;
		else
			return &m_Hash[index].pair[half];
	}

	return 0;
}

template <typename KEY, typename DATA>
void CHash<KEY,DATA>::Clear()
{
	for (int i = 0; i < m_Capacity; ++i)
	{
		if (m_Hash[i].capacity > 0)
		{
			delete [] m_Hash[i].pair;
			m_Hash[i].capacity = 0;
		}
	}
	m_Size = 0;
}

template <typename KEY, typename DATA>
int CHash<KEY,DATA>::Size()
{
	return m_Size;
}

#endif