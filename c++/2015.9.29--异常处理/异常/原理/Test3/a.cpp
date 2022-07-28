#include <iostream>

class A
{
	int x, y, z;
public:
	A(){x = y = z = 0;}
};

void f1(int i)
{
	std::cout<<"f1开始"<<std::endl;
	try
	{
		std::cout<<"f1-try开始"<<std::endl;
		switch (i)
		{
		case 0: throw true;
		case 1: throw 'A';
		case 2: throw 1;
		case 3: throw 1.0;
		case 4:
			{
				A a;
				throw a;
			}
		case 5:
			{
				throw 1.0f;
			}
		}
		std::cout<<"f1-try结束"<<std::endl;
	}
	catch (bool b/*, char x*/) //catch 处理程序必须指定一种类型
	{
		std::cout<<"捕获了bool异常"<<b<<std::endl;
	}

	//如果上面的try-catch中的try块抛出了char、int、double、A
	//这几种异常，那么上面的try-catch中的catch是捕获不了的，这
	//个异常就会被向上传递给调用本函数的函数，此处是f2，相当于
	//是f2中调用f1的那句代码产生了异常

	std::cout<<"f1结束"<<std::endl;
}

void f2(int i)
{
	std::cout<<"f2开始"<<std::endl;
	try
	{
		std::cout<<"f2-try开始"<<std::endl;
		f1(i);
		std::cout<<"f2-try结束"<<std::endl;
	}
	catch (char b)
	{
		std::cout<<"捕获了char异常"<<b<<std::endl;
	}
	catch (int b)
	{
		std::cout<<"捕获了int异常"<<b<<std::endl;
	}
	std::cout<<"f2结束"<<std::endl;
}

void f3(int i)
{
	std::cout<<"f3开始"<<std::endl;
	try
	{
		std::cout<<"f3-try开始"<<std::endl;
		f2(i);
		std::cout<<"f3-try结束"<<std::endl;
	}
	catch (double b)
	{
		std::cout<<"捕获了double异常"<<b<<std::endl;
	}
	std::cout<<"f3结束"<<std::endl;
}

void main()
{
	try
	{
		f3(5);
	}
	catch (A x)
	{
		std::cout<<"捕获了A异常"<<std::endl;
	}
	
	system("pause");
}