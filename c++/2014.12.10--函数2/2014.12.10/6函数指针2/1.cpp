#include<iostream>
//递归
//函数的默认参数
//函数的重载
//函数指针

int add2(int a,int b)
{
	return a + b;
}
int  sub2(int a,int b)
{
	return a - b;
}

void f1(int (*p)(int,int),int x,int y)
{
	std::cout<<(*p)(x,y)<<std::endl;
}

void f2(int(*p1)(int,int),int(*p2)(int,int),int x,int y)
{
	std::cout<<(*p1)((*p1)(x,y),(*p2)(y,x))<<std::endl;
}
void main()
{

	void(*p1)(int (*p)(int,int),int,int) = f1;
	(*p1)(add2,1,2);

	f1(add2,1,2);
	f1(sub2,1,2);
	f2(sub2,add2,2,3);
	system("pause");
}