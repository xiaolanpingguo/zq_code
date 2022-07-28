#include<iostream>
//递归
//函数的默认参数
//函数的重载
//函数指针

//一组名字相同，形式参数表不同(类型，数量)
//的函数就构成了函数重载
//编译器会自动根据填入的实际参数来确定调用的
//是哪个同名函数

//C++支持函数重载，C不支持函数重载
//函数重载的目的：在于减少我们的函数学习时间，一般来说
//一组功能接近的函数我们可以让他们相互重载，只要会其中一
//个那么其他的重载函数的使用也是差不多的，
//比如库函数中开方函数
//double sqrt( double x );
//float sqrt( float x );
//long double sqrt( long double x );
//注意和默认参数的使用发生调用不明确
int  add(int a,int b)
{
	return a + b;
}

float  add(float a,float b)
{
	return a + b;
}

int  add(int a,int b = 2 ,int c = 3)
{
	return a + b + c;
}

//int  add(int a,int b,int c = 3)
//{
//	return a + b + c;
//}

void main()
{
	std::cout<<add(1)<<std::endl;
	//std::cout<<add(1,2)<<std::endl;
	std::cout<<add(1.0f,2.0f)<<std::endl;
	std::cout<<add(1,2,3)<<std::endl;
	system("pause");
}