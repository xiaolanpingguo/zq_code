#include <iostream>

void main()
{
	std::cout<<"abcdef"<<std::endl;

	//"abcdef"的本质和s这char数组名没有区别
	std::cout<<"abcdef"[2]<<std::endl;

	char s1[7] = "abcdef";

	std::cout<<s1[2]<<std::endl;

	char s2[5] = {'a','b','c','d','e'};
	std::cout<<s2<<std::endl;

	char s3[6] = {'a','b','c','d','e',0};
	std::cout<<s3<<std::endl;

	s2[3] = 0;
	std::cout<<s2<<std::endl;

	s2[4] = 0;
	std::cout<<s2<<std::endl;

	//打印
	//std::cout<<字符地址：打印一个字符串
	//std::cout<<字符地址[?]:打印一个字符变量

	char s4[]={'a','b','0','d','e','0','g'};
	std::cout<<s4<<std::endl;

	char s5[] = "xyzdef";
	s5[4] = 0;
	std::cout<<s5<<std::endl;
	//"xyzdef"[3] = 0;//左值指定 const 对象
	
	system("pause");
}