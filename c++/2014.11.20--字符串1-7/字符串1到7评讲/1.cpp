#include<iostream>

void main()
{
	//02)
	//char s[256];
	//int len;
	//do
	//{
	//	std::cin>>s;
	//	for(len = 0; s[len];++len)
	//		;
	//}while(len % 2 == 0);
	//int mid = len / 2;
	//std::cout<<s[mid];
	//for(int i = 1; i <= mid;++i)
	//{
	//	std::cout<<s[mid - i] <<s[mid + i];
	//}
	//std::cout<<std::endl;

	//03)
	//char s[256];
	//int len;
	//do
	//{
	//	std::cin>>s;
	//	for(len = 0; s[len];++len)
	//		;
	//}while(len <= 3);

	//for(int i = 0; i < 3;++i)
	//{
	//	for(int j = i;j < len ; j += 3)
	//		std::cout<<s[j];
	//	std::cout<<std::endl;
	//}

	//04)
	//unsigned char s[256];
	//std::cin>>s;

	//for(int i = 0; s[i];++i)
	//{
	//	if(s[i] <= 127)
	//		std::cout<<s[i]<<" ";
	//	else
	//	{
	//		std::cout<<s[i]<<s[i + 1]<<" ";
	//		i++;
	//	}
	//}

	//05
	//char s1[256],s2[256];
	//std::cin>>s1>>s2;

	//int i = 0;
	//int bz = 0;

	//while(s1[i]||s2[i])
	//{
	//	if(s1[i] > s2[i])
	//	{
	//		bz = 1;
	//		break;
	//	}
	//	else if(s1[i] < s2[i])
	//	{
	//		bz = -1;
	//		break;
	//	}
	//	else
	//	{
	//		++i;
	//	}
	//}

	//switch(bz)
	//{
	//case 1:std::cout<<"×ó±ß > ÓÒ±ß"<<std::endl;break;
	//case -1:std::cout<<"×ó±ß < ÓÒ±ß"<<std::endl;break;
	//case 0:std::cout<<"×ó±ß = ÓÒ±ß"<<std::endl;break;
	//}

	//06)
	//unsigned char s[256];
	//std::cin>>s;

	//int len;
	//for(len = 0; s[len];++len)
	//	;
	//int mid = len >> 1;//len / 2;
	//bool shi = true;

	//for(int i = 0; i < mid; ++i)
	//{
	//	if(s[i] != s[len - 1 - i])
	//	{
	//		shi = false;
	//		break;
	//	}
	//}


	//07)
	char s1[256],s2[256];
	std::cin>>s1>>s2;
	int len1;
	int len2;
	for(len1 = 0; s1[len1];++len1)
		;
	for(len2 = 0; s2[len2];++len2)
		;

	//Òª±È½ÏµÄ´ÎÊý
	int num = len1 - len2 + 1;
	
	int cxcs = 0;

	for(int i = 0 ; i < num;++i)
	{
		bool cx = true;
		for(int j = 0; j < len2 ;++j)
		{
			if(s1[i + j] != s2[j])
			{
				cx = false;
				break;
			}
		}
		if(cx)
		{
			i += len2 - 1;
			cxcs++;
		}
	}
	
	


	system("pause");
}