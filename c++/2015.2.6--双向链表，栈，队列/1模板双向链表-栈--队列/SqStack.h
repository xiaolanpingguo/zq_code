#ifndef _SQSTACK_H_
#define _SQSTACK_H_


//顺序栈
template <typename T>
class CSqStack
{
	int m_Size;
	int m_Length;
	T* m_Data;
public:
	CSqStack(int size = 8);
	CSqStack(const CSqStack& that);
	CSqStack& operator = (const CSqStack& that);
	~CSqStack();

	//推入
	void Push(T data);
	//弹出栈顶元素
	bool Pop(T* pdata);
	//获取栈顶
	bool GetTop(T* pdata);
	//清除
	void Clear();
	//长度
	int Length();
};

template <typename T>
CSqStack<T>::CSqStack(int size)
:
m_Size(size),
m_Length(0),
m_Data(new T[m_Size])
{
}

template <typename T>
CSqStack<T>::CSqStack(const CSqStack& that)
:
m_Size(that.m_Size),
m_Length(that.m_Length),
m_Data(new T[m_Size])
{
	for(int i = 0; i < m_Length; ++i)
		m_Data[i] = that.m_Data[i];
}

template <typename T>
CSqStack<T>& CSqStack<T>::operator = (const CSqStack& that)
{
	if(this != &that)
	{
		delete []m_Data;
		m_Size = that.m_Size;
		m_Length = that.m_Length;
		m_Data = new T[m_Size];
		for(int i = 0; i < m_Length; ++i)
			m_Data[i] = that.m_Data[i];
	}
	return *this;
}

template <typename T>
CSqStack<T>::~CSqStack()
{
	if(m_Data)
		delete []m_Data;
}

//推入
template <typename T>
void CSqStack<T>::Push(T data)
{
	if(m_Length == m_Size)
	{
		T* p = new T[m_Size *= 2];
		for(int i = 0; i < m_Length;++i)
			p[i] = m_Data[i];
		delete []m_Data;
		m_Data = p;
	}
	m_Data[m_Length++] = data;
}

//弹出栈顶元素
template <typename T>
bool CSqStack<T>::Pop(T* pdata)
{
	if(m_Length == 0)
		return false;
	*pdata = m_Data[m_Length - 1];
	m_Length -= 1;
	return true;
}

//获取栈顶
template <typename T>
bool CSqStack<T>::GetTop(T* pdata)
{
	if(m_Length == 0)
		return false;
	*pdata = m_Data[m_Length - 1];
	return true;
}

//清除
template <typename T>
void CSqStack<T>::Clear()
{
	m_Length = 0;
}

//长度
template <typename T>
int CSqStack<T>::Length()
{
	return m_Length;
}

#endif