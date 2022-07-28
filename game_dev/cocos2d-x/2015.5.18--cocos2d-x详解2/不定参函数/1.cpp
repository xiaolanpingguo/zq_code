#include <iostream>

//不定参函数中使用关键字...表示从此处开始参数随意
int add(int num, ...)
{
	int* p = &num + 1;
	int a = 0;
	for (int i = 0; i < num; ++i)
		a += p[i];
	return a;
}

void main()
{
	std::cout<<add(3, 100, 101, 102)<<std::endl;
	std::cout<<add(4, 100, 101, 102, 103)<<std::endl;

	system("pause");
}