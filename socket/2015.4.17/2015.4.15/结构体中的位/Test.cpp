// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

struct A
{
	char a : 3, b : 4;
};
struct B
{
	short a : 10, b : 5;
};
struct C
{
	unsigned char a : 6, b : 2; //a:0~63、b:0~3
};

int _tmain(int argc, _TCHAR* argv[])
{
	A x = {}; //00000000:00
	std::cout<<sizeof(x)<<std::endl;

	x.a = 1; //00000001:01
	x.b = 2; //00010001:11
	x.a = -4; //00010100:14
	x.a = 3; //00010011:13
	x.a = 7; //00010??? = 00000111 -> 00010111
	x.a = 9; //00010??? = 00001001 -> 00010001

	B y = {}; //00000000 00000000:00 00
	y.a = 100; //01100100 00000000:64 00

	C z = {}; //00000000:00
	z.a = 63; //00111111:3f
	z.a = 64; //00000000:00

	system("pause");
	return 0;
}

//网络数据应该越小越好，越少的网络数据在传输上就越块

