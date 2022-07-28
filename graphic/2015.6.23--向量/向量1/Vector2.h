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
};

#endif