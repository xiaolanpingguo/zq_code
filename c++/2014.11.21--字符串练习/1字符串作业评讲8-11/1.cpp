#include <iostream>

void main()
{
	//08
	//const int len = 5;
	//int a[len] = {5,2,6,7,1};
	//√∞≈›≈≈–Ú
	//for(int  i = len - 1; i > 0; --i)
	//{
	//	for(int j = 0; j < i; ++j)
	//	{
	//		if(a[j] > a[j + 1])
	//		{
	//			int temp = a[j];
	//			a[j] = a[j + 1];
	//			a[j + 1] = temp;
	//		}
	//	}
	//}
	//—°‘Ò≈≈–Ú
	//for(int i = 0; i < len - 1; ++i)
	//{
	//	int j = i;
	//	for(int k = j + 1; k < len; ++k)
	//	{
	//		if(a[k] < a[j])
	//			j = k;
	//	}
	//	if(j != i)
	//	{
	//		int temp = a[j];
	//		a[j] = a[i];
	//		a[i] = temp;
	//	}
	//}

	//∂‡∏ˆ◊÷∑˚¥Æ≈≈–Ú
	//char s[5][256];
	//for(int i = 0; i < 5; ++i)
	//	std::cin>>s[i];
	//”√√∞≈›≈≈–Úµƒ∑Ω Ω
	//for(int  i = 5 - 1; i > 0; --i)
	//{
	//	for(int j = 0 ; j < i; ++j)
	//	{
	//		int k = 0;
	//		int bz = 0;
	//		while(s[j][k]||s[j + 1][k])
	//		{
	//			if(s[j][k] > s[j + 1][k])
	//			{
	//				bz = 1;
	//				break;
	//			}
	//			else if(s[j][k] < s[j + 1][k])
	//			{
	//				bz = -1;
	//				break;
	//			}
	//			else
	//			{
	//				++k;
	//			}
	//		}
	//		if(1 == bz)
	//		{
	//			//for(int k = 0; k < 256; ++k)
	//			//{
	//			//	char c = s[j][k];
	//			//	s[j][k] = s[j + 1][k];
	//			//	s[j + 1][k] = c;
	//			//}
	//			char c[256];
	//			for(int k = 0; c[k] = s[j][k];++k);
	//			for(int k = 0; s[j][k] = s[j + 1][k];++k);
	//			for(int k = 0; s[j + 1][k] = c[k];++k);
	//		}
	//	}
	//}

	//”√—°‘Ò≈≈–Úµƒ∑Ω Ω
	//for(int i = 0; i < 5 - 1; ++i)
	//{
	//	int j = i;
	//	for(int k = j + 1; k < 5; ++k)
	//	{
	//		int k1 = 0;
	//		int bz = 0;
	//		while(s[j][k1]||s[k][k1])
	//		{
	//			if(s[j][k1] > s[k][k1])
	//			{
	//				j = k;
	//				break;
	//			}
	//			if(s[j][k1] < s[k][k1])
	//			{
	//				break;
	//			}
	//			else
	//			{
	//				++k1;
	//			}
	//		}
	//	}
	//	if(j != i)
	//	{
	//		char c[256];
	//		for(int k = 0; c[k] = s[j][k];++k);
	//		for(int k = 0; s[j][k] = s[i][k];++k);
	//		for(int k = 0; s[i][k] = c[k];++k);
	//	}
	//}
	//std::cout<<std::endl;
	//for(int i = 0; i < 5; ++i)
	//	std::cout<<s[i]<<std::endl;
	

	//9
	//char s1[256],s2[256],s3[256];
	//std::cin>>s1>>s2;
	//int i1 = 0,i2 = 0,i3 = 0;
	//while(s1[i1] || s2[i2])
	//{
	//	if(s1[i1])
	//		s3[i3++] = s1[i1++];
	//	if(s2[i2])
	//		s3[i3++] = s2[i2++];
	//}
	//s3[i3] = 0;
	//std::cout<<s3<<std::endl;

	//10 - 1
	//char s1[256],s2[256],s3[256],s4[256],s5[256];
	//int num = 0;
	//while(1)
	//{
	//	system("cls");
	//	switch(num)
	//	{
	//	case 0:
	//		{
	//			std::cout<<"«Î ‰»Î◊÷∑˚¥Æ";
	//			std::cin>>s1;
	//			num++;
	//		}
	//		break;
	//	case 1:
	//		{
	//			std::cout<<s1<<std::endl;
	//			std::cout<<"«Î ‰»Î◊÷∑˚¥Æ";
	//			std::cin>>s2;
	//			num++;
	//		}
	//		break;
	//	case 2:
	//		{
	//			std::cout<<s1<<std::endl;
	//			std::cout<<s2<<std::endl;
	//			std::cout<<"«Î ‰»Î◊÷∑˚¥Æ";
	//			std::cin>>s3;
	//			num++;
	//		}
	//		break;
	//	case 3:
	//		{
	//			std::cout<<s1<<std::endl;
	//			std::cout<<s2<<std::endl;
	//			std::cout<<s3<<std::endl;
	//			std::cout<<"«Î ‰»Î◊÷∑˚¥Æ";
	//			std::cin>>s4;
	//			num++;
	//		}
	//		break;
	//	case 4:
	//		{
	//			std::cout<<s1<<std::endl;
	//			std::cout<<s2<<std::endl;
	//			std::cout<<s3<<std::endl;
	//			std::cout<<s4<<std::endl;
	//			std::cout<<"«Î ‰»Î◊÷∑˚¥Æ";
	//			std::cin>>s5;
	//			num++;
	//		}
	//		break;
	//	case 5:
	//		{
	//			std::cout<<s1<<std::endl;
	//			std::cout<<s2<<std::endl;
	//			std::cout<<s3<<std::endl;
	//			std::cout<<s4<<std::endl;
	//			std::cout<<s5<<std::endl;
	//			std::cout<<"«Î ‰»Î◊÷∑˚¥Æ";
	//			for(int i = 0; s1[i] = s2[i];++i)
	//				;
	//			for(int i = 0; s2[i] = s3[i];++i)
	//				;
	//			for(int i = 0; s3[i] = s4[i];++i)
	//				;
	//			for(int i = 0; s4[i] = s5[i];++i)
	//				;
	//			std::cin>>s5;
	//		}
	//		break;
	//	}
	//}

	//10 - 2
	//char s[5][256];
	//int num = 0;
	//while(1)
	//{
	//	system("cls");
	//	for(int i = 0; i < num; ++i)
	//		std::cout<<s[i]<<std::endl;

	//	std::cout<<"«Î ‰»Î◊÷∑˚¥Æ:";

	//	if(num < 5)
	//		std::cin>>s[num++];
	//	else
	//	{
	//		for(int  i = 0; i < 4;++i)
	//		{
	//			for(int j = 0; s[i][j] = s[i + 1][j];++j);
	//		}
	//		std::cin>>s[4];
	//	}
	//}

	//11
	char s1[256],s2[256],s3[256],s4[256];
	std::cin>>s1>>s2>>s3;
	int i1,i2,i3,i4 = 0;
	
	for(i1 = 0; s1[i1];++i1)
		;
	for(i2 = 0; s2[i2];++i2)
		;
	for(i3 = 0; s3[i3];++i3)
		;
	int num = i1 - i2 + 1;
	for(int i = 0 ; i < i1;++i)
	{
		bool bz = true;
		for(int j = 0; j < i2; ++j)
		{
			if(s1[i + j] != s2[j])
			{
				bz = false;
				break;
			}
		}
		if(bz)
		{
			for(int  j = 0; j < i3; ++j)
			{
				s4[i4++] = s3[j];
			}
			i += i2 - 1;
		}
		else
			s4[i4++] = s1[i];
	}

	s4[i4] = 0;
	std::cout<<s4<<std::endl;
	system("pause");
}