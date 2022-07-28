#include <iostream>

//运算符重载
//1：尽量让运算符的使用和原始运算符的使用一致
//2：尽量不用运算符重载

class ZuoBiao
{
public:
	int x, y;

	ZuoBiao& operator ++()
	{
		x += 1;
		y += 1;
		return *this;
	}

	ZuoBiao operator ++(int)
	{
		ZuoBiao zb = *this;
		x += 1;
		y += 1;
		return zb;
	}
};

void main()
{
	//赋值运算表达式的结果是赋值完毕之后左侧的变量
	int a, b, c;
	a = 1; b = 2; c = 3;
	a = b = c; //b = c; a = b;
	std::cout<<a<<b<<c<<std::endl;

	a = 1; b = 2; c = 3;
	(a = b) = c; //a = b; a = c;
	std::cout<<a<<b<<c<<std::endl;

	//赋值表达式按照C语言传统可以放在=左侧的

	//凡是下面的这种C语言传统上不能放在=左侧
	//的表达式的运算符重载都不应该返回引用
	//(a + b) = 4;

	(a += b) = 5;

	//赋值、前置自增、前置自减、自赋值运算符、下标等运算符
	//的返回值都应该是引用
	++a = 6; //++a的结果就是变量a
	//a++ = 7; //a++的结果是a加1之前的一个临时拷贝

	system("pause");
}