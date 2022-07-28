#include<iostream>

void main()
{
	//8
	//int a,b[32],c;
	//bool d;
	//do
	//{
	//	std::cin>>a;
	//	c = 0;
	//	d = false;
	//	while(a)
	//	{
	//		b[c]=a % 10;
	//		a /= 10;
	//		c++;
	//	}
	//	for(int i = 0; i < c; ++i)
	//	{
	//		if(b[i] > 1)
	//		{
	//			d = true;
	//			break;
	//		}
	//	}
	//}while(d);

	//int e = 1;
	//int f = 0;
	//for(int i = 0; i < c; ++i)
	//{
	//	f += b[i] * e;
	//	e *= 2;
	//}

	//std::cout<<f<<std::endl;

	//9
	int a[10];
	for(int i = 0; i < 10; ++i)
	{
		std::cin>>a[i];
	}
	const int len = 10;
	//√∞≈›≈≈–Ú1
	//int temp;
	//int cis = 0;
	//for(int i = len - 1; i > 0; --i)
	//{
	//	for(int j = 0; j < i; ++j)
	//	{
	//		if(a[j] > a[j + 1])
	//		{
	//			temp = a[j];
	//			a[j] = a[j + 1];
	//			a[j + 1] = temp;
	//			cis++;
	//		}
	//	}
	//}
	
	//√∞≈›≈≈–Ú2
	//int temp;
	//for(int i = 0 ; i < len; ++i)
	//{
	//	for(int j = 0 ; j < len - i - 1; ++j)
	//	{
	//		if(a[j] > a[j + 1])
	//		{
	//			temp = a[j];
	//			a[j] = a[j + 1];
	//			a[j + 1] = temp;
	//			cis++;
	//		}
	//	}
	//}

	//—°‘Ò≈≈–Ú
	int temp;
	for(int  i = 0; i  < len - 1; ++i)
	{
		int j = i;
		for(int k = j + 1; k < len; ++k)
		{
			if(a[k] < a[j])
				j = k;
		}
		if(j != i)
		{
			temp = a[j];
			a[j] = a[i];
			a[i] = temp;
		}
	}
	//10




	system("pause");
}