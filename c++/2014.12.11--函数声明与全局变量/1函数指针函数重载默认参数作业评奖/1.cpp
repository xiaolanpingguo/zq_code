#include<iostream>

//01)(默认参数、函数重载) 整数浮点数的加法
int add(int a,int b,int c = 0,int d = 0,int e = 0)
{
	return a + b + c + d + e;
}

float add(float a,float b,float c = 0.0f,float d = 0.0f,float e = 0.0f)
{
	return a + b + c + d + e;
}
//02)(函数指针) 数学运算
int add1(int a,int b)
{
	return a + b ;
}
int sub(int a,int b)
{
	return a - b;
}
int mui(int a,int b)
{
	return a * b;
}
int chu(int a,int b)
{
	return a / b;
}
int mod(int a,int b)
{
	return a % b;
}

void main()
{
	int (*p[])(int,int) = {add1,sub,mul,chu,mod};
	system("pause");
}