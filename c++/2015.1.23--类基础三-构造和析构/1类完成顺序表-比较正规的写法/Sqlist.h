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
	void Create(int size = 8);
	void Destroy();
	bool Insert(CSLDATA data , int pos);
	void Push(CSLDATA data);
	bool Erase(int pos);
	void Clear();
	CSLDATA* Get(int pos);
	int GetLength();
};

#endif