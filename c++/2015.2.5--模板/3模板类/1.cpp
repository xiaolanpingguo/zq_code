#include <iostream>
#include "SqList.h"

template <typename T>
class ZB
{
	T x,y;
public:
	void printZB();
	void SetX(T x);
	void SetY(T y);
	T GetX();
	T GetY();
};

template <typename T>
void ZB<T>::printZB()
{
	std::cout<<" x "<<x<<" y "<<y<<std::endl;
}
template <typename T>
void ZB<T>::SetX(T x)
{
	this->x = x;
}
template <typename T>
void ZB<T>::SetY(T y)
{
	this->y = y;
}
template <typename T>
T ZB<T>::GetX()
{
	return this->x;
}
template <typename T>
T ZB<T>::GetY()
{
	return this->y;
}

template <typename T>
void printSQLIST(CSqList<T>* sqlist)
{
	std::cout<<sqlist->Length()<<":";
	for(int i = 0; i < sqlist->Length();++i)
		std::cout<<*sqlist->Get(i)<<" ";
	std::cout<<std::endl;
}
void main()
{

	ZB<int> zb1;
	zb1.SetX(1);
	zb1.SetY(2);
	zb1.printZB();

	ZB<float> zb2;
	zb2.SetX(1.1f);
	zb2.SetY(2.2f);
	zb2.printZB();


	CSqList<double> sqlist;
	sqlist.Insert(1.1,0);
	sqlist.Insert(1.2,0);
	sqlist.Insert(1.3,0);
	sqlist.Insert(1.4,0);

	CSqList<double> sqlist1 = sqlist;
	sqlist1.Push(0.5);
	sqlist1.Push(2.5);//1.4 1.3 1.2 1.1 0.5 2.5

	sqlist = sqlist1;//1.4 1.3 1.2 1.1 0.5 2.5
	sqlist1.Erase(2);//1.4 1.3 1.1 0.5 2.5
	std::cout<<sqlist1.Find(0.5,0)<<std::endl;
	std::cout<<sqlist1.Find(5.5,0)<<std::endl;
	std::cout<<sqlist1.Find(0.5,-1)<<std::endl;
	sqlist1.Sort(false);
	printSQLIST<double>(&sqlist1);
	system("pause");
}

