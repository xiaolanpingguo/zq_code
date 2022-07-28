#include<iostream>

class ABC
{
public:
	int a;//成员变量
	void b()//成员函数
	{
		std::cout<<"!"<<std::endl;
	}
};

void main()
{
	ABC x;
	x.a = 1;//通过对象访问
	x.b();
	ABC* y = &x;
	y->a = 2;//通过地址访问
	y->b();
	system("pause");
}