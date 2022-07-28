#include <iostream>

//我们常常用循环来处理数组

void main()
{
	int a[5];

	//std::cin>>a[0]>>a[1]>>a[2]>>a[3]>>a[4];

	for (int i = 0; i < 5; ++i)
		std::cin>>a[i]; //i的变化0~4就是数组的有效范围

	for (int i = 0; i < 5; ++i)
		std::cout<<a[i]<<' ';

	system("pause");
}