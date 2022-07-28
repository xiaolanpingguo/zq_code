// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

float my_atof(const char* f)
{
	char a[64] = {};
	int b = 0;
	int pos = -1;
	for (int i = 0; f[i]; ++i)
	{
		if (f[i] >= '0' && f[i] <= '9')
			a[b++] = f[i];
		else
			pos = i;
	}

	int xsd = b - pos;
	float cs = 1.0f;
	for (int i = 0; i < xsd; ++i)
		cs *= 10.0f;

	//得到整数
	int d = 0;
	for (int i = 0; i < b; ++i)
	{
		d *= 10;
		d += a[i] - '0';
	}

	return d / cs;
}

int _tmain(int argc, _TCHAR* argv[])
{
	float x = my_atof("123.456");

	return 0;
}

