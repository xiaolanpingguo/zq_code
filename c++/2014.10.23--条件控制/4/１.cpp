#include<iostream>


void main()
{
	int a;
	std::cin>>a;

	

	if(a > 1)
	{
		std::cout<<"1"<<std::endl;
	}

	//if(A)
	//{
	//	B;
	//}
	//G;
	//判断A表达式的结果，如果为真则执行B，然后执行G
	//如果为假则直接执行G；
	//有可能运行到B，也可能运行不到
	

	if(a > 0)
	{
		std::cout<<"大于0"<<std::endl;
	}
	else
	{
		std::cout<<"小于等于0"<<std::endl;
	}

	//if(A)
	//{
	//	B;
	//}
	//else
	//{
	//	C;
	//}
	//G;
	//先判断A，如果A为真，则执行B
	//如果A为假则执行C
	//必然会有一个会运行到

	system("pause");
}