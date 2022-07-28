#include<iostream>

void main()
{
	int a = 1,b = 2,c;
	//逗号运算符
	//(表达式1，表达式2，。。。。。表达式n)
	//从表达式1依次执行到表达式n，最终整个逗号
	//表达式的结果就是表达式n的结果

	c = (a = 3,b = 4);
	c = (a += b,a - b,(a += b) + 2);

	system("pause");
}