#include<iostream>

struct ABC1
{
	char a;
	short b;
	int c;
};

class ABC2
{
public:
	char a;
	short b;
	int c;
	void f1(char A,short B,int C)
	{
		this;
		a = A;
		b = B;
		c = C;
	}
	void f2()
	{
		this;
		std::cout<<a<<" "<<b<<" "<<c<<std::endl;
	}
};

void main()
{
	ABC1 a1 = {1,2,3},b1 = {4,5,6};
	ABC1 c1[3] = {};
	ABC1* d1 = c1;
	ABC1& e1 = a1;
	a1 = b1;
	//a1 + b1;
	sizeof(a1);
	//++a1;
	//a1 && b1;
	//a1 > b1;
	//a1 ? 1 : 2;
	1 ? a1:b1;
	//a1 & b1;
	//a1 += b1;
	c1[0] = b1;
	d1 = &b1;
	*d1 = a1;
	a1.a = 'q';
	d1->b = 2;
	//类和结构体在运算上可以使用的运算符没有区别
	ABC2 a2 = {2,2,3},b2 = {4,5,6};
	ABC2 c2[3] = {};
	ABC2* d2 = c2;
	ABC2& e2 = a2;
	a2 = b2;
	//a2 + b2;
	sizeof(a2);
	//++a2;
	//a2 && b2;
	//a2 > b2;
	//a2?2:2;
	2 ? a2:b2;
	//a2 & b2;
	//a2 += b2;
	c2[0] = b2;
	*d2 = a2;
	a2.a = 'q';
	d2->b = 2;
	d2 = &a2;

	//类多了成员函数
	d2->f1('t',7,8);
	a2.f2();
	system("pause");
}
