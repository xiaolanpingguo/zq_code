#include <iostream>

//C语言（非纯C语言）
//1)基本数据类型
//2)运算符
//3)流程控制
//4)数组
//5)字符串
//6)地址和指针
//7)函数
//{
//	默认参数
//	static
//	重载
//	内联
//	声明和定义
//	头文件
//}
//8)生成可执行文件的步骤
//9)宏
//10)库函数
//11)复合数据类型

//C++语言
//1)成员变量和成员函数
//2)构造和析构
//3)拷贝构造和同类复制
//4)运算符重载
//5)继承
//6)多态
//7)模板

//数据结构
//1)顺序表
//2)链表
//3)基于折半查找的映射

//算法
//1)排序
//2)查找
//3)寻路

//得到f1对f2取模结果的宏
#define _FLOAT_MODAL(f1,f2) (((f1))-((int)((f1)/(f2)))*((f2)))

int add(int a, int b, int c)
{
	//aa aa aa aa
	//bb bb bb bb
	//cc cc cc cc
	return a + (&a)[1] + (&a)[2];
}
int sub(int a, int b, int c)
{
	return a - b - c;
}
int sub2(int a, int b)
{
	return a - b;
}
float sub3(int a, int b, int c)
{
	return (float)a - b - c;
}

//对整数进行排序
void sort_bubble_int(int* p, int num)
{
	for (int i = num - 1; i > 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (p[j] > p[j + 1])
			{
				int t = p[j];
				p[j] = p[j + 1];
				p[j + 1] = t;
			}
		}
	}
}

//对学员进行排序
struct _STUDENT
{
	int id; //学号
	char name[32]; //姓名
	int age; //年龄
	//身高、体重、血型...
	//如果还要添加更多的属性进行排序，那么下面的
	//函数势必还要添加那段排序的代码，而代码中仅
	//仅只有那句比较语句不同：if (...)
};
void sort_bubble_STUDENT1(_STUDENT* p, int num, int data_type)
{
	//如果data_type为0，表示用学号排序
	//如果data_type为1，表示用姓名排序
	//如果data_type为2，表示用年龄排序

	switch (data_type)
	{
	case 0:
		{
			for (int i = num - 1; i > 0; --i)
			{
				for (int j = 0; j < i; ++j)
				{
					if (p[j].id > p[j + 1].id)
					{
						_STUDENT t = p[j];
						p[j] = p[j + 1];
						p[j + 1] = t;
					}
				}
			}
			break;
		}
	case 1:
		{
			for (int i = num - 1; i > 0; --i)
			{
				for (int j = 0; j < i; ++j)
				{
					if (strcmp(p[j].name, p[j + 1].name) == 0)
					{
						_STUDENT t = p[j];
						p[j] = p[j + 1];
						p[j + 1] = t;
					}
				}
			}
			break;
		}
	case 2:
		{
			for (int i = num - 1; i > 0; --i)
			{
				for (int j = 0; j < i; ++j)
				{
					if (p[j].age > p[j + 1].age)
					{
						_STUDENT t = p[j];
						p[j] = p[j + 1];
						p[j + 1] = t;
					}
				}
			}
			break;
		}
	}
}

void sort_bubble_STUDENT2(_STUDENT* p,
						  int num,
						  //这个函数指针应该被初始化，是用来进行比较
						  //s1和s2，如果s1是大于s2的，那么要求该函数
						  //指针指向的函数返回true，否则返回false，这
						  //个_left_bigger_right指针是作为本函数的一个
						  //形式参数
						  bool (*_left_bigger_right)(_STUDENT* s1, _STUDENT* s2))
{
	for (int i = num - 1; i > 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			//下面这句代码中，具体的比较方式是由我们初始化
			//_left_bigger_right的实际参数决定，实际参数就
			//是一个返回值为bool，形式参数表是(STUDENT*,STUDENT*)
			//的函数，可以设置多个这种函数，传入不同的函数
			//就能够按照不同的规则进行排序，这样的话，一旦
			//为结构体添加了新的成员变量，本函数也无需改变，
			//只需要添加新的比较函数即可
			if ((*_left_bigger_right)(&p[j], &p[j + 1]))
			{
				_STUDENT t = p[j];
				p[j] = p[j + 1];
				p[j + 1] = t;
			}
		}
	}
}

bool sort_by_id(_STUDENT* s1, _STUDENT* s2)
{
	return s1->id > s2->id;
}
bool sort_by_name(_STUDENT* s1, _STUDENT* s2)
{
	return strcmp(s1->name, s2->name) == 1;
}
bool sort_by_age(_STUDENT* s1, _STUDENT* s2)
{
	return s1->age > s2->age;
}

void main()
{
	//1）使浮点数支持取模运算
	std::cout<<_FLOAT_MODAL(4.3, 1.5)<<std::endl;

	//2）位运算符
	//   按位与一般用来把指定字节中的某些位置0，其它位不变
	//   按位或一般用来把指定字节中的某些位置1，其它位不变

	//3）sizeof
	//  a)sizeof(类型名)得到该类型占据的字节数
	//  b)sizeof(表达式)得到该表达式结果的类型占据的字节数
	//  c)sizeof(数组名)得到数组的总大小
	//  d)sizeof(字符串字面常量)得到存储该字符串所需总字节数，含结束符0

	//4）数组名是地址，地址是常量不是变量，不能放在=的左侧

	//5）字符串字面常量
	//   编译器在扫描代码文本的时候，一旦在代码中发现类似"123abc"
	//   之类的字符串字面常量，那么就在常量内存区开辟该字符串长度
	//   再加1个字节的连续内存块，然后把该字符串中的每个文字对应的
	//   整数编码依次存放到刚才开辟的内存块中，最后多出的一个字节
	//   被设置为0作为结束符，且该字符串字面常量作为表达式的结果是
	//   刚才开辟的内存区的首地址
	//   0x11223344 61 <- "123abc"
	//   0x11223345 62 <- "123abc" + 1、&("123abc"[2]) - 1
	//   0x11223346 63
	//   0x11223347 31
	//   0x11223348 32
	//   0x11223349 33 <- "123abc" + 5
	//   0x1122334a 00

	//6）结果是地址的表达式
	//   a)数组名
	//   b)字符串字面常量（字符类型地址）
	//   c)&变量
	//   d)指针
	//   e)函数名

	//7）地址可以进行的运算
	//   a)地址和整数的加减法，结果是地址
	//   b)地址前面加*（解引用），结果是变量
	//   c)地址后面加[]（下标），结果是变量，地址[0]就是*地址，地址[1]就是*(地址+1)
	//   d)地址和地址的减法，结果是整数

	//8）地址的强转
	bool a1 = true; //01
	short a2 = 12345; //39 30
	int a3 = 123456789; //15 cd 5b 07
	char a4[7] = {}; //00 00 00 00 00 00 00
	*((bool*)a4) = a1; //完全等同于((bool*)a4)[0] = a1;
	//01 00 00 00 00 00 00
	*((short*)(a4 + 1)) = a2;
	//01 39 30 00 00 00 00
	*((int*)(a4 + 3)) = a3;
	//01 39 30 15 cd 5b 07

	//9）函数的四大要素
	//  a)返回值类型，分为void和非void两大类
	//  b)函数名，函数名就是函数的指令内存区在内存中的首地址
	//  c)形式参数，形式参数一定是一个变量，实际参数可以是
	//    任何结果类型和形式参数类型相同的表达式，在函数调
	//    用的瞬间，即在形式参数开辟内存之后用实际参数对形
	//    势进行初始化，一旦初始化完毕之后二者再无任何联系，
	//    注意形式参数在内存中是连续存放的
	//  d)函数体，即函数执行代码的真正实现
	std::cout<<add(1, 2, 3)<<std::endl;

	//10）指针分两大类，一类是指向数据的，一种是指向函数的，指向
	//    函数的指针称之为函数指针
	//int* p = add; //数据指针p是不能指向函数的
	int (* q)(int,int,int) = add; //q是一个函数指针，它只能指向一个返回值为int，形式参数表为(int,int,int)的函数
	//q = &a3; //函数指针p是不能指向数据的
	int w = (*q)(1, 2, 3); //因为当前q是指向add的，所以完全等同于int w = add(1, 2, 3);
	q = sub; //将函数sub赋值给q指针
	w = (*q)(1, 2, 3); //完全等同于w = sub(1, 2, 3);
	//q = sub2; //sub2的形式参数不符合q指针的要求，是不能赋值的
	//q = sub3; //sub2的返回值类型不符合q指针的要求，是不能赋值的
	sort_bubble_STUDENT2(0, 0, sort_by_id);
	sort_bubble_STUDENT2(0, 0, sort_by_name);
	sort_bubble_STUDENT2(0, 0, sort_by_age);

	//11）指针函数，返回值类型是指针的函数就是指针函数，比如库函数中
	//    的const char* strstr(const char* s1, const char* s2)，以及
	//    char* strcpy(char* s1, const char* s2)都是指针函数，它们的
	//    返回值都是地址


	system("pause");
}