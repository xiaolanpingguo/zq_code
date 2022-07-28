#include<iostream>

void f1()
{
	std::cout<<"abc"<<std::endl;
}

void f2()
{
	f1();
	std::cout<<"def"<<std::endl;
}

void f3()
{
	f2();
	std::cout<<"ghi"<<std::endl;
}


void main()
{
	f3();
	system("pause");
}

//断点+启动调试
//逐过程单步F10
//逐语句单步F11:跳入到调用的函数中
//shift+f11跳出调用的函数

//function ：函数
//pointer:指针
//referance:引用
//void:空，无