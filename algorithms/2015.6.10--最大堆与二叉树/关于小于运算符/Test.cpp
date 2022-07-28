// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

struct STUDENT1
{
	int id;
	char name[32];
	int age;

	//小于运算符规定就是按照id进行比较，代码
	//写死了其后很难修改比较的法则
	bool operator < (const STUDENT1& that)
	{
		return id < that.id;
	}
};

//声明
struct STUDENT2;
extern bool (* less)(const STUDENT2* s1, const STUDENT2* s2);

struct STUDENT2
{
	int id;
	char name[32];
	int age;

	bool operator < (const STUDENT2& that)
	{
		return (*less)(this, &that);
	}
};

//一个函数指针
bool (* less)(const STUDENT2* s1, const STUDENT2* s2);

bool less_id(const STUDENT2* s1, const STUDENT2* s2)
{
	return s1->id < s2->id;
}
bool less_name(const STUDENT2* s1, const STUDENT2* s2)
{
	return strcmp(s1->name, s2->name) == -1;
}
bool less_age(const STUDENT2* s1, const STUDENT2* s2)
{
	return s1->age < s2->age;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//标准库中对于数据可以进行大小比较的
	//要求就是数据类型必须支持<运算符

	STUDENT2 sa = {10, "abc", 21}, sb = {11, "aaa", 23};

	//通过下面的代码可以设置小于运算符中的具体比较方式
	less = less_id;

	if (sa < sb)
		std::cout<<"!"<<std::endl;

	less = less_name;

	if (sa < sb)
		std::cout<<"!"<<std::endl;

	return 0;
}

