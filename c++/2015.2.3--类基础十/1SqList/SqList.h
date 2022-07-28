#ifndef _SQ_LIST_H_
#define _SQ_LIST_H_

#include "Sq.h"

class CSqList : public CSq
{
public:
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