#include<iostream>

//*****
//*****
//*****
//*****
//4行5列的矩形


void main()
{
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			std::cout<<"*";
		}
		std::cout<<std::endl;
	}
	
	system("pause");
}