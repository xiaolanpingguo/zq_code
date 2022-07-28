#include<iostream>

//此处定义了一个结构体类型名叫_ABC。此后的代码
//中就可以把_ABC当做一个类型来使用
struct _ABC
{
	char u;
	short i;
	int o;
};//u,i,o称为_ABC类型的成员变量

struct _DEF
{
	_ABC j;//结构体类型的嵌套定义
	double k;
};

void main()
{
	_DEF x;
	x.j.u = 1;
	x.j.i = 2;
	x.j.o = 3; 
	x.k = 4.0;
	std::cout<<sizeof(x)<<std::endl;
	system("pause");
}
