#include<iostream>

//数据类型
//基本数据类型
//复合数据类型
//指针
//引用

//&
//A&&B:逻辑与
//A&B:位与
//&A:取地址，A必须是变量，&A的到的地址和A的类型相同
//定义引用  类型& 引用名 = 变量;
void main()
{

	int a = 1;

	int& b = a;

	b = 2;

	std::cout<<a<<std::endl;

	int& c = b;

	c = 0;//00 00 00 00

	//short& d = (short)a;//(short)a的结果不是一个变量
		
	short& d = *((short*)((char*)&a + 1));

	d = 1;//00 01 00 00
	std::cout<<a<<std::endl;

	bool& e = ((bool*)&a)[3];

	e = true;//00 01 00 01
	std::cout<<a<<std::endl;//16777472
	//引用实际就是为变量取了一个别名

	//bool& f;// error C2530: “f”: 必须初始化引用
	//01)引用是c++中特有的，c中没有
	//02)引用就是一个变量的别名
	//03)引用必须初始化，一旦初始化则该引用
	//就是初始化他的那个变量的别名
	//04)引用的底层运作机制还是指针
	//05)Java的引用其实就是C++的指针
	system("pause");
}
