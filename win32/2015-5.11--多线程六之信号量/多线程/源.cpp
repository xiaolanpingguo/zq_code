#include <iostream>
#include <Windows.h>
#include <process.h>
using namespace std;

//信号量Semaphore
//1）创建
//HANDLE CreateSemaphore(
//					LPSECURITY_ATTRIBUTES lpEventAttributes,//安全等级，NULL表示默认
//					LONG lInitialCount,//初始资源数量
//					LONG lMaximumCount,//最大并发数量
//					LPCTSTR lpName//信号量名称，多个进程中的线程通过名称来访问同一个互斥量，NULL表示匿名信号量
//2）打开一个信号量
//HANDLE OpenSemaphore(
//					DWORD dwDesiredAccess,//访问权限，一般传入EVENT_ALL_ACCESS
//					BOOL bInheritHandle,//信号量句柄的继承性，传TRUE即可
//					LPCTSTR lpName//表示名称，不同进程的各线程可以通过名称来确保他们访问的是同一个事件
//3）递增信号量的当前资源计数
//BOOL ReleaseSemaphore(
//						HANDLE hSemaphore,//信号量句柄名称
//						LONG lReleaseCount,//表示增加个数，必须大于0，且不超过最大资源数量
//						LONG lpPreviousCount//用来传出先前的资源计数，NULL表示不需要传出
//注意：当前资源数量大于0，表示信号量处于触发，等于0表示资源已经耗尽故信号量处于未触发，
//		在对信号量调用等待函数时，等待函数会检查信号量的当前资源计数，如果大于0，即信号量处于触发
//		状态，减1后返回继续让调用线程执行，一个线程可以多次调用等待函数来减少信号量
//4）销毁信号量
//CloseHandle()即可

//信号量的形象比喻
//以一个停车场的运作为例。简单起见，假设停车场只有三个车位，一开始三个车位都是空的。
//这时如果同时来了五辆车，看门人允许其中三辆直接进入，然后放下车拦，剩下的车则必须在入口等待，
//此后来的车也都不得不在入口处等待。这时，有一辆车离开停车场，看门人得知后，打开车拦，
//放入外面的一辆进去，如果又离开两辆，则又可以放入两辆，如此往复。
//在这个停车场系统中，车位是公共资源，每辆车好比一个线程，看门人起的就是信号量的作用。
//抽象的来讲，信号量的特性如下：信号量是一个非负整数（车位数），
//所有通过它的线程/进程（车辆）都会将该整数减一（通过它当然是为了使用资源），当该整数值为零时，
//所有试图通过它的线程都将处于等待状态。在信号量上我们定义两种操作： Wait（等待） 和 Release（释放）。
//当一个线程调用Wait操作时，它要么得到资源然后将信号量减一，要么一直等下去（指放入阻塞队列），
//直到信号量大于等于一时。Release（释放）实际上是在信号量上执行加操作，
//对应于车辆离开停车场，该操作之所以叫做“释放”是因为释放了由信号量守护的资源。
long g_nNum;
unsigned int __stdcall Fun(void *pPM);
const int THREAD_NUM = 10;
//关键段变量声明
CRITICAL_SECTION  g_csThreadCode;
//信号量
HANDLE g_hThreadSemaphore;
int main()
{
	//当前0个资源，最大允许一个同时访问
	g_hThreadSemaphore = CreateSemaphore(NULL,0, 1, NULL);
	//关键段初始化
	InitializeCriticalSection(&g_csThreadCode);
	
	HANDLE  handle[THREAD_NUM];	
	g_nNum = 0;	
	int i = 0;
	while (i < THREAD_NUM) 
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		WaitForSingleObject(g_hThreadSemaphore,INFINITE);
		++i;
	}
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);

	DeleteCriticalSection(&g_csThreadCode);
	system("pause");
	return 0;
}
unsigned int __stdcall Fun(void *pPM)
{
	int nThreadNum = *(int *)pPM; 
	//信号量++
	ReleaseSemaphore(g_hThreadSemaphore,1,NULL);
	Sleep(50);//some work should to do

	EnterCriticalSection(&g_csThreadCode);//进入各子线程互斥区域
	g_nNum++;
	Sleep(0);//some work should to do
	printf("线程编号为%d  全局资源值为%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);//离开各子线程互斥区域
	return 0;
}