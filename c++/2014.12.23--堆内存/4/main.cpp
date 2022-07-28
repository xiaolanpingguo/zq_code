#include<iostream>

////p是堆内存，p和q没有任何的关系
//void f(char* p)
//{
//	p = (char*)malloc(10);
//}

void f(char** p)
{
	*p = (char*)malloc(10);
}

void main()
{
	char* q = 0;
	//f(q);
	f(&q);
	strcpy_s(q,4,"abc");
	std::cout<<q<<std::endl;
	system("pause");
}