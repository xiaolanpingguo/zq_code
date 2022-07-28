#include <iostream>
#include <Windows.h>
#include <process.h>
using namespace std;

//互斥对象（Mutex)
//1）创建
//HANDLE CreateMutex(
//					LPSECURITY_ATTRIBUTES lpEventAttributes,//安全等级，NULL表示默认
//					BOOL bInitialOwner,//互斥量的初始拥有者，TRUE表示互斥量对象内部会记录创建它的线程的线程ID并将
//										递归计数设置为1，由于该线程ID非0，所以互斥量处于未触发状态，FALSE表示互斥量对象内部
//										的线程ID将设置为NULL，递归计数为0，这意味着互斥量不为任何线程占用，处于触发状态
//					LPCTSTR lpName//互斥量名称，多个进程中的线程通过名称来访问同一个互斥量，NULL表示匿名事件
//2）打开一个事件句柄
//HANDLE OpenEvent(
//					DWORD dwDesiredAccess,//访问权限，一般传入EVENT_ALL_ACCESS
//					BOOL bInheritHandle,//互斥量句柄的继承性，传TRUE即可
//					LPCTSTR lpName//表示名称，不同进程的各线程可以通过名称来确保他们访问的是同一个事件
//3）触发互斥量
//ReleaseMutex(HANDLE hMutex)
//访问互斥资源前应调用等待函数，结束访问应该调用该函数表示自己已经结束访问，其他线程可以开始访问了
//4）销毁事件
//CloseHandle()即可


//从该代码可以看出，互斥对象和关键段类似，也不能解决线程间的同步问题
//但互斥量能够完美解决某进程意外终止所造成的遗弃问题，比如一个互斥对象被线程创建后，
//在没有被释放前,该线程被意外终止，这时系统会自动选择一个线程来完成调度，
//此时用WaitForSingleObject()会返回WAIT_ABANDONED_0

long g_nNum;
unsigned int __stdcall Fun(void *pPM);
const int THREAD_NUM = 10;
//关键段变量声明
CRITICAL_SECTION  g_csThreadCode;
//互斥对象
HANDLE g_hThreadMutex;
int main()
{
	//关键段初始化
	g_hThreadMutex = CreateMutex(NULL, FALSE, NULL);
	InitializeCriticalSection(&g_csThreadCode);
	
	HANDLE  handle[THREAD_NUM];	
	g_nNum = 0;	
	int i = 0;
	while (i < THREAD_NUM) 
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		WaitForSingleObject(g_hThreadMutex,INFINITE);
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
	ReleaseMutex(g_hThreadMutex);
	Sleep(50);//some work should to do

	EnterCriticalSection(&g_csThreadCode);//进入各子线程互斥区域
	g_nNum++;
	Sleep(0);//some work should to do
	printf("线程编号为%d  全局资源值为%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);//离开各子线程互斥区域
	return 0;
}