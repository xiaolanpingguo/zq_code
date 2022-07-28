#include<iostream>

//告诉下面代码在整个工程中有两个全局int变量
//x,y可以使用
extern int x,y;


void main()
{
	x = 1;
	y = 2;
	//int x1,y1;
	system("pause");
}