#include<iostream>

//C++主要是在C的基础增加了一个复合数据类型，
//称为类(class)，有了类之后,C++就被称为面向
//对象的编程语言。
//面向对象有如下三个特征：
//1)封装:对数据的保护
//2)继承:代码的复用
//3)多态:相同的调用执行不同的代码

class ABC//ABC是类型名
{
public://访问权限公有
	char a;//成员变量
	short b;
	int c;
};

void main()
{
	ABC x;//x是类的对象(类变量)
	x.a = 'a';
	x.b = 2;
	x.c = 3;

	ABC* y = &x;
	y->a = 4;
	y->b = 5;
	y->c = 6;
	system("pause");
}