#ifndef _SQLIST_H_
#define _SQLIST_H_


//模板类的实现其成员函数的定义必须和类的定义写
//在头文件中，不能分开写在cpp中.

template <typename T>
class CSqList
{
	int m_iSize;
	int m_iLength;
	T* m_tData;
public:
	CSqList(int size = 8);
	CSqList(const CSqList& that);
	CSqList& operator = (const CSqList& that);
	~CSqList();

	bool Insert(T data,int pos);
	void Push(T data);
	bool Erase(int pos);
	void Clear();
	int Length();
	int Find(T data,int begin);
	void Sort(bool increase);
	T* Get(int pos);
};

template <typename T>
CSqList<T>::CSqList(int size)
:
m_iSize(size),
m_iLength(0),
m_tData(new T[m_iSize])
{}
template <typename T>
CSqList<T>::CSqList(const CSqList& that)
:
m_iSize(that.m_iSize),
m_iLength(that.m_iLength),
m_tData(new T[m_iSize])
{
	for(int i = 0; i < m_iLength; ++i)
		m_tData[i] = that.m_tData[i];
}
template <typename T>
CSqList<T>& CSqList<T>::operator = (const CSqList& that)
{
	if(this != &that)
	{
		delete []m_tData;
		m_iSize = that.m_iSize;
		m_iLength = that.m_iLength;
		m_tData = new T[m_iSize];
		for(int i = 0; i < m_iLength; ++i)
			m_tData[i] = that.m_tData[i];
	}
	return *this;
}
template <typename T>
bool CSqList<T>::Insert(T data,int pos)
{
	if(pos < 0 || pos > m_iLength)
		return false;
	if(m_iLength == m_iSize)
	{
		T* p = new T[m_iSize *= 2];
		for(int i = 0; i < m_iLength;++i)
			p[i] = m_tData[i];
		delete []m_tData;
		m_tData = p;
	}
	int m = m_iLength - pos;
	for(int i = 0; i < m; ++i)
		m_tData[m_iLength - i] = m_tData[m_iLength - i - 1];
	m_tData[pos] = data;
	m_iLength += 1;
	return true;
}
template <typename T>
T* CSqList<T>::Get(int pos)
{
	if(pos < 0 || pos >= m_iLength)
		return 0;
	return m_tData + pos;
}

template <typename T>
CSqList<T>::~CSqList()
{
	if(m_tData)
		delete []m_tData;
}

template <typename T>
void CSqList<T>::Push(T data)
{
	Insert(data, m_iLength);
}
template <typename T>
bool CSqList<T>::Erase(int pos)
{
	if(pos < 0 || pos >= m_iLength)
		return false;
	int m = m_iLength - pos - 1;
	for(int i = 0; i < m ; ++i)
		m_tData[pos + i] = m_tData[pos + i + 1];
	m_iLength -= 1;
	return true;
}
template <typename T>
void CSqList<T>::Clear()
{
	m_iLength = 0;
}
template <typename T>
int CSqList<T>::Length()
{
	return m_iLength;
}
template <typename T>
int CSqList<T>::Find(T data,int begin)
{
	if(begin < 0 || begin >= m_iLength)
		return -2;
	for(;begin < m_iLength;++begin)
	{
		if(!(m_tData[begin] < data) 
		&& !(data < m_tData[begin]))
			return begin;
	}
	return -1;
}
template <typename T>
void CSqList<T>::Sort(bool increase)
{
	if(increase)
	{
		for(int i = m_iLength - 1; i > 0;--i)
		{
			for(int j = 0 ; j < i;++j)
			{
				if(m_tData[j + 1]<m_tData[j])
				{
					T t = m_tData[j + 1];
					m_tData[j + 1] = m_tData[j];
					m_tData[j] = t;
				}
			}
		}
	}
	else
	{
		for(int i = m_iLength - 1; i > 0;--i)
		{
			for(int j = 0 ; j < i;++j)
			{
				if(m_tData[j]<m_tData[j + 1])
				{
					T t = m_tData[j + 1];
					m_tData[j + 1] = m_tData[j];
					m_tData[j] = t;
				}
			}
		}
	}
}
#endif