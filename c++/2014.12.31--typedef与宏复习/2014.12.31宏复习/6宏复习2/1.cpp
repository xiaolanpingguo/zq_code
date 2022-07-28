#include<iostream>

//#ifdef ,#ifndef, #else,#endif,#if,#elif

#define ABC//宏可以没有替换文本
#define XYZ 5

void main()
{
#ifdef ABC //如果定义ABC宏，就编译下面的代码直到#endif为止

	std::cout<<1<<std::endl;

#endif

	//下面的打印语句虽然不可能执行，但是一定会被编译
	//而上面的语句如果没有定义ABC宏，就相当于没有
	//std::cout<<1<<std::endl;
	if(0)
		std::cout<<2<<std::endl;

#ifdef DEF //如果定义了DEF宏，就编译下面代码直到#else
	std::cout<<3<<std::endl;
#else//如果没有定义DEF宏，就编译下面代码直到#endif
	std::cout<<4<<std::endl;
#endif

#ifndef DEF //如果没有定义DEF宏，就编译下面代码直到#else
	std::cout<<5<<std::endl;
#else//如果定义了DEF宏，就编译下面代码直到#endif
	std::cout<<6<<std::endl;
#endif

#if 1 //如果#if后面的常量表达式(可以用逻辑,关系运算符)为真，就编译下面的代码直到#endif
	std::cout<<7<<std::endl;
#endif

#if 0 //如果#if后面的常量表达式(可以用逻辑,关系运算符)为真，就编译下面的代码直到#else
	std::cout<<8<<std::endl;
#else//如果#if后面的常量表达式(可以用逻辑,关系运算符)为假，就编译下面的代码直到#endif
	std::cout<<9<<std::endl;
#endif

#if XYZ == 0//如果#if后面的常量表达式(可以用逻辑,关系运算符)为真，就编译下面的代码直到#elif
	std::cout<<10<<std::endl;
#elif XYZ == 1//如果#elif后面的常量表达式(可以用逻辑,关系运算符)为真，就编译下面的代码直到#elif
	std::cout<<11<<std::endl;
#elif XYZ == 2//如果#elif后面的常量表达式(可以用逻辑,关系运算符)为真，就编译下面的代码直到#else
	std::cout<<12<<std::endl;
#else//如果#else后面的常量表达式(可以用逻辑,关系运算符)为真，就编译下面的代码直到#endif
	std::cout<<13<<std::endl;
#endif

	system("pause");
}