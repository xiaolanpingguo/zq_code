#ifndef _VECTOR_2_H_
#define _VECTOR_2_H_

#include <cmath>
#include <cassert>

//浮点数最好不要直接用0.0去判断，而是取一个精度区间判断
#define _IS_ZERO(num) ((num)>-0.0001f&&(num)<+0.0001f)

class CVector2
{
public:

	float x, y;

	CVector2(float X = 0.0f, float Y = 0.0f)
		:
	x(X), y(Y)
	{}

	void Set(float X = 0.0f, float Y = 0.0f)
	{
		x = X;
		y = Y;
	}

	//得到向量长度
	float Length() const //成员函数后面加上const表示该成员函数不会去对成员变量进行写操作
	{
		return sqrt(x * x + y * y);
	}

	//得到单位向量
	CVector2 Normalize() const
	{
		//得到向量长度
		float length = sqrt(x * x + y * y);

		//断言长度非零
		assert(!_IS_ZERO(length));

		return CVector2(x / length, y / length);
	}

	//加法
	CVector2 operator + (const CVector2& that)
	{
		return CVector2(x + that.x, y + that.y);
	}

	//自加法
	CVector2& operator += (const CVector2& that)
	{
		x += that.x;
		y += that.y;
		return *this;
	}

	//取负
	CVector2 operator - ()
	{
		return CVector2(-x, -y);
	}

	//减法
	CVector2 operator - (const CVector2& that)
	{
		return CVector2(x - that.x, y - that.y);
	}

	//自减法
	CVector2& operator -= (const CVector2& that)
	{
		x -= that.x;
		y -= that.y;
		return *this;
	}

	//数乘（向量 * 标量）
	CVector2 operator * (float num)
	{
		return CVector2(x * num, y * num);
	}

	//点乘（向量 * 向量）
	float operator * (const CVector2& that)
	{
		return x * that.x + y * that.y;
	}

	//投影
	CVector2 Shadow(const CVector2& that)
	{
		//得到that长度的平方
		float f1 = that.x * that.x + that.y * that.y;

		//断言that长度的平方非零
		assert(!_IS_ZERO(f1));

		//得到this 点乘 that的结果
		float f2 = x * that.x + y * that.y;

		//得到比值
		float f3 = f2 / f1;

		return CVector2(that.x * f3, that.y * f3);
	}

	CVector2 Clock()
	{
		return CVector2(-y, x);
	}

	CVector2 CounterClock()
	{
		return CVector2(y, -x);
	}
};

//如果是在类A的类体中写的运算符重载，那么运算符的左侧
//只能是那个类的对象，如果要使得某个运算符支持这个类
//放在右侧，那么只能重载全局的运算符而不是类中的运算符
//，全局运算符没有this，其本质就是一个全局函数（因为写
//在h头文件中的，所以加上inline），下面的运算符重载代
//码就支持了num * v

//数乘（标量 * 向量）
inline CVector2 operator * (float num, const CVector2& v)
{
	return CVector2(v.x * num, v.y * num);
}

#endif