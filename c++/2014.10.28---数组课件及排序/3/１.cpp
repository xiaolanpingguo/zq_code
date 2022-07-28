#include<iostream>

void main()
{
	//冒泡排序
	int a[5];
	for(int i = 0; i < 5; ++i)
	{
		std::cin>>a[i];
	}
	int temp = 0;
	//for(int i = 0; i < 5; ++i)
	//{
	//	temp += a[i];
	//}
	//std::cout<<temp<<std::endl;
	int len = 5;
	for(int i = len - 1; i > 0; --i)
	{
		for(int j = 0; j < i; ++j)
		{
			if(a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}

	for(int i = 0; i < len; ++i)
	{
		std::cout<<a[i]<<std::endl;
	}

	int b[5];
	for(int i = 0; i < len; ++i)
	{
		b[i] = a[len - i - 1];
	}
	
	std::cout<<"b数组"<<std::endl;

	for(int i = 0; i < len; ++i)
	{
		std::cout<<b[i]<<std::endl;
	}

	for(int i = 0; i < len - 1; ++i)
	{
		int j = i;
		for(int k = j + 1; k < len; ++k)
		{
			if(b[k] < b[j])
			{
				j = k;
			}
		}
		if( j != i)
		{
			temp = b[j];
			b[j] = b[i];
			b[i] = temp;
		}

	}

	std::cout<<"b数组   :   "<<std::endl;
	for(int i = 0; i < len; ++i)
	{
		std::cout<<b[i]<<std::endl;
	}

	system("pause");
}