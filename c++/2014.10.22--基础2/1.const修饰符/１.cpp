#include <iostream>

//const
//constant:永恒的，不变的
//用const修饰的标识符
//必须初始化
//只能读不能写的
//const
void main()
{
	//const 数据类型 标识符 = 值
	const int a = 0;

	const char b = 'a';

	const int c = a;

	int d = 10;

	const int e = d;

	//const int a1;//必须初始化
	//a = 10;//不能赋值

	//1
	double r;
	std::cin>>r;
	std::cout<<2 * r * 3.1415926<<std::endl;
	
	//2
	double r1;
	double pai1 = 3.1415926;
	std::cin>>r1;
	std::cout<<2 * r1 * pai1<<std::endl;
	
	//3
	double r2;
	const double pai2 = 3.1415926;
	std::cin>>r2;
	std::cout<<2 * r2 * pai2<<std::endl;

	system("pause");
}