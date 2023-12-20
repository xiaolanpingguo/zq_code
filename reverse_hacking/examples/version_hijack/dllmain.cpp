// dllmain.cpp : Defines the entry point for the DLL application.
#include "hijack.h"

#include <windows.h>
#include <winternl.h> // hideThread

/*
    change:  
    1: C++->optimation->disable(OD0)
    2: for x64, right click project->build dependencies->build customazation->masm
    3: for x86: if you want to use x86 version.dll, you must remove x64call.aasm
*/

static const char* s_dllLoaderName = "LogitechLedHelper.dll";


static bool hideThread(HANDLE hThread)
{
    using FnSetInformationThread = NTSTATUS(NTAPI*)(HANDLE, THREADINFOCLASS, PVOID, ULONG);
    const auto NtSetInformationThread{ reinterpret_cast<FnSetInformationThread>(::GetProcAddress(::GetModuleHandle(L"ntdll.dll"), "NtSetInformationThread")) };
    if (NtSetInformationThread == nullptr)
    {
        return false;
    }

    // ThreadHideFromDebugger:0x11 
    // it mean any exceptions skip the debugger and either hit SEH or explode and crash the app
    if (SUCCEEDED(NtSetInformationThread(hThread, (THREADINFOCLASS)0x11, NULL, 0)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    DisableThreadLibraryCalls(hModule);
    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
    {
        return FALSE;
    }

    hideThread(hModule);

    if (InitDll())
    {
        LoadLibraryA(s_dllLoaderName);
    }

    ::CloseHandle(hModule);
    return TRUE;
}

