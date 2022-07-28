#include <iostream>

void f(int i)
{
	try
	{
		switch (i)
		{
		case 0: throw true;
		case 1: throw 'A';
		case 2: throw 1;
		case 3: throw 1.0;
		}
	}
	catch (bool b)
	{
		std::cout<<"捕获了bool异常"<<b<<std::endl;
	}
}

void f2(...)
{}

int add_num(int num, ...)
{
	int* p = &num + 1;
	int add = 0;
	for (int i = 0; i < num; ++i)
		add += p[i];
	return add;
}

void main()
{
	try
	{
		f(3);
	}
	catch (int i)
	{
		std::cout<<"捕获了int异常"<<i<<std::endl;
	}
	catch (...) //如果要写...那么一定要写在try-catch的最后
	{
		std::cout<<"捕获了未知异常"<<std::endl;
	}

	//...的两种用法
	//1）在catch块中表示要捕获任何类型异常，但是
	//   这么写的话是不能得到具体的异常值
	//2）定义不定参函数的，...表示任意类型和任意
	//   数量的函数

	//f2(1);
	//f2(1, 2);
	//f2(1, 2, 3, 4, 5);

	std::cout<<add_num(3, 5, 7, 9)<<std::endl;
	std::cout<<add_num(5, 5, 7, 9, 11, 13)<<std::endl;
	
	system("pause");
}