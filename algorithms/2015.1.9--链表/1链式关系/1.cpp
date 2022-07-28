#include <iostream>

//struct _XYZ1
//{
//	int a;
//	_XYZ1 x;//结构体重不能有自己定义的成员变量
//};

struct _XYZ2
{
	int z;
	_XYZ2* a;//结构体中可以有自己定义的成员指针
};

void main()
{
	_XYZ2 u1 = {100};
	_XYZ2 u2 = {200};
	_XYZ2 u3 = {300};
	_XYZ2 u4 = {400};
	_XYZ2 u5 = {500};

	u1.a = &u3;
	u3.a = &u2;
	u2.a = &u5;
	u5.a = &u4;
	u4.a = 0;
	for(_XYZ2* p = &u1;p;p = p->a)
		std::cout<<p->z<<std::endl;
	system("pause");
}