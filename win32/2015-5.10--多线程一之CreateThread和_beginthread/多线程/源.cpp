
参考资料：http://blog.csdn.net/morewindows/article/details/7392749

#include <windows.h>

#include <process.h>

#include <iostream>

using namespace std;


//CreateThread和_beginthreadex

//如果代码中有使用标准C运行库中的函数时，尽量使用_beginthreadex代替CreateThread

//HANDLE WINAPI CreateThread(

//			   	LPSECURITY_ATTRIBUTES lpThreadAttributes,//线程内核的安全属性，NULL表示默认

//				SIZE_T dwStackSize,//线程栈空间大小，0表示默认大小（1M）

//				LPTHREAD_START_ROUTINE lpStartAddress，//执行的线程函数地址，多个线程可以使用同个函数地址

//				LPVOID lpParameter，//传给线程函数的参数

//				DWORD dwCreationFlags，//指定额外的标志来控制线程的创建，0表示线程创建过后立即就可以调度，如果为

//							CREATE_SUSPENDED表示线程创建后暂停运行，这样就无法调度，直到调用ResumeThread()

//				LPDWORD lpThreadId,//将返回线程的ID号，NULL表示不需要返回线程ID号

//函数成功返回一个新的句柄，失败返回NULL
//

//HANDLE WINAPI WaitForSingleObject(

//				HANDLE hHandle,//要等待的内核对象

//				DWORD dwMilliseconds,//最长等待时间，毫秒为单位，传入0立即返回，INFINITE表示无限等待

//函数返回值：

//WAIT_OBJECT_0:在指定的时间内，对象触发

//WAIT_TIMEOUT:超过最长时间，对象仍未被触发

//WAIT_FAILED：传入参数有误

//一般这个函数与线程函数结合用，因为线程的句柄在线程运行时是未触发的，线程结束运行，句柄处于触发状态

//所以用这个函数可以等待一个线程结束运行


//

#define THREAD_NUM 5

int a=0;

UINT WINAPI  f1(void *);

UINT WINAPI  f2(void*);

void main()
{
	
	HANDLE handle[THREAD_NUM];
	
	for(int i = 0; i < THREAD_NUM; ++i)
		
		handle[i]=(HANDLE)_beginthreadex(0,0, f1, 0,0,0 );
	
	WaitForMultipleObjects(THREAD_NUM,handle,true,INFINITE);
	
	cout<<"所以线程运行完毕。。"<<endl;
	
	for(int i = 0; i < THREAD_NUM; ++i)
		
		CloseHandle(handle[i]);
	
	system("pause");

}

UINT WINAPI  f1(LPVOID lparam)

{
	
	a++;
	
	cout<<"ID号为"<<GetCurrentThreadId()<<"的子线程输出:"<<a<<endl;
	return 0;

}

UINT WINAPI  f2(void *)

{

	
	return 0;

}