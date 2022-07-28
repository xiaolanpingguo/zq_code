#include <iostream>

//类的前置声明

//告诉下面的代码有一个叫A的类
class A;
//A没有具体的实体

//A没有具体的实体能定义引用
void f(A& a)
{
	//仅仅是定义而已
}

void main()
{
	//A没有具体的实体不能定义对象
	//A a;

	//A没有具体的实体能定义指针
	A* b = 0;
	//b现在没有用处，因为A没有具体的定义

	system("pause");
}


