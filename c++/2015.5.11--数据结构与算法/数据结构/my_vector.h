#ifndef _MY_VECTOR_H_
#define _MY_VECTOR_H_

#include <assert.h>

template <typename T>
class my_vector
{
	int m_capacity;
	int m_size;
	T* m_data;

public:

	my_vector(int capacity = 8);
	my_vector(const my_vector& that);
	my_vector& operator = (const my_vector& that);
	~my_vector();

	void push_back(T data);
	void clear();
	int size();
	T& at(int index);
	
	class iterator
	{
		template <typename T>
		friend class my_vector;

		my_vector* p; //指向的my_vector
		int cur; //当前表示的my_vector中的下标

	public:
		iterator();
		bool operator != (const iterator& that);
		iterator& operator ++ ();
		iterator operator ++ (int);
		iterator& operator -- ();
		iterator operator -- (int);
		iterator operator + (int num);
		iterator& operator += (int num);
		iterator operator - (int num);
		iterator& operator -= (int num);
		T& operator * ();
		T* operator -> ();
	};

	iterator begin();
	iterator end();
	iterator insert(iterator& it, T data);
	iterator erase(iterator& it);
};

template <typename T>
my_vector<T>::my_vector(int capacity)
:
m_capacity(capacity),
m_size(0),
m_data(new T[m_capacity])
{}

template <typename T>
my_vector<T>::my_vector(const my_vector& that)
:
m_capacity(that.m_capacity),
m_size(that.m_size),
m_data(new T[m_capacity])
{
	for (int i = 0; i < m_size; ++i)
		m_data[i] = that.m_data[i];
}

template <typename T>
my_vector<T>& my_vector<T>::operator = (const my_vector& that)
{
	if (this != &that)
	{
		delete [] m_data;
		m_capacity = that.m_capacity;
		m_size = that.m_size;
		m_data = new T[m_capacity];
		for (int i = 0; i < m_size; ++i)
			m_data[i] = that.m_data[i];
	}

	return *this;
}

template <typename T>
my_vector<T>::~my_vector()
{
	delete [] m_data;
}

template <typename T>
void my_vector<T>::push_back(T data)
{
	if (m_size == m_capacity)
	{
		T* p = new T[m_capacity *= 2];
		for (int i = 0; i < m_size; ++i)
			p[i] = m_data[i];
		delete [] m_data;
		m_data = p;
	}
	m_data[m_size++] = data;
}

template <typename T>
void my_vector<T>::clear()
{
	m_size = 0;
}

template <typename T>
int my_vector<T>::size()
{
	return m_size;
}

template <typename T>
T& my_vector<T>::at(int index)
{
	assert(index >= 0 && index < m_size);
	return m_data[index];
}

template <typename T>
my_vector<T>::iterator::iterator()
:
p(0), //初始化指向的my_vector为空
cur(-1) //初始化代表的下标为-1
{}

template <typename T>
bool my_vector<T>::iterator::operator != (const iterator& that)
{
	return p != that.p || cur != that.cur;
}

//如果模板类中函数返回值类型是模板类中的类，那么前面必须加上
//typename以表示这个东西是一个模板类中的类

template <typename T>
typename my_vector<T>::iterator& my_vector<T>::iterator::operator ++ ()
{
	//断言当前迭代器表示的位置是可以进行前置++
	assert(p && cur >= 0 && cur < p->m_size);
	++cur;
	return *this;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::iterator::operator ++ (int)
{
	//断言当前迭代器表示的位置是可以进行后置++
	assert(p && cur >= 0 && cur < p->m_size);
	iterator it = *this;
	cur++;
	return it;
}

template <typename T>
typename my_vector<T>::iterator& my_vector<T>::iterator::operator -- ()
{
	//断言当前迭代器表示的位置是可以进行前置--
	assert(p && cur > 0 && cur <= p->m_size);
	--cur;
	return *this;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::iterator::operator -- (int)
{
	//断言当前迭代器表示的位置是可以进行后置--
	assert(p && cur > 0 && cur <= p->m_size);
	iterator it = *this;
	cur--;
	return it;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::iterator::operator + (int num)
{
	assert(p && cur + num >= 0 && cur + num <= p->m_size);
	iterator it;
	it.p = p;
	it.cur = cur + num;
	return it;
}

template <typename T>
typename my_vector<T>::iterator& my_vector<T>::iterator::operator += (int num)
{
	assert(p && cur + num >= 0 && cur + num <= p->m_size);
	cur += num;
	return *this;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::iterator::operator - (int num)
{
	assert(p && cur - num >= 0 && cur - num <= p->m_size);
	iterator it;
	it.p = p;
	it.cur = cur - num;
	return it;
}

template <typename T>
typename my_vector<T>::iterator& my_vector<T>::iterator::operator -= (int num)
{
	assert(p && cur - num >= 0 && cur - num <= p->m_size);
	cur -= num;
	return *this;
}

template <typename T>
T& my_vector<T>::iterator::operator * ()
{
	//断言当前迭代器表示的位置是可以得到数据
	assert(p && cur >= 0 && cur < p->m_size);
	return p->m_data[cur];
}

template <typename T>
T* my_vector<T>::iterator::operator -> ()
{
	//断言当前迭代器表示的位置是可以得到数据
	assert(p && cur >= 0 && cur < p->m_size);
	return p->m_data + cur;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::begin()
{
	iterator it;
	it.p = this;
	it.cur = 0;
	return it;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::end()
{
	iterator it;
	it.p = this;
	it.cur = m_size;
	return it;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::insert(iterator& it, T data)
{
	iterator r = end();

	//一旦参数无效就返回end位置
	if (it.p != this || it.cur < 0 || it.cur > m_size)
		return r;

	//扩容
	if (m_size == m_capacity)
	{
		T* p = new T[m_capacity *= 2];
		for (int i = 0; i < m_size; ++i)
			p[i] = m_data[i];
		delete [] m_data;
		m_data = p;
	}

	//插入
	int move = m_size - it.cur;
	for (int i = 0; i < move; ++i)
		m_data[m_size - i] = m_data[m_size - 1 - i];
	m_data[it.cur] = data;
	m_size += 1;

	//设置返回值
	r = it;

	//设置传入的迭代器无效
	it.p = 0;
	it.cur = -1;

	//返回
	return r;
}

template <typename T>
typename my_vector<T>::iterator my_vector<T>::erase(iterator& it)
{
	assert(it.p == this && it.cur >= 0 && it.cur < m_size);

	//删除
	int move = m_size - it.cur - 1;
	for (int i = 0; i < move; ++i)
		m_data[it.cur + i] = m_data[it.cur + 1 + i];
	m_size -= 1;

	//设置返回值
	iterator r = it;

	//设置传入的迭代器无效
	it.p = 0;
	it.cur = -1;

	//返回
	return r;
}

#endif