#include "Sq.h"

CSq::CSq()
:
m_Size(32),
m_Length(0),
m_Array(new SQDATA[m_Size])
{}

CSq::CSq(const CSq& that)
:
m_Size(that.m_Size),
m_Length(that.m_Length),
m_Array(new SQDATA[m_Size])
{
	for (int i = 0; i < m_Length; ++i)
		m_Array[i] = that.m_Array[i];
}

CSq::~CSq()
{
	delete [] m_Array;
}

CSq& CSq::operator = (const CSq& that)
{
	if (this != &that)
	{
		if (m_Size < that.m_Size)
		{
			delete [] m_Array;
			m_Array = new SQDATA[m_Size = that.m_Size];
		}
		m_Length = that.m_Length;
		for (int i = 0; i < m_Length; ++i)
			m_Array[i] = that.m_Array[i];
	}
	return *this;
}

bool CSq::Insert(SQDATA d, int p)
{
	if (p < 1 || p > m_Length + 1)
		return false;

	if (m_Length == m_Size)
	{
		SQDATA* q = new SQDATA[m_Size *= 2];
		for (int i = 0; i < m_Length; ++i)
			q[i] = m_Array[i];
		delete [] m_Array;
		m_Array = q;
	}

	int m = m_Length - p + 1;
	for (int i = 0; i < m; ++i)
		m_Array[m_Length - i] = m_Array[m_Length - 1 - i];

	m_Array[p - 1] = d;

	m_Length += 1;

	return true;
}

void CSq::Push(SQDATA d)
{
	Insert(d, m_Length + 1);
}

bool CSq::Erase(int p)
{
	if (p < 1 || p > m_Length)
		return false;

	int m = m_Length - p;
	for (int i = 0; i < m; ++i)
		m_Array[p - 1 + i] = m_Array[p + i];

	m_Length -= 1;

	return true;
}

void CSq::Clear()
{
	m_Length = 0;
}

SQDATA* CSq::Get(int p)
{
	return (p < 1 || p > m_Length) ? 0 : m_Array + p - 1;
}

int CSq::Length()
{
	return m_Length;
}

int CSq::Locate(int b, SQDATA d, bool (* e)(SQDATA, SQDATA))
{
	if (b < 1 || b > m_Length)
		return 0;

	for (int i = b - 1; i < m_Length; ++i)
	{
		if ((*e)(d, m_Array[i]))
			return i + 1;
	}

	return 0;
}

void CSq::Sort(bool (* b)(SQDATA, SQDATA), bool i)
{
	int a = m_Length - 1;

	if (i)
	{
		for (int i = 0; i < a; ++i)
		{
			for (int j = 0; j < a - i; ++j)
			{
				if ((*b)(m_Array[j], m_Array[j + 1]))
				{
					SQDATA d = m_Array[j];
					m_Array[j] = m_Array[j + 1];
					m_Array[j + 1] = d;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < a; ++i)
		{
			for (int j = 0; j < a - i; ++j)
			{
				if ((*b)(m_Array[j + 1], m_Array[j]))
				{
					SQDATA d = m_Array[j];
					m_Array[j] = m_Array[j + 1];
					m_Array[j + 1] = d;
				}
			}
		}
	}
}