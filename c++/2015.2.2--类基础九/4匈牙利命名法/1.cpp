#include <iostream>

//前缀 + 类型标记 + 名字
//前缀
//全局变量(global:全球的，全局的):g_
//成员变量(member:成员):m_
//符号常量(constant:不变的):c_

//类型
//基本数据类型
//bool:b
//char:c
//unsigned char :uc
//wchar_t:w
//short:s
//unsigned short:us
//int:i
//unsigned int :ui
//long:l
//unsigned long:ul
//float :f
//double:d
//long double:ld
//指针(pointer):p
//引用(reference):r
//宏一般大写
//循环变化量 i j k

int g_iHeroHp;

void main()
{
	const int c_iHeroMp=100;
	int* pHeroHp = &g_iHeroHp;
	system("pause");
}