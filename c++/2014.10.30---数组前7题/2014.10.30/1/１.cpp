#include<iostream>

void main()
{
	//2
	//int a[5];
	//int b[5];
	//std::cout<<"输入第一个数组的元素值"<<std::endl;
	//for(int i = 0; i < 5; ++i)
	//{
	//	std::cout<<"请输入第"<<i<<"个元素：";
	//	std::cin>>a[i];
	//}
	//std::cout<<"输入第二个数组的元素值"<<std::endl;
	//for(int i = 0; i < 5; ++i)
	//{
	//	std::cout<<"请输入第"<<i<<"个元素：";
	//	std::cin>>b[i];
	//}
	//int temp;
	//for(int i = 0; i < 5; ++i)
	//{
	//	temp = a[i];
	//	a[i] = b[i];
	//	b[i] = temp;
	//}
	//for(int i = 0; i < 5; ++i)
	//{
	//	std::cout<<a[i]<<" ";
	//}
	//std::cout<<std::endl;
	//for(int i = 0; i < 5; ++i)
	//{
	//	std::cout<<b[i]<<" ";
	//}
	//std::cout<<std::endl;

	//3
	//char a[10];
	//for(int i = 0; i < 10; ++i)
	//{
	//	std::cout<<"请输入第"<<i<<"个元素：";
	//	std::cin>>a[i];
	//}
	//int shuzhiNum = 0;
	//int zimuNum = 0;
	//for(int i = 0; i < 10; ++i)
	//{
	//	if((a[i] >= 'A' && a[i] <= 'Z')||(a[i] >= 'a' && a[i] <= 'z'))
	//		zimuNum++;
	//	else if(a[i] >= '0' && a[i] <= '9')
	//		shuzhiNum++;
	//}
	//std::cout<<"字母有"<<zimuNum<<"个   数字有"<<shuzhiNum<<"个"<<std::endl;

	//4
	//int a[10];
	//for(int i = 0; i < 10; ++i)
	//{
	//	std::cout<<"请输入第"<<i<<"个元素：";
	//	std::cin>>a[i];
	//}
	//int max = a[0];
	//int min = a[0];
	//for(int i = 0; i < 10; ++i)
	//{
	//	if(max < a[i])
	//		max = a[i];
	//	if(min > a[i])
	//		min = a[i];
	//}
	//std::cout<<"大 "<<max<<" 小"<<min<<std::endl;
	

	//5
	//int a[10];
	//for(int i = 0; i < 10; ++i)
	//{
	//	std::cout<<"请输入第"<<i<<"个元素：";
	//	std::cin>>a[i];
	//}
	////int temp;
	////for(int i = 0; i < 10; ++i)
	////{
	////	temp = a[i];
	////	a[i] = a[9 - i];
	////	a[9 - i] = temp;
	////}

	//int b[10];
	//for(int i = 0; i < 10; ++i)
	//{
	//	b[i] = a[9 - i];
	//}
	//for(int i = 0; i < 10; ++i)
	//{
	//	a[i] = b[i];
	//}
	
	//6
	//int a[10];
	//for(int i = 0; i < 10; ++i)
	//{
	//	std::cout<<"请输入第"<<i<<"个元素：";
	//	std::cin>>a[i];
	//}

	////for(int i = 0; i < 10; ++i)
	////{
	////	int temp = a[i];
	////	bool shi = true;
	////	while(temp > 1)
	////	{
	////		if(temp % 2 == 1)
	////		{
	////			shi = false;
	////			break;
	////		}
	////		temp /= 2;
	////	}
	////	if(shi)
	////	{
	////		std::cout<<a[i]<<std::endl;
	////	}
	////}

	//for(int i = 0 ; i < 10; ++i)
	//{
	//	if(((a[i] - 1) & a[i]) == 0)
	//		std::cout<<a[i]<<std::endl;
	//}

	//7

	int a;
	int temp;
	int c;
	int d[32];
	do
	{
		std::cin>>a;
	}while(a < 1);

	//二进制
	temp = a;
	c = 0;
	while(temp)
	{
		d[c] = temp % 2;
		temp /= 2;
		c++;
	}
	for(int i = c - 1; i >= 0; --i)
		std::cout<<d[i];
	std::cout<<std::endl;

	//八进制
	temp = a;
	c = 0;
	while(temp)
	{
		d[c] = temp % 8;
		temp /= 8;
		c++;
	}
	for(int i = c - 1; i >= 0; --i)
		std::cout<<d[i];
	std::cout<<std::endl;

	//十六进制
	temp = a;
	c = 0;
	while(temp)
	{
		d[c] = temp % 16;
		temp /= 16;
		c++;
	}
	for(int i = c - 1; i >= 0; --i)
	{
		if(d[i] < 10)
			std::cout<<d[i];
		else
		{
			std::cout<<(char)((d[i] - 10) + 'A');
		}
	}

	std::cout<<std::endl;

	system("pause");
}