#include<iostream>

struct _ABC
{
	char a;
	short b;
	int c;
};

void main()
{
	//结构体变量的初始化
	//下面的代码依次初始化：
	//x.a为1，x.b为2，x.c为3
	_ABC x = {1,2,3};

	//下面的代码依次初始化：
	//y.a为1，y.b为2，y.c
	//没有对应初始化项则被
	//初始化为0
	_ABC y = {1,2};

	_ABC z[3] = {{1,2,3},{4,5,6}};
	
	//t中的3个成员变量都为0
	_ABC t = {};
	system("pause");
}
