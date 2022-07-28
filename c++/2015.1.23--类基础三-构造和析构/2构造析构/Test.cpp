#include <iostream>

//构造函数
//01)名字必须和类名相同
//02)不能有返回值类型
//03)在分配类对象的内存之后被自动调用
//04)构造函数一般用来进行必要的初始化工作
//05)可以重载

//析构函数
//01)名字必须和类名一样,前面加上~
//02)不能有返回值类型
//03)在释放类对象的内存之前自动调用
//04)析构函数一般用来做必要的收尾工作
//05)不能重载

class ABC
{
public:
	int a;
	void f()
	{
		std::cout<<a<<std::endl;
	}

	ABC()
	{
		std::cout<<"ABC的无参构造"<<std::endl;
	}

	ABC(int a)
	{
		std::cout<<"ABC的带参构造1"<<std::endl;
	}

	ABC(float a)
	{
		std::cout<<"ABC的带参构造2"<<std::endl;
	}

	~ABC()
	{
		std::cout<<"ABC的析构函数"<<std::endl;
	}
};

void main()
{
	//01)先开辟sizeof(ABC)个字节的连续的内存块在main栈中
	//02）调用构造函数
	ABC x;//无参构造
	x.a = 1;
	x.f();

	ABC y(1);//带参构造1
	ABC z(1.0f);//带参构造2
	system("pause");
}