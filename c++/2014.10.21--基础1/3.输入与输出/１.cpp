#include <iostream>

//std::cout<<"":将""中的内容原封不动的打印到控制台中
//std::cout<<变量：将变量的值打印到控制台上
//std::cout<<表达式：将表达式的结果的值打印到控制台上

//std::cin>>变量：
//等待用户输入一个数，然后按回车键
//当用户按回车后，将输入的值赋值给
//变量
void main()
{
	int a;
	
	a = 10;
	
	//输出整数变量a的值
	std::cout<<a<<std::endl;
	//输出a * 2的值
	std::cout<<a * 2<<std::endl;

	//等待用户输入一个数，然后按回车键
	//当用户按回车后，将输入的值赋值给
	//a
	std::cin>>a;//65

	std::cout<<a<<std::endl;

	system("pause");

	int b = 10;

	b = 2 * 4;

	std::cin>>b;

	std::cout<<b<<std::endl;

	system("pause");
}