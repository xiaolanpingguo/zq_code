#include<iostream>

class XYZ
{
public:
	char x;
	short y;
	int z;
	void f(char X,short Y,int Z)
	{
		this->x = X;
		y = Y;
		z = Z;
	}
	void h()
	{
		std::cout<<x<<" "<<y<<" "<<z<<std::endl;
	}
};

//类在处理成员函数的时候，做了特殊的变化，比如上面的这
//两个函数，就变为
//void f(XYZ* this,char X,short Y,int Z)
//{
//	this->x = X;
//	this->y = Y;
//	this->z = Z;
//}
//void h(XYZ* this)
//{
//	std::cout<<this->x<<" "<<this->y<<" "<<this->z<<std::endl;
//}

//成员函数都会被加入一个隐藏的形式参数，这个形式参数的名字叫this,
//类型是本类的指针，然后在成员函数中的所有成员变量之前都加上this->

//void main()
//{
//	XYZ a;
//	a.f('q',1,2);//f(&a,'q',1,2)
//	a.h();//h(&a)
//
//	XYZ b;
//	b.f('p',3,4);//f(&b,'q',1,2)
//	b.h();//h(&b)
//	system("pause");
//}

//编译器在处理上面的XYZ的时候
//大概变成下面的样子：一个结构体加上一组函数。
//这些函数的第一个参数到是这个结构体的指针，
//可见成员函数的本质就是一个普通函数，只不过编译器
//自动为其加上this指针。使之调用的时候更方便

struct XYZ2
{
	char x;
	short y;
	int z;
};

void f(XYZ2* thiss,char X,short Y,int Z)
{
	thiss->x = X;
	thiss->y = Y;
	thiss->z = Z;
}
void h(XYZ2* thiss)
{
	std::cout<<thiss->x<<" "<<thiss->y<<" "<<thiss->z<<std::endl;
}

void main()
{
	XYZ2 a;
	f(&a,'q',1,2);
	h(&a);

	XYZ2 b;
	f(&b,'p',3,4);
	h(&b);
	system("pause");
}