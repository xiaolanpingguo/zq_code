#include <iostream>
#include <Windows.h>
#include <process.h>
using namespace std;

//事件EVENT
//1）创建
//HANDLE CreateEvent(
//					LPSECURITY_ATTRIBUTES lpEventAttributes,//安全等级，NULL表示默认
//					BOOL bManualRest,//TRUE表示手动置位，FALSE表示自动置位，如果是自动置位，
//							则对该事件调用WaitForSingleObjec()后会自动调用RestEvent()使事件变为未触发状态
//					BOOL bInitialState,//初始状态，TRUE表示已触发
//					LPCTSTR lpName//NULL表示匿名事件
//2）打开一个事件句柄
//HANDLE OpenEvent(
//					DWORD dwDesiredAccess,//访问权限，一般传入EVENT_ALL_ACCESS
//					BOOL bInheritHandle,//事件句柄的继承性，传TRUE即可
//					LPCTSTR lpName//表示名称，不同进程的各线程可以通过名称来确保他们访问的是同一个事件
//3）触发和未触发
//SetEvent：触发事件
//RestEvent:将事件变为未触发
//4）销毁事件
//CloseHandle()即可

//关键断可以用于线程间的互斥，但不可以用于同步
long g_nNum;
unsigned int __stdcall Fun(void *pPM);
const int THREAD_NUM = 10;
//关键段变量声明
CRITICAL_SECTION  g_csThreadCode;
//事件对象
HANDLE g_hThreadEvent;
int main()
{
	//关键段初始化
	g_hThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	InitializeCriticalSection(&g_csThreadCode);
	
	HANDLE  handle[THREAD_NUM];	
	g_nNum = 0;	
	int i = 0;
	while (i < THREAD_NUM) 
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		WaitForSingleObject(g_hThreadEvent,INFINITE);
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
	SetEvent(g_hThreadEvent);
	Sleep(50);//some work should to do

	EnterCriticalSection(&g_csThreadCode);//进入各子线程互斥区域
	g_nNum++;
	Sleep(0);//some work should to do
	printf("线程编号为%d  全局资源值为%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);//离开各子线程互斥区域
	return 0;
}