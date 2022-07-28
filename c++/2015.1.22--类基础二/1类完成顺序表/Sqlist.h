#ifndef _C_SQ_LIST_H_
#define _C_SQ_LIST_H_

#define CSLDATA int

//一般来说在成员变量前加上m_表示是member的意思
class CSqList
{
	int m_Size;//容量
	int m_Length;//长度
	CSLDATA* m_Data;//数据
public:
	void Create(int size = 8)
	{
		m_Size = size;
		m_Length = 0;
		m_Data = (CSLDATA*)malloc(sizeof(CSLDATA) * m_Size);
	}
	void Destroy()
	{
		free(m_Data);
	}
	bool Insert(CSLDATA data , int pos)
	{
		if(pos < 0 || pos > m_Length)
			return false;
		if(m_Length == m_Size)
		{
			m_Size *= 2;
			CSLDATA* p = (CSLDATA*)malloc(sizeof(CSLDATA) * m_Size);
			for(int i = 0; i < m_Length; ++i)
				p[i] = m_Data[i];
			free(m_Data);
			m_Data = p;
		}
		int m = m_Length - pos;
		for(int  i = 0; i < m;++i)
			m_Data[m_Length - i] = m_Data[m_Length - i - 1];
		m_Data[pos] = data;
		m_Length++;
		return true;
	}

	void Push(CSLDATA data)
	{
		Insert(data,m_Length);
	}

	bool Erase(int pos)
	{
		if(pos < 0 || pos >= m_Length)
			return false;
		int m = m_Length - pos - 1;
		for(int i = 0; i < m;++i)
			m_Data[pos + i] = m_Data[pos + i + 1];
		m_Length--;
		return true;
	}

	void Clear()
	{
		m_Length = 0;
	}

	CSLDATA* Get(int pos)
	{
		if(pos < 0 || pos >= m_Length)
			return 0;
		return m_Data + pos;
	}

	int GetLength()
	{
		return m_Length;
	}

};

#endif