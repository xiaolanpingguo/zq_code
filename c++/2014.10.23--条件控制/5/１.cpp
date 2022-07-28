#include<iostream>


void main()
{
	int a;
	std::cin>>a;

	if(a > 0)
	{
		std::cout<<"大于0"<<std::endl;
		if(a > 10)
		{
			std::cout<<"大于10"<<std::endl;
		}
	}
	else if(a == -4)
	{
		std::cout<<"等于0"<<std::endl;
	}
	else if(a == -10)
	{
		std::cout<<"小于0"<<std::endl;
	}

	//if(A)
	//{
	//	B;
	//}
	//else if(C)
	//{
	//	D;
	//}
	//.........
	//else if(E)
	//{
	//	F;
	//}
	//G;
	//先判断A，如果A为真，则执行B，然后执行G
	//如果A为假则执行C,当C为真时执行D，然后执行G
	//如果C为假则继续执行下面的else if()中的
	//表达式，一直为假则直接执行G，
	//一旦有真，就只需该else if下属的{}中的内容，
	//然后执行G
	//可能会有一个会执行的到

	system("pause");
}