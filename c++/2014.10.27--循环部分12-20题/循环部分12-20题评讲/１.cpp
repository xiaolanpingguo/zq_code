#include<iostream>

void main()
{
	//12
	//int a;
	//do
	//{
	//	std::cout<<"请输入一个正整数:";
	//	std::cin>>a;
	//}while(a < 1);
	//
	//for(int i = 0; i < a; ++i)
	//{
	//	for(int j = 0; j < a; ++j)
	//	{
	//		if(i == j || i + j == a - 1)
	//		{
	//			std::cout<<"■";
	//		}
	//		else
	//		{
	//			std::cout<<"  ";
	//		}
	//	}
	//	std::cout<<std::endl;
	//}

	//13
	//int a;
	//int b;
	//do
	//{
	//	std::cout<<"请输入一个正整数:";
	//	std::cin>>a;
	//}while(a < 1);

	//do
	//{
	//	std::cout<<"请输入一个正整数（2-"<<a<<"):";
	//	std::cin>>b;
	//}while(b < 2 || b > a);

	//for(int i = 1; i <= a; ++i)
	//{
	//	std::cout<<i<<" ";
	//	if(i % b == 0)
	//		std::cout<<std::endl;
	//}

	//14
	//int a;
	//int b;
	//do
	//{
	//	std::cout<<"请输入第一个数;";
	//	std::cin>>a;
	//	std::cout<<"请输入第二个数，必须与第一个不相等:";
	//	std::cin>>b;
	//}while(a == b);
	//
	//if(a > b)
	//{
	//	int c = a;
	//	a = b;
	//	b = c;
	//}
	//int num = b - a + 1;
	//for(int i = 0; i < num / 2; ++i)
	//{
	//	std::cout<<	a + i << " " << b - i<<" ";
	//	if(a + i == b - i)
	//		std::cout<<a + i<<std::endl;
	//	if(num % 2 == i)
	//		std::cout<<a + num/2<<std::endl;
	//}

	//15
	//int a;
	//int b;
	//do
	//{
	//	std::cout<<"请输入第一个数;";
	//	std::cin>>a;
	//	std::cout<<"请输入第二个数，必须与第一个不相等:";
	//	std::cin>>b;
	//}while(a == b || a < 1 || b < 1);
	//
	//if(a > b)
	//{
	//	int c = a;
	//	a = b;
	//	b = c;
	//}

	//int num;
	//for(int i = a; i <= b; ++i)
	//{
	//	num = 0;
	//	for(int j = 1; j < i; ++j)
	//	{
	//		if(i % j == 0)
	//			num += j;
	//	}
	//	if(num == i)
	//		std::cout<<i<<" ";
	//}
	
	//16
	//int a;
	//int b;
	//do
	//{
	//	std::cout<<"请输入第一个数;";
	//	std::cin>>a;
	//	std::cout<<"请输入第二个数，必须与第一个不相等:";
	//	std::cin>>b;
	//}while(a == b || a < 1 || b < 1);
	//
	//if(a > b)
	//{
	//	int c = a;
	//	a = b;
	//	b = c;
	//}
	//	
	//int num = b - a + 1;
	//int hang = num / 10;
	//for(int i = 0; i < hang; ++i)
	//{
	//	int min = a + i * 10;
	//	if(i % 2 == 0)
	//	{
	//	//从左到右
	//		for(int j = min; j < min + 10; ++j)
	//			std::cout<<j<<" ";
	//	}
	//	else//从右到左 
	//	{
	//		for(int j = min + 9; j >= min; --j)
	//		{
	//			std::cout<<j<<" ";
	//		}
	//	}
	//	std::cout<<std::endl;
	//}
	//if(num % 10 != 0)
	//{
	//	int min = b - num % 10 + 1;
	//	int max = b;
	//	if(hang % 2 == 0)
	//	{
	//		for(int j = min; j <= max; ++j)
	//			std::cout<<j<<" ";
	//	}
	//	else
	//	{
	//		for(int j = 0; j < 10 - (max - min + 1);++j)
	//			std::cout<<" ";
	//		for(int j = max ;j >= min; --j)
	//			std::cout<<j<<" ";
	//	}
	//}
	//std::cout<<std::endl;

	//17
	//int a;
	//do
	//{
	//	std::cout<<"请输入一个正整数:";
	//	std::cin>>a;
	//}while(a < 1);

	//int b = 1;//当前行最后的那个数
	//int c = 1;//当前行数
	////int k = 1;
	//for(int i = 1; i <= a; ++i)
	//{
	//	std::cout<<i<<" ";
	//	if(i == b)
	//	{
	//		c += 1;
	//		b += c;
	//		std::cout<<std::endl;
	//	}
	//	
	//	//for(int j = 1; j <= i; ++j)
	//	//{
	//	//	std::cout<<k<<" ";
	//	//	k++;
	//	//	if(k > a)
	//	//		break;
	//	//}
	//	//std::cout<<std::endl;
	//	//if(k > a)
	//	//	break;
	//}

	//18 
	//int a;
	//do
	//{
	//	std::cout<<"请输入一个正整数:";
	//	std::cin>>a;
	//}while(a < 1);
	//
	//if(a == 1)
	//	std::cout<<"0"<<std::endl;
	//else if(a == 2)
	//	std::cout<<"0 1"<<std::endl;
	//else
	//{
	//	std::cout<<"0 1 ";
	//	int x = 0;
	//	int y = 1;
	//	for(int i = 0; i < a - 2; ++i)
	//	{
	//		std::cout<<x + y<<" ";
	//		int z = x;
	//		x = y;
	//		y = z + y;
	//	}
	//}

	//19
	//int a;
	//do
	//{
	//	std::cout<<"请输入一个0到255的整数：";
	//	std::cin>>a;
	//}while(a < 0 || a > 255);

	//int num1 = 0;
	//for(int i = 0; i < 8; ++i)
	//{
	//	//if(a % 2 == 1)
	//	//{
	//	//	num1++;
	//	//	a /= 2;
	//	//}
	//	if((a>>i)&1)
	//		num1++;
	//}
	//std::cout<<"1的数量为"<<num1<<"   0的数量"<<8 - num1<<std::endl;

	//20
	//int year;
	//int month;
	//int day;
	//do
	//{
	//	std::cout<<"请输入年(2005 - 2014)：";
	//	std::cin>>year;
	//}while(year < 2005 || year > 2014);

	//do
	//{
	//	std::cout<<"请输入月(1-12):";
	//	std::cin>>month;
	//}while(month < 1 || month > 12);

	//int max_day = 31;
	//if(month == 4 || month == 6 || month == 9 || month == 11)
	//	max_day = 30;
	//else if(month == 2)
	//{
	//	if(year == 2008 || year == 2012)
	//		max_day = 29;
	//	else
	//		max_day = 28;
	//}

	//do
	//{
	//	std::cout<<"请输入日(1-"<<max_day<<"):";
	//	std::cin>>day;
	//}while(day < 1 ||day > max_day);

	////总天数
	//int num_day = 0;
	////得到所有的天数
	//for(int i = 2005; i < year;++i)
	//{
	//	if(i == 2008 || i == 2012)
	//		num_day += 366;
	//	else
	//		num_day += 365;
	//}
	//switch(month)
	//{
	//case 12:num_day += 30;
	//case 11:num_day += 31;
	//case 10:num_day += 30;
	//case 9:num_day += 31;
	//case 8:num_day += 31;
	//case 7:num_day += 30;
 //   case 6:num_day += 31;
	//case 5:num_day += 30;
	//case 4:num_day += 31;
	//case 3:
	//	{
	//		if(year == 2008 || year == 2012)
	//			num_day += 29;
	//		else
	//			num_day += 28;
	//	}
	//case 2:num_day += 31;
	//case 1:
	//}

	//num_day += day;

	//num_day -= 1;

	//////2005年1月1日是星期六
	////int xq = (num_day + 6) % 7;

	////if(xq)
	////	std::cout<<"周"<<xq<<std::endl;
	////else
	////	std::cout<<"周日"<<std::endl;

	//int xq = num_day % 7;
	//switch(xq)
	//{
	//case 0:
	//	{
	//		std::cout<<"周六"<<std::endl;
	//	}
	//	break;
	//case 1:
	//	{
	//		std::cout<<"周日"<<std::endl;
	//	}
	//	break;
	//case 2:
	//	{
	//		std::cout<<"周一"<<std::endl;
	//	}
	//	break;
	//case 3:
	//	{
	//		std::cout<<"周二"<<std::endl;
	//	}
	//	break;
	//case 4:
	//	{
	//		std::cout<<"周三"<<std::endl;
	//	}
	//	break;
	//case 5:
	//	{
	//		std::cout<<"周四"<<std::endl;
	//	}
	//	break;
	//case 6:
	//	{
	//		std::cout<<"周五"<<std::endl;
	//	}
	//	break;
	//}
	
	system("pause");
}