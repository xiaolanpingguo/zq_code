#include <iostream>
#include <conio.h>
#include <windows.h>
#include <process.h>

//一句C语言代码可以被翻译成多句汇编语句，而汇编语句
//是不可再分的，所以线程的切换一定是一句汇编执行完毕
//之后被切换，不是C语言代码执行完才切换

//临界区：多个线程中在同一时间只能有一个线程进入临界区
CRITICAL_SECTION cs;

unsigned int __stdcall music(void* p)
{
	while (1)
	{
		EnterCriticalSection(&cs); //入临界区

		std::cout<<"abc";
		std::cout<<"def"<<std::endl;
		Sleep(200);

		LeaveCriticalSection(&cs); //出临界区
	}
}

void main()
{
	InitializeCriticalSection(&cs); //初始化临界区

	_beginthreadex(
		0,
		0,
		music,
		0,
		0,
		0);

	while (1)
	{
		EnterCriticalSection(&cs); //入临界区

		std::cout<<"123";
		std::cout<<"456"<<std::endl;
		Sleep(200);

		LeaveCriticalSection(&cs); //出临界区
	}

	DeleteCriticalSection(&cs); //删除临界区
}