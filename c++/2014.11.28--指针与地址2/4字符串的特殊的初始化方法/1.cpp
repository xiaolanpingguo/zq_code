#include<iostream>


void main()
{
	char a[] = "123abc";
	char b[7] = "123abc";
	char c[256] = "123abc";

	//01
	char* a1 = "456def";
	std::cout<<a1<<std::endl;

	std::cout<<a<<std::endl;

	a[0] = 'A';

	std::cout<<a<<std::endl;

	//a1[0] = 'A';

	//std::cout<<a1<<std::endl;

	for(int i = 0; i < 6; ++i)
	{
		a[i] = a1[i];
	}
	std::cout<<a<<std::endl;

	//地址是常量，a1是指针，指针是存储地址的变量
	//a = a1;//=左侧不能是常量

	a1 = a;

	system("pause");
}