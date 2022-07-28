#pragma once


#include <Windows.h>
#include <winternl.h>
#include <vector>
#include <string>
#include <string_view>
#include <memory>


struct ProcessInfo
{
	std::wstring processName;
	unsigned long pid;
	unsigned long tid;
};

class ProcessManager
{
private:
	struct SYSTEM_THREADS
	{
		LARGE_INTEGER  KernelTime;
		LARGE_INTEGER  UserTime;
		LARGE_INTEGER  CreateTime;
		ULONG          WaitTime;
		PVOID          StartAddress;
		CLIENT_ID      ClientId;
		KPRIORITY      Priority;
		KPRIORITY      BasePriority;
		ULONG          ContextSwitchCount;
		LONG           State;
		LONG           WaitReason;
	};

	struct VM_COUNTERS
	{
		SIZE_T             PeakVirtualSize;
		SIZE_T             VirtualSize;
		ULONG              PageFaultCount;
		SIZE_T             PeakWorkingSetSize;
		SIZE_T             WorkingSetSize;
		SIZE_T             QuotaPeakPagedPoolUsage;
		SIZE_T             QuotaPagedPoolUsage;
		SIZE_T             QuotaPeakNonPagedPoolUsage;
		SIZE_T             QuotaNonPagedPoolUsage;
		SIZE_T             PagefileUsage;
		SIZE_T             PeakPagefileUsage;
	};

	struct SYSTEM_PROCESSES {
		ULONG              NextEntryDelta;
		ULONG              ThreadCount;
		ULONG              Reserved1[6];
		LARGE_INTEGER      CreateTime;
		LARGE_INTEGER      UserTime;
		LARGE_INTEGER      KernelTime;
		UNICODE_STRING     ProcessName;
		KPRIORITY          BasePriority;
		ULONG              ProcessId;
		ULONG              InheritedFromProcessId;
		ULONG              HandleCount;
		ULONG              Reserved2[2];
		VM_COUNTERS        VmCounters;
		IO_COUNTERS        IoCounters;
		SYSTEM_THREADS     Threads[1];
	};

public:

	static bool getProcess(std::wstring_view name, ProcessInfo& processInfo);

	static DWORD getPid(std::wstring_view name);
	static HANDLE getProcessHandle(DWORD pid);
};

