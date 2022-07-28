#include<iostream>

void main()
{
	//10
	//int a[5];
	//int b[5];
	//bool feifa = false;
	//do
	//{
	//	for(int i = 0; i < 5; ++i)
	//	{
	//		std::cout<<"请输入第"<<i<<"个元素：";
	//		std::cin>>a[i];
	//	}
	//	for(int i = 0; i < 5; ++i)
	//	{
	//		std::cout<<"请输入第"<<i<<"个元素：";
	//		std::cin>>b[i];
	//	}
	//	for(int i = 0; i < 4; ++i)
	//	{
	//		if(a[i] > a[i + 1]||b[i] > b[i + 1])
	//		{
	//			feifa = true;
	//			break;
	//		}
	//	}
	//}while(feifa);
	//int d[10];

	//int ai = 0;
	//int bi = 0;
	//int di = 0;

	//while(ai < 5 && bi < 5)
	//{
	//	if(a[ai] < b[bi])
	//	{
	//		d[di++] = a[ai++];
	//	}
	//	else
	//	{
	//		d[di++] = b[bi++];
	//	}
	//}
	//for(;ai < 5; ++ai)
	//	d[di++] = a[ai];
	//for(;bi < 5; ++bi)
	//	d[di++] = b[bi];

	//11
	//int a[100];
	//for(int i = 0; i < 100; ++i)
	//	a[i] = -1;
	//int b;
	//do
	//{
	//	std::cin>>b;
	//}while(b < 0 || b > 99);
	//int num = b + 1;

	//for(int i = 0; i < num; ++i)
	//{
	//	//当前斜方向的起始坐标
	//	int x,y;
	//	if(i < 10)
	//	{
	//		x = 0;
	//		y = i;
	//	}
	//	else
	//	{
	//		x = i - 9;
	//		y = 9;
	//	}

	//	for(; x >= 0 && x < 10 && y >= 0 && y < 10;x++,y--)
	//	{
	//		a[x + y * 10] = b--;
	//		
	//		system("cls");
	//		for(int j = 0; j < 100; ++j)
	//		{
	//			if(a[j] > -1)
	//			{
	//				if(a[j] < 10)
	//					std::cout<<"0";
	//				std::cout<<a[j]<<" ";
	//			}
	//			else
	//				std::cout<<"■  ";
	//			if( j % 10 == 9)
	//				std::cout<<std::endl;
	//		}

	//		if(-1 == b)
	//		{
	//			i = num;
	//			break;
	//		}
	//	}
	//}

	//12
	//int a;
	//int b;
	//do
	//{
	//	std::cout<<"请输入第一个数:";
	//	std::cin>>a;
	//}while(a < 0 || a > 99);

	//do
	//{
	//	std::cout<<"请输入第二个数:";
	//	std::cin>>b;
	//}while(b < 0 || b > 99 || b == a);

	//if(a > b)
	//{
	//	int temp = a;
	//	a = b;
	//	b = temp;
	//}
	//int c[121];
	//for(int i = 0; i < 121; ++i)
	//	c[i] = -1;
	////中间起始坐标
	//int x = 5;
	//int y = 5;
	//int quan = 1;//最开始的第一圈，用来记录圈数
	//int yjdysz = 0;//已经打印的数字的个数
	//int gs = 1;//当前圈打印的数字的总个数
	//int dir = 0;//方向,用0123表示下左上右的变化

	//while(1)
	//{
	//	c[x + y * 11] = a++;
	//	yjdysz ++;
	//	system("cls");
	//	for(int  i = 0 ; i < 121; ++i)
	//	{
	//		if(c[i] == -1)
	//		{
	//			std::cout<<"■ ";
	//		}
	//		else
	//		{	
	//			if(c[i] < 10)
	//				std::cout<<"0";
	//			std::cout<<c[i]<<" ";
	//		}
	//		if(i % 11 == 10)
	//			std::cout<<std::endl;
	//	}
	//	
	//	if(a > b)
	//		break;
	//		
	//	if(yjdysz == gs)
	//	{
	//		quan++;
	//		yjdysz = 0;
	//		gs = (quan - 1) * 8;//2 * 4
	//		dir = 0;
	//		x++;
	//	}
	//	else
	//	{
	//		if(yjdysz  % (gs / 4) == 0)
	//			dir ++;
	//		switch(dir)
	//		{
	//		case 0:y++;break;
	//		case 1:x--;break;
	//		case 2:y--;break;
	//		case 3:x++;break;
	//		}
	//	}
	//}

	int a[5];
	int b;
	std::cin>>b;
	bool feifa = false;
	do
	{
		for(int i = 0; i < 5; ++i)
		{
			std::cout<<"请输入第"<<i<<"个元素：";
			std::cin>>a[i];
		}
		for(int i = 0; i < 4; ++i)
		{
			if(a[i] > a[i + 1])
			{
				feifa = true;
				break;
			}
		}
	}while(feifa);

	for(int i = 0; i < 5; ++i)
	{
		if(b == a[i])
		{
			std::cout<<"找到了 "<<i<<std::endl;
			system("pause");
			return;
		}
	}
	std::cout<<"没找到"<<std::endl;
	
	system("pause");
}