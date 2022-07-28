#include<iostream>

//do-while
//while
//for

void main()
{
	std::cout<<"开始了"<<std::endl;

	int a;
	std::cout<<"请输入一个大于0的数:";
	std::cin>>a;
	int i;
	//while(a <= 0 && i < 3)
	//{
	//	std::cout<<"请输入一个大于0的数:";
	//	std::cin>>a;
	//	++i;
	//}

	
	//for(A;B;C)
	//{
	//	D;
	//}
	//G;
	//01)先执行Ａ
	//02)判断B
	//03)如果B为真则执行D
	//04)执行C 然后重复02)到04)过程
	//05)如果B为假，则跳出循环执行G。

	for(i = 0; i < 3; ++i)
	{
		if(a <= 0)
		{
			std::cout<<"请输入一个大于0的数:";
			std::cin>>a;
		}
	}

	std::cout<<"出来了"<<std::endl;


	//70%都是用这种写法
	for(int j = 0; j < 10; ++j)
	{
		
	}

	//for(;;)
	//{
	//	
	//}

	//for(;B;C)
	//{}

	//for(;B;)
	//{}

	//A，B，C不一定写完的情况下
	//对跳出条件的控制

	system("pause");
}