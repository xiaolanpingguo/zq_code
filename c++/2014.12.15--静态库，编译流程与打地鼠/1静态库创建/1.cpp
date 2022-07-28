//静态库工程不是生成exe文件，而是生成
//lib库文件,库文件中就是工程中各个cpp
//文件中的各个函数，全局变量的定义

#include<iostream>

int x;
void y()
{
	std::cout<<x<<std::endl;
}