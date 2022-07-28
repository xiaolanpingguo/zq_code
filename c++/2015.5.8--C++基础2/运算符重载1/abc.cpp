#include <iostream>
#include <assert.h>

//运算符重载
//1）使得我们的类支持原本不能使用的运算符
//2）重载的运算符的功能完全由程序员控制
//3）运算符重载的本质就是函数
//4）不建议在一般的类中使用运算符重载，可能会造成理解的困难
//5）字符串类中的+、一些数学类中的运算，这些场合可以用运算符重载

class Cfraction //分数
{
	int m_Numerator;
	int m_Denominator;

	int _max_common_divisor(int n1, int n2)
	{
		int n3 = n1 < n2 ? n1 : n2;
		for (int i = n3; i > 1; --i)
		{
			if (n1 % i == 0 && n2 % i == 0)
				return i;
		}
		return 1;
	}

public:

	//构造
	Cfraction(int n = 1, int d = 1)
		:
	m_Numerator(n),
	m_Denominator(d)
	{
		//断言分母不为0
		assert(m_Denominator != 0);

		//约分
		int cd = _max_common_divisor(m_Numerator, m_Denominator);
		m_Numerator /= cd;
		m_Denominator /= cd;
	}

	//加法
	Cfraction operator + (const Cfraction& that)
	{
		//分母相同
		if (m_Denominator == that.m_Denominator)
		{
			Cfraction f(m_Numerator + that.m_Numerator, m_Denominator);
			return f;
		}
		//分母不相同
		else
		{
			Cfraction f(
				m_Numerator * that.m_Denominator + that.m_Numerator * m_Denominator,
				m_Denominator * that.m_Denominator);
			return f;
		}
	}

	//自赋值加法
	Cfraction& operator += (const Cfraction& that)
	{
		//分母相同
		if (m_Denominator == that.m_Denominator)
			m_Numerator += that.m_Numerator;
		//分母不相同
		else
		{
			m_Numerator = m_Numerator * that.m_Denominator + that.m_Numerator * m_Denominator;
			m_Denominator = m_Denominator * that.m_Denominator;
		}
		//约分
		int cd = _max_common_divisor(m_Numerator, m_Denominator);
		m_Numerator /= cd;
		m_Denominator /= cd;
		return *this;
	}

	Cfraction operator * (const Cfraction& that)
	{
		Cfraction f(
			m_Numerator * that.m_Numerator,
			m_Denominator * that.m_Denominator);
		return f;
	}

	Cfraction& operator *= (const Cfraction& that)
	{
		m_Numerator *= that.m_Numerator;
		m_Denominator *= that.m_Denominator;

		//约分
		int cd = _max_common_divisor(m_Numerator, m_Denominator);
		m_Numerator /= cd;
		m_Denominator /= cd;

		return *this;
	}
};

void main()
{
	int a = 1, b = 2;
	(a += b) = 4; //+=的结果是左侧的变量

	Cfraction f1(18, 24);
	Cfraction f2 = f1;
	Cfraction f3 = f1 + f2;
	f3 = f1 * f2;

	system("pause");
}