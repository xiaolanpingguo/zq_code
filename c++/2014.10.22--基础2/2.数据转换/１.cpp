#include <iostream>

//数据转换
//隐式转换
//显式转换(强制转换)

//隐式转换
//01）(当=两边的数据类型不一致时)=右边的最终会被转换为=左边的数据类型并赋值给左边
//02)无论有无int型的数据参与运算，所有的字节数小于int的
//类型都会被先提升为int后再参与运算
//03)字节数少的会被转换为字节数多的
//04)精度低的会被转换为精度高的

void main()
{
	int a = 1;

	int b = 3.14f;

	//int = double ->int = int
	b = 3.5;

	//int = float -> int = int
	b = 3.5f;

	//int = char + char -> int = int + int 
	int a1 = 'a' + 'b';

	double a2;

	//double = double + float->double = double + double
	a2 = 4.4 + 1.2f;

	//double = int + double->double = double + double
	a2 = 3 + 2.5;

	//double = int + float->double = float + float->double = double
    a2 = 3 + 3.14f;

	//double = float + double->double = double + double
	a2 = 3.14f + 2.58;

	//int = double + int->int = double + double->int = int
	int a3 = 1.2 + 3;// warning C4244: “初始化”: 从“double”转换到“int”，可能丢失数据

	system("pause");
}