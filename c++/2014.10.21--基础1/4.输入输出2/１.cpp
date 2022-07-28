#include <iostream>

void main()
{
	int a;
	int b;
	int c;

	//连续对多个变量通过输入的方式赋值可以再输入时
	//用空格区分那个变量
	std::cin>>a;
	std::cin>>b;
	std::cin>>c;

	std::cout<<a<<" "<<b<<" "<<c<<std::endl;


	int d = 10;
	d = 29;

	a = 045;//这里在整数常量前面加上一个0表示这
	//是一个八进制整数
	std::cout<<a<<std::endl;
	a = 0x145;//这里在整数常量前面加上0x则表示这个
	//是一个十六进制整数
	std::cout<<a<<std::endl;

	//没有二进制的整数常量的写法

	system("pause");
}