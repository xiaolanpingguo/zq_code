#ifndef SCM_DRV_CTRL_H
#define SCM_DRV_CTRL_H

#include <windows.h>
#pragma comment(lib,"advapi32.lib")

class cDrvCtrl
{
public:
	cDrvCtrl();
	~cDrvCtrl();
private:

	//错误码
	DWORD m_dwLastError;

	//驱动文件路径
	PCHAR m_pSysPath;

	//服务名
	PCHAR m_pServiceName;

	//用户界面显示名
	PCHAR m_pDisplayName;

	//符号链接句柄句柄
	HANDLE m_hDriver;

	//服务控制管理器句柄
	SC_HANDLE m_hSCManager;

	//服务管理器句柄
	SC_HANDLE m_hService;
public:

	//安装驱动
	BOOL Install(PCHAR pSysPath, PCHAR pServiceName, PCHAR pDisplayName);

	//启动服务
	BOOL Start();

	//暂停服务
	BOOL Stop();

	//卸载驱动
	BOOL Remove();

	//"打开"驱动的符号链接,相当于获得一个与驱动通信的句柄
	BOOL Open(PCHAR pLinkName);

	//与驱动进行IO控制
	BOOL IoControl(DWORD dwIoCode, PVOID InBuff, DWORD InBuffLen, PVOID OutBuff, DWORD OutBuffLen, DWORD *RealRetBytes);

	//关闭符号链接句柄
	void CloseDrvHandle();

private:

	//通过服务器名获得服务句柄
	BOOL GetSvcHandle(PCHAR pServiceName);

	//构造IO控制代码
	DWORD CTL_CODE_GEN(DWORD lngFunction);
};



#endif
