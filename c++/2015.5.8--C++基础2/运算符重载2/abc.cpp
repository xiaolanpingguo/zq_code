#include <iostream>
#include <assert.h>

class CZuoBiao
{
	int x, y;

public:

	CZuoBiao(int X = 0, int Y = 0)
		:
	x(X),y(Y)
	{}

	//前置自增
	CZuoBiao& operator ++ ()
	{
		++x;
		++y;
		return *this;
	}

	//后置自增（C++规定用一个无用的int形参作为和前置的区别）
	CZuoBiao operator ++ (int)
	{
		CZuoBiao zb(x, y);
		x++;
		y++;
		return zb;
	}

	//下标运算符重载
	int& operator [] (bool b)
	{
		return b ? x : y;
	}

	//下标运算符重载，虽然语法可行，但是这种用法没有必要
	int& operator [] (const char* s)
	{
		return strlen(s) > 5 ? x : y;
	}

	//隐式转换

	//为我们的类添加一个默认可以被转换为int的隐式转换
	operator int ()
	{
		return x + y;
	}

	operator const char* ()
	{
		return "Hello World";
	}
};

void main()
{
	int x = 1;
	(++x) = 2; //前置自增运算符的结果是变量
	//(x++) = 3; //后置自增运算符的结果是临时量

	CZuoBiao zb1;
	CZuoBiao zb2 = ++zb1;
	CZuoBiao zb3 = zb1++;

	//类常量
	//写法：类名();
	//注意：可以用不同的构造来初始化一个常量
	int a = 1; //变量 = 常量;
	CZuoBiao zb4 = CZuoBiao(5, 5); //变量 = 常量;
	CZuoBiao zb5 = CZuoBiao(); //变量 = 常量;
	zb5[true] = 7;
	zb5[false] = 8;
	zb5["sdljfjlksdjflkjsdflkj"] = 9;
	zb5["sdl"] = 10;

	//编译器会去CZuoBiao类中去查找有没有可以被转换为
	//int类型的隐式转换，有就调用那个隐式转换
	int p = zb5;
	double q = zb5; //zb5可以被先转为int，再转为double
	const char* r = zb5;
	//int* w = zb5; //无法进行转换的表达式将会报错

	system("pause");
}