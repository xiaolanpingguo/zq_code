#include <iostream>

class A 
{
	int a;
public:
	A(int aa)
		:
	a(aa)
	{}


	//隐式转换
	//operator 目标类型()
	operator int()
	{
		return a;
	}

	operator const char*()
	{
		return "123abc";
	}
};

void main()
{
	A x(100);
	int y;
	y = x;

	const char* p = x;
	system("pause");
}

//运算符，隐式转换的重载本质上都是函数
//其形式参数除了个数是规定好的，其他的
//都可以由我们来处理，其返回值也可以由
//我们设置，这样太灵活,所以不推荐使用运算
//符重载。
//进行数学运算的类中比较适合使用运算符重载

 