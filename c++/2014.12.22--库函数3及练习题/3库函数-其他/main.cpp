#include<iostream>
#include <assert.h>
#include <time.h>
void f()
{
	exit(0);//退出程序
}


void main()
{
	//f();
	//exit(0);退出程序
	//执行dos命令
	system("pause");
	system("cls");
	system("dir");//打印目录
	system("md c:\\8班");//新建目录
	system("pause");
	//如果()的表达式的结果为假，则强制退出程序(用的exit)
	//并给出出错的代码
	//如果()的表达式的结果为真，则什么都不会发生
	//主要用于调试，()中可以是任意表达式
	//assert(0);//断言


	//01)取随机数前一般都要设置随机种子
	//02)rand的返回值范围是0到32767
	//03)要随机得到一个范围的值必须取模
	srand((unsigned int)time(0));

	rand() % 10 + 5;

	system("pause");
}