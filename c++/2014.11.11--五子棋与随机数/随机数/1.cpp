#include <iostream>
#include <time.h>

//随机数：基于一个初始的整数值(随机种子)
//和一套运算规则得到的一个不确定大小的数值

void main()
{
	//模拟随机随机数的产生
	//int sjzz = 200;
	//for(int i = 0; i < 10; ++i)
	//{
	//	sjzz *= 128;
	//	sjzz += 128;
	//	sjzz %= 32767;
	//	int a = sjzz;
	//	std::cout<<a<<std::endl;
	//}
	//如果随机数种子每次都一样，那么每次得到
	//的随机数序列就都是一样的，如果我们可以让我们
	//的随机数的种子每次都不一样，那么我们就可以得到
	//一个不一样的随机数序列
	//time(0)得到是1970.1.1--0.0.0到目前执行这句话所
	//经过的秒数
	srand(time(0));//取随机种子
	//取5---10的随机数
	for(int i = 0; i < 10; ++i)
	{
		int a = rand() % 6 + 5;
		std::cout<<a<<std::endl;
	}
	std::cout<<"  -----------------  "<<std::endl;
	int x = rand() % 20;
	std::cout<<x<<std::endl;
	
	system("pause");
}