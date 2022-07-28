#include<iostream>

//局部变量与作用域
//局部变量就是定义在函数内部的变量
//局部变量只能在其作用域中起作用
//一旦出了其作用域，这个变量就相当于
//不存在了

//局部变量的作用域是从其定义语句开始，到直接包含它
//的{}结束

//作用域就是变量起作用的区域

void main()
{
	int i = 0;
	while(1)
	{
		int a;
		if( i == 10)
		{
			int b;
			break;
		}
		//b = 0;b的作用域在if的{}中
		std::cout<<i<<std::endl;
		++i;
		a = i;
	}
	i = 0;
	//a = 0;a的作用域在while循环内,出了循环就不存在了
	system("pause");
}