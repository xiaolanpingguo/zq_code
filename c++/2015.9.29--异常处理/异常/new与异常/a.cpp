#include <iostream>

//malloc如果失败就返回0
//new如果失败将会抛出一个std::bad_alloc异常

void* operator new (size_t size, const char* s)
{
	return malloc(size);
}

void main()
{
	//如果堆被破坏了，或者真的没有内存了，那么抛出std::bad_alloc异常
	//new int;

	//如果堆被破坏了，或者真的没有内存了，那么这句表达式的结果为0但是不抛异常
	//new (std::nothrow) int; //本质是重载new运算符

	int* p = new ("123abc") int;

	system("pause");
}