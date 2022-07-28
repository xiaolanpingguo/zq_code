#include<iostream>

void main()
{
	//强制转换就是一次运算，是修改类型的运算
	int a = (int)1.0;//(int)1.0的结果就是int类型的1
	a = 2;
	(char)a;//(char)a的结果就是char类型的整数2

	//(char)a = 3;//error C2106: “=”: 左操作数必须为左值
	//(char)a不是变量
	
	a = 0;//00 00 00 00
	char b = 1;//01
	
	a = (short)b;//00 00 00 00 = (强制转换)01 00 
	//->00 00 00 00 = (隐式转换)01 00 00 00
	
	system("pause");
}