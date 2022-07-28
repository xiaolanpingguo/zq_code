#include<iostream>


void main()
{
	//C++中结果是地址的表达式
	//01)数组名
	int a[5];//a是int类型的地址
	short b[3];//b是short类型的地址
	double c[4];//c是double类型的地址
	double* e[4];//e是double*类型的地址
	//02)字符串字面常量
	"123abc你好";//char类型的地址
	L"123abc你好";//wchar_t类型的地址
	//03)&变量
	int f;//&f是int类型的地址
	int* g;//&g是int*类型的地址
	//&b[2]是short类型的地址
	//04)指针(参与运算时就看做是地址)
	int* i = &a[3];//i是int类型的地址
	int** k = &g;//k是int*类型的地址
	//05)函数名
	//main就是一个void(*)(void)类型的地址
	//前面4种都是数据地址
	//最后一种是指令地址
	system("pause");
}