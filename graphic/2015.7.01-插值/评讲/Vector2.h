#ifndef _VECTOR_2_H_
#define _VECTOR_2_H_

#include <cmath>
#include <cassert>

#define _IS_ZERO(num) ((num)>=-0.0001&&(num)<=0.0001)

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

	float Length() const
	{
		return sqrt(x * x + y * y);
	}

	CVector2 Normalize() const
	{
		//得到长度
		float len = sqrt(x * x + y * y);

		//断言长度不为0
		assert(!_IS_ZERO(len));

		//返回单位向量
		return CVector2(x / len, y / len);
	}

	CVector2 operator + (const CVector2& that) const
	{
		return CVector2(x + that.x, y + that.y);
	}

	CVector2& operator += (const CVector2& that)
	{
		x += that.x;
		y += that.y;
		return *this;
	}

	CVector2 operator - () const
	{
		return CVector2(-x, -y);
	}

	CVector2 operator - (const CVector2& that) const
	{
		return CVector2(x - that.x, y - that.y);
	}

	CVector2& operator -= (const CVector2& that)
	{
		x -= that.x;
		y -= that.y;
		return *this;
	}

	CVector2 operator * (float num) const
	{
		return CVector2(x * num, y * num);
	}

	CVector2& operator *= (float num)
	{
		x *= num;
		y *= num;
		return *this;
	}

	//点乘
	float operator * (const CVector2& that) const
	{
		return x * that.x + y * that.y;
	}

	//投影
	CVector2 Projection(const CVector2& that) const
	{
		//得到that长度的平方
		float len_power2 = that.x * that.x + that.y * that.y;

		//断言that长度的平方不为0
		assert(!_IS_ZERO(len_power2));

		//得到点乘结果
		float dot_result = x * that.x + y * that.y;

		//得到比值
		float f = dot_result / len_power2;

		return CVector2(that.x * f, that.y * f);
	}
};

//如果要使得标量*向量也成立，那么不能写在
//向量类中，凡是向量类中的运算符重载，那么
//都是默认指定this在运算符的左侧，所以我们
//只能去重载全局的乘法
inline CVector2 operator * (float num, const CVector2 v)
{
	return CVector2(v.x * num, v.y * num);
}

#endif