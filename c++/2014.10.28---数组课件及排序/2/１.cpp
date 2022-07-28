#include<iostream>

void main()
{
	int a[100];

	//char b[200];

	for(int i = 0; i < 100; ++i)
	{
		a[i] = i;
	}

	for(int i = 0; i < 100; ++i)
	{
		if(a[i] % 2 == 0)
			std::cout<<a[i]<<std::endl;
	}

	system("pause");
}