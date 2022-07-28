#include<iostream>
#include<time.h>


void main()
{
	//获取1970.1.1-0.0.0到现在执行到time(0)这句话
	//的时候的总秒数
	srand(time(0));
	//取0到n-1的随机数则要rand()%n
	//取7到12的随机数
	//注意：随机数是从0开始到n-1，若要取0之后X
	//到Y的随机数，则在后面加上X，那么就能取到
	//X到Y之间的随机数，Y指取值的范围的最后一个数
	for(int i = 0; i < 10; ++i)
	{
		int a = rand() % 8 + 6;
		std::cout<<a<<std::endl;
	}

	system("pause");
}