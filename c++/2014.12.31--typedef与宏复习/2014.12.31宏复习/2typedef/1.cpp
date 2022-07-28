#include<iostream>

//typedef

//引用是给变量起别名,而typedef关键字是给类型
//取别名

//为int类型取了一个别名叫MyInt
typedef int MyInt;

//为int*类型取了一个别名叫pMyInt
typedef int* pMyInt;

//p是一个全局的函数指针
int (*p)(int,int);

//q是一个函数指针类型，类型就是int(*)(int,int)
typedef int (*q)(int,int);

int add(int a,int b)
{
	return a + b;
}

struct ABC1
{
	int a,b,c;
}x1,*y1,z1[3];//x1,y1,z1分别是全局变量，全局指针，全局数组

typedef struct ABC2
{
	int a,b,c;
}x2,*y2;//x2,y2分别是ABC2类型，ABC2*类型的别名


void main()
{
	MyInt i = 1;//完全等同于int i = 1;
	pMyInt j = &i;//完全等同于int* j = &i;
	p = add;
	//x是q定义出来的一个函数指针
	//相当于int (*x)(int,int) = add
	q x = add;

	x2 t;
	y2 tt = &t;
	system("pause");
}