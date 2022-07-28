#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _STUDENT
{
	int _id;
	char _name[32];
	int _age;

	//纯C代码中不能有成员函数
	void (*Init)(struct _STUDENT*, int, const char*, int);
};

void Init_Student(struct _STUDENT* this, int id, const char* name, int age)
{
	//此处this只是一个普通标识符，不是关键字
	this->_id = id;
	strcpy_s(this->_name, 32, name);
	this->_age = age;
}

void main()
{
	struct _STUDENT s;

	//将函数赋值到成员变量（函数指针）中
	s.Init = Init_Student;

	//相当于成员函数的调用
	(s.Init)(&s, 1, "abc", 2); //有点像s.Init(1, "abc", 2);

	system("pause");
}

//class Student
//{
//	int _id;
//	char _name[32];
//	int _age;
//
//	void Init(int id, const char* name, int age)
//	{
//		_id = id;
//		strcpy_s(_name, 32, name);
//		_age = age;
//	}
//};
//C++编译器会把成员函数重新处理为类似下面的情况
//void Init(Student* this, int id, const char* name, int age)
//{
//	this->_id = id;
//	strcpy_s(this->_name, 32, name);
//	this->_age = age;
//}
//Student s;
//s.Init(1, "abc", 2); //左侧的调用语句会被编译器修改为Init(&s, 1, "abc", 2);