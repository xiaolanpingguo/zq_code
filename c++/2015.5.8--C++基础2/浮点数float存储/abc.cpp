#include <iostream>
#include <assert.h>

//要求完成这个函数，从一个浮点数中提取其整数部分
int get_int_from_float(float num)
{
	//不能用下面的数值强转
	//return (int)num;

	//可以用下面的地址强转
	int* p = (int*)&num;
}

void main()
{
	float a = 13.125f;

	system("pause");
}