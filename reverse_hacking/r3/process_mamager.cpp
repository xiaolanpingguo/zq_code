#include "process_mamager.h"
#include "utils.h"
#include <tlhelp32.h>


bool ProcessManager::getProcess(std::wstring_view name, ProcessInfo& processInfo)
{
#ifdef _WIN64
	return false;
#else
	using f_NTQuerySystemInformation = NTSTATUS(WINAPI*)(ULONG, PVOID, ULONG, PULONG);

	const auto hNTDLL{ LoadLibraryW(L"ntdll") };
	if (!hNTDLL)
	{
		return false;
	}

	const auto ntQSI{ reinterpret_cast<f_NTQuerySystemInformation>(GetProcAddress(hNTDLL, "NtQuerySystemInformation")) };
	if (!ntQSI)
	{
		return false;
	}

	ULONG buffersize;
	if (!NT_SUCCESS(ntQSI(SystemProcessInformation, nullptr, 0, &buffersize)))
	{
		auto buffer{ std::make_unique<unsigned char[]>(buffersize) };
		auto spi{ reinterpret_cast<SYSTEM_PROCESSES*>(buffer.get()) };

		NTSTATUS status;
		if (!NT_SUCCESS(status = ntQSI(SystemProcessInformation, spi, buffersize, nullptr)))
		{
			return false;
		}

		while (spi->NextEntryDelta)
		{
			if (wcsncmp(spi->ProcessName.Buffer, name.data(), name.length()) == 0)
			{
				spi = reinterpret_cast<SYSTEM_PROCESSES*>((LPBYTE)spi + spi->NextEntryDelta);
				processInfo.pid = spi->ProcessId;
				processInfo.processName = spi->ProcessName.Buffer;
				processInfo.tid = reinterpret_cast<ULONG>(spi->Threads->ClientId.UniqueThread);
				return true;
			}
		}
	}

	return false;
#endif
}

DWORD ProcessManager::getPid(std::wstring_view name)
{
	//函数通过获取进程信息为指定的进程、进程使用的堆[HEAP]、模块[MODULE]、线程建立一个快照.
	// 可以获取系统中正在运行的进程信息，线程信息等
	HANDLE hande = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hande == INVALID_HANDLE_VALUE) 
	{
		return 0;
	}

	PROCESSENTRY32 pInfo = { 0 };
	pInfo.dwSize = sizeof(pInfo);
	BOOL state = Process32First(hande, &pInfo);
	while (state) 
	{
		if (wcsncmp(pInfo.szExeFile, name.data(), name.length()) == 0)
		{
			CloseHandle(hande);
			return pInfo.th32ProcessID;
		}

		state = Process32Next(hande, &pInfo);
	}

	return 0;
}

HANDLE ProcessManager::getProcessHandle(DWORD pid) 
{
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (handle == 0)
	{
		return nullptr;
	}

	return handle;
}

