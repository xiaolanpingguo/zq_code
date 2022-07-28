#include<iostream>

//函数
//return的作用
//01)结束函数的执行
//02)在非void返回值类型的函数中返回一个表达式，
//则return后面表达式的结果就是该函数作为表达式的结果

//函数的4大要素
//1)返回值类型
//  a)void类型
//    可以不用return关键字，如果用return关键字，
//	  那么其后不能带任何表达式
//  b)非void类型
//     这种函数必须使用return关键字,而且return
//     关键字后面必须加上一个和返回值类型相同
//     的表达式。
//2)函数名
//	a)函数名就是这个函数的指令内存区的首地址
//  b)函数的调用的语法：函数名(实际参数1,实际参数2,...实际参数n);
//3)形式参数表
//  a)形式参数表可以是空表，比如说printhello，main。
//  b)形式参数是变量,可以有任意个，每个形式参数必须以
//    逗号隔开
//  c)在调用函数的时候，必须为形式参数表中的每个形式参数
//    填写对应的实际参数(结果的类型和形式参数类型相同的任意
//    表达式),实际参数将依次初始化形式参数，初始化完毕后二者将
//    再无任何关系.
//  d)形式参数的本质就是其所在的函数的局部变量
//  e)形式参数在内存中是连续的
//4)函数体
// 写代码的地方

int/*返回值类型*/ add2/*函数名*/(int a,int b)/*形式参数表*/
{//函数体-开始
	//int c;
	//c = a + b;
	//return c;
	return a + b;
}//函数体-结束

void /*返回值类型*/ printhello/*函数名*/()/*形式参数表*/
{//函数体-开始
	std::cout<<"hello"<<std::endl;
	return;
	std::cout<<"HELLO"<<std::endl;
}//函数体-结束

int add3(int a,int b,int c)
{
	return add2(add2(a,b),c);
}

int add4(int a,int b,int c,int d)
{
	return (&a)[0] + (&a)[1] + (&a)[2] + (&a)[3];
}

void main()
{
	//main函数调用2次add2函数
	//第一次调用传入的实际参数100,200
	//add2(int a = 100,int b = 200)
	//第二次调用传入的实际参数6 + 2,5
	//add2(int a = 6 + 2,int b = 5)
	int x = add2(100,200) + add2(6 + 2 ,5);

	//
	int y = add2(x,x * 2);

	//int z = add2(x,&y);//&y的类型不是int

	//main调用了printhello函数
	printhello();

	int z = add3(1,2,3);

	int t = add4(1,2,3,4);
	system("pause");
}