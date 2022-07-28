#include <iostream>

class A
{
public:
	A& operator = (const A& that)
	{
		return *this;
	}
};

//运算符重载
//01)让我们的类支持某些本身不能进行的运算
//02)运算符重载本质是函数
//03)有4个运算符不能重载: 
//.
//:: 
//?:
//sizeof
//04)单目运算符的形式参数必须为空
//   后置的++，--的形式参数是一个
//   不使用的int
//05)双目运算符的形式参数只能有一个

class ZuoBiao
{
public:
	int x,y;
	
	ZuoBiao(int X = 0,int Y = 0)
		:
	x(X),y(Y)
	{
	
	}

	//算术运算符的返回值一般是相加类型的临时量
	//而不是引用
	ZuoBiao operator + (const ZuoBiao& that)
	{
		//this + that
		ZuoBiao zb(x + that.x,y + that.y);
		return zb;
	}

	//赋值，自赋值运算符的返回值一般是相加类型的
	//引用，应该设置*this

	ZuoBiao& operator += (const ZuoBiao& that)
	{
		x += that.x;
		y += that.y;
		return *this;
	}

	//前置++
	ZuoBiao& operator ++()
	{
		++x;
		++y;
		return *this;
	}

	//后置++
	//形式参数是一个不使用的int
	ZuoBiao operator ++(int)
	{
		ZuoBiao zb(x,y);
		++x;
		++y;
		return zb;
	}
	
	//负号
	ZuoBiao operator -()
	{
		ZuoBiao zb(-x,-y);
		return zb;
	}


};

//- * / % 
//-= ,*= ,/=, %=
//--
//== != >= <= > < 
//&& || !

void main()
{
	ZuoBiao zb1(1,2),zb2(3,4);
	ZuoBiao zb3 = zb1+zb2;
	//+ 默认拷贝构造
	//ZuoBiao zb3 = zb1.operator +(zb2);
	//完全等同于上面的代码

	zb3 += zb1;

	++zb3;

	ZuoBiao zb4 = zb3++;
	system("pause");
}
