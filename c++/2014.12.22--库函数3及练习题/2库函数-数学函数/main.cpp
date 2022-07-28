#include<iostream>
#include <math.h>

//数学函数
//弧度 = 弧长/半径
//360角的弧度2π
//180角的弧度是π
//90角的弧度是π/2

void main()
{
	const float pi = 3.1415926f;
	//01)求正弦
	std::cout<<sin(pi/6.0f)<<std::endl;
	//02)求余弦
	std::cout<<cos(pi/6.0f)<<std::endl;
	//03)开方
	std::cout<<sqrt(9.0f)<<std::endl;
	std::cout<<sqrt(10.0f)<<std::endl;
	std::cout<<sqrt(25.0f)<<std::endl;


	system("pause");
}