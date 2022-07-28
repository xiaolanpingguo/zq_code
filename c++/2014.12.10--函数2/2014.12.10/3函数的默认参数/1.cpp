#include<iostream>
//递归
//函数的默认参数
//函数的重载
//函数指针

int add1(int a,int b)
{
	return a + b;
}

int add2(int a = 1,int b = 2)
{
	return a + b;
}

int sub2(int a,int b = 2)
{
	return a - b;
}

//实际参数必须是从最右边形式参数往左边形式参数写
//且中间不能有隔开
//int mul2(int a = 1,int b)
//{
//	return a * b;
//}

//int add3(int a = 1,int b,int c = 3)
//{
//	return a + b + c;
//}

void main()
{
	//add2(int a = 3,int b = 4)
	std::cout<<add2(3,4)<<std::endl;
	//add2(int a = 3,int b = 2)
	std::cout<<add2(3)<<std::endl;
	//只给出了形式参数a的实参，形式参数b使用默认参数
	std::cout<<add2()<<std::endl;
	//a，b 都没有实际参数，所以都使用了默认参数
	std::cout<<sub2(4)<<std::endl;

	//std::cout<<mul2(4,3)<<std::endl;

	system("pause");
}