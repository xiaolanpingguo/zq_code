// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

//定点数是一种用整数来模拟浮点数运算的方法，早期
//一些cpu没有浮点运算功能的时候会用到这种方法

typedef int FIX; //定点数类型
#define _FLOAT_FIX(num) ((FIX)(num * 256.0f))
#define _FIX_FLOAT(num) ((float)num / 256.0f)
#define _FIX_MUL(num1,num2) ((num1) * (num2) / 256.0f)
#define _FIX_DIV(num1,num2) (((float)(num1) / (num2)) * 256.0f)

//在cpu对数字的计算中，整数的运算比浮点数要快不少，早期
//的cpu有一些没有直接支持浮点数运算，都是特别为这些cpu
//增加了一个协助处理浮点数运算的部件（协处理器）

int _tmain(int argc, _TCHAR* argv[])
{
	FIX f1 = _FLOAT_FIX(3.14);
	FIX f2 = _FLOAT_FIX(6.58);
	FIX f3 = f1 + f2; //本质是整数运算
	FIX f4 = f1 - f2; //本质是整数运算
	FIX f5 = _FIX_MUL(f1, f2); //本质是整数运算
	FIX f6 = _FIX_DIV(f1, f2); //本质是整数运算
	std::cout<<_FIX_FLOAT(f3)<<std::endl;
	std::cout<<_FIX_FLOAT(f4)<<std::endl;
	std::cout<<_FIX_FLOAT(f5)<<std::endl;
	std::cout<<_FIX_FLOAT(f6)<<std::endl;

	//三维引擎中有些会用定点数加减法替换浮点数
	//加减法来提高效率

	return 0;
}