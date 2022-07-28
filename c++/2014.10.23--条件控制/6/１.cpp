#include<iostream>

//do-while
//while
//for

void main()
{
	//do
	//{
	//	A;
	//}while(B);
	//G;
	//01)执行A
	//02)执行B，当B为真时，继续01)-02)过程
	//03)当B为假时，跳出循环执行G

	std::cout<<"开始了"<<std::endl;

	int a;
	do
	{
		std::cout<<"请输入一个大于0的数:";
		std::cin>>a;
	}while(a <= 0);

	std::cout<<"出来了"<<std::endl;

	system("pause");
}