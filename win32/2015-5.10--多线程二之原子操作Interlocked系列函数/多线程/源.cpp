#include <windows.h>

#include <process.h>

#include <iostream>

using namespace std;


//在下面代码中，有可能会出现数据对应的情况，因为一条自增语句是由三条汇编语句组成吗，

//所以数据很有可能再运行过程中被改变，所以我们应该对一个值的操作时候是原子操作，即不可打断性，

//Windows系统提供了Interlocked开头的函数完成这一任务

//1）递增操作

//LONG __cdecl InterlockedIncrement(LONG volatile* Addend);
//LONG __cdecl InterlockedDecrement(LONG volatile* Addend);
//返回变量执行增减操作之后的值。

//LONG __cdec  InterlockedExchangeAdd(LONG volatile* Addend, LONGValue);
//返回运算后的值，注意！加个负数就是减

//2）赋值操作
//LONG __cdecl InterlockedExchange(LONG volatile* Target, LONGValue);
//Value就是新值，函数会返回原先的值。

#define THREAD_NUM 50

int a=0;

UINT WINAPI  f1(void *);
UINT WINAPI  f2(void*);

void main()

{
	
	HANDLE handle[THREAD_NUM];
	
	for(int j = 0;j < 20; ++ j)
	
	{
		
		a = 0;
		
		for(int i = 0; i < THREAD_NUM; ++i)
			
			handle[i]=(HANDLE)_beginthreadex(0,0, f1, 0,0,0 );
		
		WaitForMultipleObjects(THREAD_NUM,handle,true,INFINITE);
		
	cout<<"开辟了"<<THREAD_NUM<<"个线程，a最后的值为："<<a<<endl;
	
	}
	
	cout<<"所以线程运行完毕。。"<<endl;
	
	for(int i = 0; i < THREAD_NUM; ++i)
		
		CloseHandle(handle[i]);
	
	system("pause");

}

UINT WINAPI  f1(LPVOID lparam)

{
	
	Sleep(100);
	//a++;
	
	InterlockedIncrement((LPLONG)&a);
	
	return 0;

}

UINT WINAPI  f2(void *)

{

	
	return 0;

}