#include<iostream>

//void指针 void地址

//void关键字
//01)void修饰函数表示这个函数不返回任何数据
//02)定义void指针
//地址的两种特性：
//该地址具体的字节编号
//该地址的类型

void main()
{
	char a[8];//a的地址为0x11223346,类型为char
	a + 2;//在0x11223348上的char地址
	&a[3];//在0x11223349上的char地址
	(int*)a + 1;// 在0x1122334a上的int类型的地址
	(float*)((short*)a + 1);// 在0x11223348上的float地址
	
	//void类型的指针存储的地址只用一个特性
	//01)该地址具体的字节编号
	//即void类型指针存储的地址没有类型可言，这样的话void类型的指针
	//就有以下的特性:
	//1)任何的地址都可以赋值或者初始化给void类型的指针
	void* p1 = a;//p1存储了0x11223346

	p1 = main;//p1存储了main函数指令区的地址

	short b;//0x11223354
	
	p1 = &b;//p1存储的是0x11223354

	//2)前面讲过得4种地址运算，void类型地址都不能参与
	void* p2 = a;

	//p1[0];//error C2036: “void *”: 未知的大小
	//*p1;//error C2100: 非法的间接寻址
	//p1 + 2;// error C2036: “void *”: 未知的大小
	//p1 - p2;//error C2036: “void *”: 未知的大小
	//3)我们往往是强制转换void类型的地址在使用
	*((char*)p1) = 'x';

	//int* q = p1;//p1没有类型,不能赋值给int类型的指针

	int* q = (int*)p1;//(int*)p1是一个int类型的地址
	//q = p1;
	system("pause");
}