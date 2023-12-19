// dllmain.cpp : Defines the entry point for the DLL application.
#include "hijack.h"

#include <windows.h>

/*
    change:  
    1: C++->optimation->disable(OD0)
    2: for x64, right click project->build dependencies->build customazation->masm
    3: for x86: if you want to use x86 version.dll, you must remove x64call.aasm
*/

static const char* s_dllLoaderName = "Log1techLed.dll";

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
		if (InitDll())
		{
			LoadLibraryA(s_dllLoaderName);
		}

        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

