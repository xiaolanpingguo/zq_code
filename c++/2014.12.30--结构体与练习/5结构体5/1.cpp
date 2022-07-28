#include<iostream>

struct _ABC
{
	char a;
	short b;
	int c;
};

struct _DEF
{
	char a;
	short b;
	char* c;
};

//结构体变量的地址不能赋值给非结构体指针
void main()
{
	_ABC x;//?? ?? ?? ?? ?? ?? ?? ?? 

	int* p = &(x.c);//int变量赋值给int指针

	//int* q = &x;//_ABC类型的地址不能赋值给int类型指针
	//char* q = &x;
	//short* q = &x;
	//bool* xx = &x;

	p[-1] = 0;//00 00 00 00  ?? ?? ?? ?? 
	p[0] = -1;//00 00 00 00  ff ff ff ff
	//00000000 00000000 00000000 00000001
	//11111111 11111111 11111111 11111110
	//11111111 11111111 11111111 11111111
	//ff ff ff ff

	_DEF y;
	y.c = &y.a;
	*(y.c) = 'a';
	y.a = 'b';
	y.c[1] = y.c[2] = y.c[3] = 3;

	system("pause");
}
