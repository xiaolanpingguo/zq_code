#include<iostream>


void main()
{
	int a1,b1,c1;//a1,b1,c1是int类型的变量
	int* a2,b2,c2;//a2是int类型的指针，b2,c2是int类型的变量
	//int *a2;
	//int b2;
	//int c2;
	a2 = &a1;
	//b2 = &b1;
	//c2 = &c1;
	a2 = &b2;
	a2 = &c2;

	int *a3,*b3,*c3;//a3,b3,c3都是int类型的指针
	a3 = &a1;
	b3 = &b1;
	c3 = &c1;
	system("pause");
}