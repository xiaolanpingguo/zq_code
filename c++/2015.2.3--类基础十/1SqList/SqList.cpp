#include "SqList.h"

bool CSqList::Insert(SQDATA d, int p)
{
	if(p < 1 || p > CSq::Length() + 1)
		return false;
	return CSq::Insert(d,p);
}
void CSqList::Push(SQDATA d)
{
	CSq::Push(d);
}
bool CSqList::Erase(int p)
{
	if (p < 1 || p > CSq::Length())
		return false;
	return CSq::Erase(p);
}
void CSqList::Clear()
{
	CSq::Clear();
}
SQDATA* CSqList::Get(int p)
{
	if (p < 1 || p > CSq::Length())
		return 0;
	return CSq::Get(p);
}
int CSqList::Length()
{
	return CSq::Length();
}
int CSqList::Locate(int b, SQDATA d, bool (* e)(SQDATA, SQDATA))
{
	return CSq::Locate(b,d,e);
}
void CSqList::Sort(bool (* b)(SQDATA, SQDATA), bool i)
{
	CSq::Sort(b,i);
}