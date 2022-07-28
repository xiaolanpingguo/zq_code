#include <iostream>

//返回值仅仅是一个被常量1初始化的临时量（不是内存中的变量）
int f1()
{
	return 1;
}

//返回值仅仅是一个被变量x初始化的临时量（不是内存中的变量）
int x;
int f2()
{
	return x;
}

//返回值是一个被变量x初始化的引用（不是内存中的变量）
int& f3()
{
	return x;
}

void f4(int x)
{
	x = 1;
}

void f5(int& x)
{
	x = 1;
}

int& f6()
{
	int z = 1;
	return z; //warning C4172: 返回局部变量或临时变量的地址
}

int& f7()
{
	static int* p = new int;
	return *p;
}

void main()
{
	//定义的使用一个变量a
	int a;

	//定义了一个引用b被变量a初始化
	int& b = a;

	//引用就是一个变量的别名
	b = 1;

	std::cout<<a<<std::endl;

	//能够放在=运算符左侧的东西只能是变量
	//f1() = 2;
	//f2() = 3;
	f3() = 4;

	//凡是能够放在=运算符左侧的表达式结果必须是一个变量（引用）

	int y = 2;
	f4(y);
	std::cout<<y<<std::endl;
	f5(y);
	std::cout<<y<<std::endl;

	//f4(1); //int x可以被任意结果为整数的表达式初始化
	//f5(1); //int& x是引用，只能被变量初始化

	//下面的代码是修改了f6栈内存中的变量，是一个
	//局部变量，下面的代码可以修改，但是从程序来
	//说没有意义 
	f6() = 3;

	//f7()的结果就是那个堆中的变量
	f7() = 7;

	delete &f7();

	system("pause");
}



