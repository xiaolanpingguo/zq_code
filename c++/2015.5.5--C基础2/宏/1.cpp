#include <stdio.h>
#include <windows.h>
#include <iostream>

//#include：有<>和""两种
//#define：定义宏
//#undef：取消宏
//#ifdef、#ifndef、#endif、#else、#if、#elif：条件编译
//#error：编译报错
//#：字符串生成
//#@：字符生成
//##：文本连接

#if WINVER < 0x0501
#error 本工程支持Windows最低版本号为0x0501
#endif

#define _A1(s) #s
#define _A2(s) #@s
#define _A3(s,t) s##t

void main()
{
	char* p = _A1(123abc你好);
	//char* p = "123abc你好";
	
	char q = _A2(X);
	//char q = 'X';

	int _A3(abc,def) = 1;
	//int abcdef = 1;

	_A3(dou,ble) tt = 1.0;
	//double tt = 1.0;

	//编译器提供给我们的有用的宏名
	std::cout<<__FILE__<<std::endl; //文件路径
	std::cout<<__LINE__<<std::endl; //行号
	std::cout<<__DATE__<<std::endl; //日期
	std::cout<<__TIME__<<std::endl; //时间
	//如果是C++编译器，还会自动定义一个宏__cplusplus，可以用下面的代码
	//确定是不是C++编译器在编译本文件
#ifdef __cplusplus
	std::cout<<"C++"<<std::endl;
#else
	std::cout<<"C"<<std::endl;
#endif

	system("pause");
}