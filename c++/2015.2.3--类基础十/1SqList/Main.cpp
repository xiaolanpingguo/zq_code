#include <iostream>
#include "SqList.h"

bool e(int a, int b)
{
	return a == b;
}

bool b(int a, int b)
{
	return a > b;
}

void main()
{
	CSqList sqlist;

	sqlist.Insert(100, 1);
	sqlist.Insert(200, 1);
	sqlist.Insert(300, 1);
	sqlist.Push(400);
	sqlist.Erase(2);
	sqlist.Sort(b, true);
	sqlist.Clear();
	std::cout<<sqlist.Locate(1, 400, e)<<std::endl;
	std::cout<<sqlist.Locate(1, 200, e)<<std::endl;

	for (int i = 1; i <= sqlist.Length(); ++i)
		std::cout<<*sqlist.Get(i)<<std::endl;

	
	system("pause");
}