#include<iostream>

//do-while
//while
//for

void main()
{
	//while(A)
	//{
	//	B;
	//}
	//G;
	//01)执行A，判断A的真假。
	//02)当A为真，执行B，然后重复01)-02)过程
	//03)当A为假，则执行G

	//do-while要比while多执行一次

	std::cout<<"开始了"<<std::endl;

	int a;
	std::cout<<"请输入一个大于0的数:";
	std::cin>>a;
	while(a <= 0)
	{
		std::cout<<"请输入一个大于0的数:";
		std::cin>>a;
	}

	std::cout<<"出来了"<<std::endl;

	//while(1)
	//{
	//	
	//}

	system("pause");
}