#include<iostream>

//break continue return goto

void main()
{
	for(int i = 0; i < 10 ; ++i)
	{
		if(i == 4)
			continue;
		//一旦运行到continue，则本次循环结束,
		//下面的打印将不被执行，然后执行
		//++i,然后进入下次循环
		//只是针对直接包含它的循环
		for(int j = 0; j < 10; ++j)
		{
			if(j == 5)
				break;
			//一旦运行到break则跳出循环，后面的循环将都不执行
			//只针对直接包含它的循环
			if(j == 3)
				return;
			//一旦运行到return，则该函数下面所有的都不被执行，
			//直接退出函数。
			//针对的是直接包含它的函数
			std::cout<<j;
		}
		std::cout<<std::endl;
		//std::cout<<i<<std::endl;
	}
	system("pause");
}