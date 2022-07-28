#include <iostream>

struct ABC
{
	//a是一个占2位的有符号整数（-2~1）
	//b是一个占4位的有符号整数（-8~7）
	char a : 2, b : 4;
};

struct DEF
{
	//a是一个占3位的无符号整数（0~7）
	//b是一个占11位的无符号整数（0~2047）
	unsigned short a : 3, b : 11; //所有的占位和不能超过sizeof(类型)
	//c是一个int遍历
	int c;
	//d是一个占30位的有符号整数（0~2047）
	int d : 30;
};

struct XYZ1
{
	unsigned short a : 3, b : 13;
	//[b][b][b][b][b][a][a][a]
	//[b][b][b][b][b][b][b][b]
};

struct XYZ2
{
	unsigned short a : 3, b : 14;
	//[b][b][b][b][b][a][a][a]
	//[b][b][b][b][b][b][b][b]
	//[b][?][?][?][?][?][?][?]
	//[?][?][?][?][?][?][?][?]
};

void main()
{
	ABC abc;
	abc.a = -2;
	abc.a = 1;
	abc.a = 2;
	abc.b = 2;
	std::cout<<sizeof(ABC)<<std::endl;

	DEF def;
	def.a = 0;
	def.a = 7;
	def.a = 8;
	def.b = 2047;

	std::cout<<sizeof(XYZ1)<<std::endl;
	std::cout<<sizeof(XYZ2)<<std::endl;

	system("pause");
}