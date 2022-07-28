#include<iostream>
#include "Sqlist.h"

void main()
{
	CSqList sqlist1,sqlist2;
	sqlist1.Create();
	sqlist1.Push(1);
	sqlist1.Push(3);
	sqlist1.Push(2);
	sqlist1.Insert(4,0);
	sqlist1.Insert(5,2);
	for(int i = 0; i < sqlist1.GetLength(); ++i)
		std::cout<<*sqlist1.Get(i)<<std::endl;
	sqlist1.Destroy();



	sqlist2.Clear();
	sqlist2.Create();
	sqlist2.Push(10);
	sqlist2.Push(30);
	sqlist2.Push(20);
	sqlist2.Insert(40,0);
	sqlist2.Insert(50,2);
	for(int i = 0; i < sqlist2.GetLength(); ++i)
		std::cout<<*sqlist2.Get(i)<<std::endl;
	sqlist2.Destroy();
	system("pause");
}
