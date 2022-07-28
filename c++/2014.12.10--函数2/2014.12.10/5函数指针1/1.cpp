#include<iostream>
//递归
//函数的默认参数
//函数的重载
//函数指针

int add2(int a,int b)
{
	return a + b;
}
int add3(int a,int b,int c)
{
	return a + b + c;
}
int  sub2(int a,int b)
{
	return a - b;
}

void f(const char* p)
{
	std::cout<<p + 1<<std::endl;
}
void main()
{
	//返回值类型 函数指针名 （形式参数表(只写数据类型)）;
	void (*q)(const char*) = 0;
	q = f;
	(*q)("asdff");
	//void* q1 = f;
	//int* q2 = sub2;
	//01)函数名是函数的首地址
	//02)指向变量的指针是不能指向函数的
	//03)void指针是可以指向函数的，但没有用

	//所有的指向变量的指针(除开void指针)都不能指向函数
	//void指针是可以指向函数的，但没有用

	int (*p)(int,int) = add2;
	//add2的返回值，形式参数表符合p的要求
	//函数指针 = 函数名
	p = sub2;
	//sub2的返回值，形式参数表符合p的要求

	//p = add3;
	//add3的返回值，形式参数表不符合p的要求

	//*函数指针就表示其指向的函数
	std::cout<<(*p)(1,2)<<std::endl;//相当于sub2(1,2)

	p = add2;
	std::cout<<(*p)(1,2)<<std::endl;//相当于add2(1,2)

	//函数指针可以用同一句代码完成不同的功能(多态)


	//函数指针数组
	int (*r[3])(int,int) = {p,sub2,r[1]};
	//r[0] = p,r[1] = sub2; r[2] = r[1];
	std::cout<<(*r[0])(1,2)<<std::endl;//3
	std::cout<<(*r[1])(1,2)<<std::endl;//-1
	std::cout<<(*r[2])(1,2)<<std::endl;//-1
	system("pause");
}