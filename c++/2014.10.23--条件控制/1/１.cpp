#include<iostream>


void main()
{
	std::cout<<"1"<<std::endl;
	{
		std::cout<<"2"<<std::endl;
		std::cout<<"3"<<std::endl;
		{
			std::cout<<"4"<<std::endl;
			std::cout<<"5"<<std::endl;
			{
				
			}
		}
	}
	system("pause");
}

//在概念上。复合语句可以当成一句代码
//只不过这句代码由其他很多单语句一起组成