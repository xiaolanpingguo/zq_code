#include<iostream>

//宏
//#define 替换文本的作用
//01)带替换文本的宏
//02)带替换文本的带参宏
//03)不带替换文本的宏

//在C ,C++语音中，有一种宏命令的存在，它们以#开头
//#include也是宏命令，其作用是包含头文件
//01)带替换文本的宏
//此处设置了一个宏XYZ，其替换文本为100
//在之后的代码中，只要出现了XYZ都会被替换为100
#define XYZ 100

//此处设置了一个宏ABC，其替换文本为XYZ + XYZ
//在之后的代码中，只要出现了ABC都会被替换为XYZ + XYZ
#define ABC  XYZ + XYZ

//此处设置了一个宏ZanTing，其替换文本为system("pause")
//在之后的代码中，只要出现了ZanTing都会被替换为system("pause")
#define ZanTing system("pause")

//03)不带替换文本的宏
//此处设置了一个宏DEF，其没有替换文本
//在之后的代码中，出现了DEF就相当于什么都没有
#define DEF 

//02)带替换文本的带参宏
//此处设置了一个带参宏，只要出现了ADD(?,!)的地方都会被
//替换为？+ !
#define ADD(a,b)  a + b

//此处设置了一个带参宏，只要出现了BOOLL(?,!)的地方都会被
//替换为？== !
#define BOOLL(a,b) a == b

#define MAP_W 20
#define MAP_H 20
#define MAP   MAP_W * MAP_H

#define _KD 0 
#define _SD 1
#define _BJ 3
#define _Hero 2


void main()
{
	//int a = 200;
	//a = 200;
	//a = 200;
	//a = 200;
	//a = 200;
	//a = 200;
	int a = XYZ;
	a = ABC;
	std::cout<<a<<std::endl;
	//system("pause");
	ZanTing;

	DEF;

	int b = 15;

	int c = ADD(a,b);

	std::cout<<c<<std::endl;
	ZanTing;

	c = BOOLL(a,b);

	std::cout<<c<<std::endl;

	ZanTing;

	int map[MAP];
}