#include<iostream>
//递归
//函数的默认参数
//函数的重载
//函数指针

//01)相互调用：函数A直接或者间接调用函数B
//02)递归调用: 函数A直接或者间接调用函数A
unsigned int f1(unsigned int a)
{
	int b = 1;
	for(unsigned int i = 1; i <= a; ++i)
		b += i;
	return b;
}

unsigned int f2(unsigned int a)
{
	if(1 == a)
		return 1;
	else
		return a * f2(a - 1);
}

//f3没有办法退出函数
//int f3(int a)
//{
//	return a + f3(a -1);
//}

int f3_1(int a)
{
	if(a < 0)
		return 0;
	return a + f3_1(a - 1);
}

void main()
{
	std::cout<<f1(5)<<std::endl;
	std::cout<<f2(5)<<std::endl;
	//std::cout<<f3(5)<<std::endl;
	std::cout<<f3_1(5)<<std::endl;
	//return 5 * f2(4);
	//return 5 * 4 * f2(3);
	//return 5 * 4 * 3 * f2(2);
	//return 5 * 4 * 3 * 2 * f2(1);
	//return 5 * 4 * 3 * 2 * 1 * 1;
	system("pause");
}
//递归函数必须需要处理：当满足某个条件的时候
//就不调用自身函数了