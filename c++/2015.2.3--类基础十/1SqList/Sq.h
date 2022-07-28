#ifndef _SQ_H_
#define _SQ_H_

#ifndef SQDATA
#define SQDATA int
#endif

class CSq
{
	int m_Size;
	int m_Length;
	SQDATA* m_Array;

protected:
	CSq();
	CSq(const CSq& that);
	~CSq();
	CSq& operator = (const CSq& that);

	bool Insert(SQDATA d, int p);
	void Push(SQDATA d);
	bool Erase(int p);
	void Clear();
	SQDATA* Get(int p);
	int Length();
	int Locate(int b, SQDATA d, bool (* e)(SQDATA, SQDATA));
	void Sort(bool (* b)(SQDATA, SQDATA), bool i);
};

#endif