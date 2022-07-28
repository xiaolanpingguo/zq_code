#include<iostream>


void main()
{
	//指针是存储地址的变量
	//32位操作系统用32个二进制位(4个字节)来对
	//内存中的每个字节进行编号,也就是说只要是
	//地址就可以用4个字节存储，所以32位操作系
	//统下的指针无论什么类型都是4个字节
	char* a;//char指针
	short* b;//short指针
	int* c;//int指针
	double* d;//double指针
	
	std::cout<<sizeof(a)<<std::endl;
	std::cout<<sizeof(b)<<std::endl;
	std::cout<<sizeof(c)<<std::endl;
	std::cout<<sizeof(d)<<std::endl;
	std::cout<<sizeof(double*)<<std::endl;
	std::cout<<sizeof(double************)<<std::endl;

	system("pause");
}