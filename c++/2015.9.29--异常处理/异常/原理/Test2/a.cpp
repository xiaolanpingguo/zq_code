//new (std::nothrow) XXX;

#include <iostream>

//在通常的程序中，对于出现异常情况一般都用返回值告知
//调用者，也就是说早期的错误检查和处理主要是用返回值
//来处理的，但是通过返回值来进行的处理可以存在一些问
//题，程序代码中到处充斥着这种返回值检查，难以阅读，
//各个检查的方式和错误处理的手段又不同一，整体缺乏对
//程序错误的统一管理，为了方便地对程序中出现的错误情
//况进行有效管理，c99开始C++支持了异常处理，简单地说
//异常提供了一种在指定位置统一处理错误的办法，C++中的
//异常通过关键字throw、try、catch来处理

void f()
{
	std::cout<<"f开始"<<std::endl;

	//此处抛出一个类型为int，数值为1的异常
	throw 1;

	std::cout<<"f结束"<<std::endl;
}

void main()
{
	//1）可以抛出异常的代码如果不被放在try块中的话，
	//是不可能被捕获的，也就是如果抛异常的代码是没
	//有放在try块中的话，那么一定引发程序被系统强制
	//exit
	//2）try块和catch块必须同时出现，在一个try-catch
	//中，try只能有一个，catch可以有任意个
	//3）异常的本质就是一种跳转，只不过这种设计出来
	//的跳转用来处理错误情况非常方便

	//本try-catch块只能捕获int、double类型的异常
	try
	{
		std::cout<<"try开始"<<std::endl;
		f();
		std::cout<<"try结束"<<std::endl;
	}
	catch(int num)
	{
		std::cout<<"捕获了int类型异常"<<num<<std::endl;
	}
	catch(double num)
	{
		std::cout<<"捕获了double类型异常"<<num<<std::endl;
	}

	system("pause");
}