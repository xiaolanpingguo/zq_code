#include "hijack.h"
#include "stdio.h"

#include <string>
#include <windows.h>

#ifdef _WIN64
extern "C" UINT_PTR g_call[32] = {0};
#else
UINT_PTR g_call[32] = { 0 };
void __declspec(naked)g_call_01()
{
	__asm jmp dword ptr ds : [g_call + 1 * 4];
}
void __declspec(naked)g_call_02()
{
	__asm jmp dword ptr ds : [g_call + 2 * 4];
}
void __declspec(naked)g_call_03()
{
	__asm jmp dword ptr ds : [g_call +3 * 4];
}
void __declspec(naked)g_call_04()
{
	__asm jmp dword ptr ds : [g_call + 4 * 4];
}
void __declspec(naked)g_call_05()
{
	__asm jmp dword ptr ds : [g_call + 5 * 4];
}
void __declspec(naked)g_call_06()
{
	__asm jmp dword ptr ds : [g_call + 6 * 4];
}
void __declspec(naked)g_call_07()
{
	__asm jmp dword ptr ds : [g_call + 7 * 4];
}
void __declspec(naked)g_call_08()
{
	__asm jmp dword ptr ds : [g_call +8 * 4];
}
void __declspec(naked)g_call_09()
{
	__asm jmp dword ptr ds : [g_call + 9 * 4];
}
void __declspec(naked)g_call_10()
{
	__asm jmp dword ptr ds : [g_call + 10 * 4];
}
void __declspec(naked)g_call_11()
{
	__asm jmp dword ptr ds : [g_call + 11 * 4];
}
void __declspec(naked)g_call_12()
{
	__asm jmp dword ptr ds : [g_call + 12 * 4];
}
void __declspec(naked)g_call_13()
{
	__asm jmp dword ptr ds : [g_call + 13 * 4];
}
void __declspec(naked)g_call_14()
{
	__asm jmp dword ptr ds : [g_call + 14 * 4];
}
void __declspec(naked)g_call_15()
{
	__asm jmp dword ptr ds : [g_call + 15 * 4];
}
void __declspec(naked)g_call_16()
{
	__asm jmp dword ptr ds : [g_call + 16 * 4];
}
void __declspec(naked)g_call_17()
{
	__asm jmp dword ptr ds : [g_call + 17 * 4];
}
#endif

bool InitDll()
{
	// x86: C:\Windows\SysWOW64\version.dll
	// x64: C:\Windows\System32\version.dll

#ifdef _WIN64
	// no matter x86 or x64, it will return "C:\Windows\System32\version.dll"
	//char systemPath[64] = { 0 };
	//GetSystemDirectoryA(systemPath, sizeof(systemPath));

	const char* dllPath = "C:\\Windows\\System32\\version.dll";
#else
	const char* dllPath = "C:\\Windows\\SysWOW64\\version.dll";
#endif

	HMODULE handle = LoadLibraryA(dllPath);
	if (handle)
	{
		for (int i = 1; i <= 17; i++)
		{
			g_call[i] = (UINT_PTR)GetProcAddress(handle, MAKEINTRESOURCEA(i));
		}

		return true;
	}
	else
	{
		return false;
	}
}
