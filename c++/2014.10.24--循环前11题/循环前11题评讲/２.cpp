#include <iostream>


void main()
{
	//1
	//int a;
	//int b;
	//int c;
	//std::cin>>a;
	//std::cin>>b;
	//std::cin>>c;
	//int max = a;
	//if(max < b)
	//	max = b;
	//if(max < c)
	//	max = c;
	//std::cout<<max<<std::endl;

	//2
	//int a;
	//int b;
	//std::cin>>a;
	//int i = 0;
	//do
	//{
	//	std::cin>>b;
	//	if(a == b)
	//	{
	//		std::cout<<"等"<<std::endl;
	//		break;
	//	}
	//	else
	//	{
	//		if(a > b)
	//		{
	//			std::cout<<"a > b"<<std::endl;
	//		}
	//		else
	//		{
	//			std::cout<<"a < b"<<std::endl;
	//		}
	//	}
	//	++i;
	//}while(i < 3);

	//3

	//int i_PlayerOne;
	//int i_PlayerTwo;

	//do
	//{
	//	std::cout<<"玩家1：";
	//	std::cin>>i_PlayerOne;
	//}while(i_PlayerOne < 1 || i_PlayerOne > 3);

	//do
	//{
	//	std::cout<<"玩家2：";
	//	std::cin>>i_PlayerTwo;
	//}while(i_PlayerTwo < 1 || i_PlayerTwo > 3);

	//std::cout<<"玩家1";
	//switch(i_PlayerOne)
	//{
	//case 1:std::cout<<"石头";break;
	//case 2:std::cout<<"剪子";break;
	//case 3:std::cout<<"布";break;
	//}
	//std::cout<<"玩家2";
	//switch(i_PlayerTwo)
	//{
	//case 1:std::cout<<"石头";break;
	//case 2:std::cout<<"剪子";break;
	//case 3:std::cout<<"布";break;
	//}

	//if(i_PlayerOne == i_PlayerTwo)
	//	std::cout<<"平"<<std::endl;
	//else if((1 == i_PlayerOne && 2 == i_PlayerTwo)
	//	||(2 == i_PlayerOne && 3 == i_PlayerTwo)
	//	||(3 == i_PlayerOne && 1 == i_PlayerTwo))
	//	std::cout<<"玩家1胜利!"<<std::endl;
	//else
	//	std::cout<<"玩家2胜利!"<<std::endl;

	//4
	//int x1;
	//int y1;
	//int x2;
	//int y2;
	//int x3;
	//int y3;
	//std::cin>>x1;
	//std::cin>>y1;
	//std::cin>>x2;
	//std::cin>>y2;
	//std::cin>>x3;
	//std::cin>>y3;
	//y = kx + b;
	//2 = k * 1 + b
	//4 = k * 3 + b
	//6 = k * 4 + b
	//y1 - y2 = k * (x1 - x2)
	//k = (y1 - y2) / (x1 - x2)
	//y1 = ((y1 - y2) / (x1 - x2)) * x1 + b
	//b = y1 - ((y1 - y2) / (x1 - x2)) * x1
	//x3 * k + b == y3
	//
	//int k = (y1 - y2) / (x1 - x2);
	//int b = y1 - ((y1 - y2) / (x1 - x2)) * x1;

	//if(y3 == x3 * k + b)
	//	std::cout<<"不能"<<std::endl;
	//else
	//	std::cout<<"能"<<std::endl;

	//if((y1 - y2) * (x2 -x3) == (y2 - y3) * (x1 - x2))
	//	std::cout<<"不能"<<std::endl;
	//else
	//	std::cout<<"能"<<std::endl;

	//5
	//int a;//
	//int b;//
	//int c;//
	//int d;//
	//int e;//

	//std::cin>>a;
	//std::cin>>b;
	//std::cin>>c;
	//std::cin>>d;
	//std::cin>>e;

	//int temp = a;
	//if(a > b)
	//{
	//	temp = a;
	//	a = b;
	//	b = temp;
	//}
	//if(b > c)
	//{
	//	temp = b;
	//	b = c;
	//	c = temp;
	//}
	//if(c > d)
	//{
	//	temp = c;
	//	c = d;
	//	d = temp;
	//}
	//if(d > e)
	//{
	//	temp = d;
	//	d = e;
	//	e = temp;
	//}
	//if(a > b)
	//{}
	//if(b > c)
	//{}
	//if(c > d)
	//{}
	//if(a > b)
	//{}
	//if(b > c)
	//{}
	//if(a > b)
	//{}

	//6
	//int a,j=1;
	//std::cin>>a;
	//for(int i=a;i>9;)
	//{
	//   i=i/10;
	//   j++;

	//}
	//std::cout<<j;
	
	//7
	//int a;
	//std::cin>>a;
	//int temp = 1;
	//for(int i = 1; i <= a; ++i)
	//{
	//	temp *= i;
	//}

	//8
	//int a;
	//do
	//{
	//	std::cout<<"请输入一个大于0的数:";
	//	std::cin>>a;
	//}while(a <= 0);

	//for(int i = 1; i <= a;++i)
	//{
	//	for(int j = 1; j <= i; ++j)
	//	{
	//		std::cout<<i<<"*"<<j<<"="<<i * j<<" ";
	//	}
	//	std::cout<<std::endl;
	//}

	//9:质数就是只能被1或者本身整除的整数
	//int a;
	//do
	//{
	//	std::cout<<"请输入大于2的整数:";
	//	std::cin>>a;
	//}while(a <= 2);
	//
	//for(int i = 2; i < a / 2; ++i)
	//{
	//	if(a % i == 0)
	//	{
	//		std::cout<<"不是"<<std::endl;
	//		system("pause");
	//		return;
	//	}
	//}
	//std::cout<<"是"<<std::endl;
	
	//10
	//   *		3   a / 2 0    1				
	//  ***		2   a / 2 - 1  1   3     2  3   ( a + 1) / 2
	// *****	1   a / 2 - 2  2   5     3  5    
	//*******	0   3   7      4   7   
	//int a;
	//do
	//{
	//	std::cout<<"请输入一个大于1的正奇数：";
	//	std::cin>>a;
	//}while(a <= 1 || a % 2 == 0);
	//
	//for(int i = 0; i < (a + 1)/2; ++i)
	//{
	//	int star = i * 2 + 1;
	//	int space = a / 2 - i;
	//	for(int j = 0; j < space; ++j)
	//	{
	//		std::cout<<" ";
	//	}
	//	for(int j = 0; j < star; ++j)
	//	{
	//		std::cout<<"*";
	//	}
	//	std::cout<<std::endl;
	//}
	//11
	//   *			(7 - 1)/2			
	//  ***		    (7 - 3)/2
	// *****		(7 - 5)/2
	//*******		(7 - 7)/2
	// *****		(7 - 5)/2 (a - i) * 2 - 1 		
	//  ***			(7 - 3)/2 2 * 2 - 1 
	//   *			(7 - 1)/2 1 * 2 - 1 
	
	int a;
	do
	{
		std::cout<<"请输入一个大于1的正奇数：";
		std::cin>>a;
	}while(a <= 1 || a % 2 == 0);
	
	for(int i = 0; i < a ; ++i)
	{
		int star;
		if( i <= a / 2)
			star = 2 * i + 1;
		else
			star = (a - i) * 2 - 1;
		int space = (a - star) / 2;
		for(int j = 0; j < space; ++j)
			std::cout<<" ";
		for(int j = 0; j < star; ++j)
			std::cout<<"*";
		std::cout<<std::endl;
	}

	system("pause");
}