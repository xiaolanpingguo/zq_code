// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

bool is_big_endian()
{
	//大端：00 00 00 01
	//小端：01 00 00 00
	int a = 1;
	return *((char*)&a) == 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//00 00 91 41
	float a = 18.125;

	int b = 123456789;

	//x86是一个cpu体系，主要是intel、AMD公司生产
	//的微机CPU，x86体系的cpu是属于小端cpu，在所
	//有的cpu中，从存储数据的顺序来说分为大端和
	//小端两种，注意一定是超过一个字节的数据才有
	//大小端之分，x86命名是来自于intel的8086型号
	//的cpu，这款cpu的直接后续救市286、386、486
	//小端：15 cd 5b 07
	//大端：07 5b cd 15

	return 0;
}