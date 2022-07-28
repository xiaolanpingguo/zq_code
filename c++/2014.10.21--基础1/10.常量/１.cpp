#include <iostream>

//常量：不能被改变的量
//字面常量
//符号常量


void main()
{
	false;
	true;//布尔型字面常量
	'a';//用''括起的一个文字叫字符型字面常量
	'1';
	//没有unsinged char的字面常量写法
	L'3';//wchar_t型字面常量

	"asdfdf";//char* 字符串字面常量
	//用""括起的一个或者多个文字叫字符串
	"a";
	L"a";//wchar_t* 宽字节(双字节)字符串字面常量

	//short unsigned short 没有字面常量的写法
	123;//int字面常量
	-123;//int字面常量
	0;//int字面常量

	123U;//无符号整型字面常量unsinged int
	123u;//unsinged int
	15L;//long长整型字面常量
	52l;//long长整型字面常量

	56UL;//unsinged long 无符号长整型字面常量
	65ul;//unsinged long 无符号长整型字面常量
	55Ul;//unsinged long 无符号长整型字面常量
	65uL;//unsinged long 无符号长整型字面常量
	65LU;//unsinged long 无符号长整型字面常量
	95lu;//unsinged long 无符号长整型字面常量
	99Lu;//unsinged long 无符号长整型字面常量
	99lU;//unsinged long 无符号长整型字面常量

	35.6f;//float 单精度浮点型字面常量
	66.5F;//float 单精度浮点型字面常量

	65.00;//double 双精度浮点型字面常量

	1.2L;//long double 长双精度浮点型字面常量
	1.3l;//long double 长双精度浮点型字面常量


	//long al = 41L;

	//sizeof()得到括号内的字面常量所属的数据类型的字节
	std::cout<<sizeof(false)<<std::endl;
	std::cout<<sizeof('a')<<std::endl;
	std::cout<<sizeof(L'a')<<std::endl;
	std::cout<<sizeof("a")<<std::endl;
	std::cout<<sizeof(L"assd")<<std::endl;
	std::cout<<sizeof(1)<<std::endl;
	std::cout<<sizeof(6L)<<std::endl;
	std::cout<<sizeof(8UL)<<std::endl;
	std::cout<<sizeof(3.12f)<<std::endl;
	std::cout<<sizeof(3.00)<<std::endl;
	std::cout<<sizeof(3.1L)<<std::endl;
	
	system("pause");
}