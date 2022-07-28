// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//Debug版本包含了很多用于调试的信息，所以运行要慢一些
//Release版本是去除了调试信息，所以运行要快，并且Release
//版本也可以进行调试，只需要把[项目][属性][C\C++][优化]
//中的[最大化速度]设置为[禁用]那么Release版本也可以使用
//各种调试手段，在真正的项目开发中往往直接用Release开发

int _tmain(int argc, _TCHAR* argv[])
{
	int a = 1;
	int b = 2;
	int c = a + b;

	return 0;
}

