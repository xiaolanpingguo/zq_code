#include "dllloader.h"
#include "r3/log.h"


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
		LOG_ENABLE_CONSOLE();
		LOG_INFO("DLL_PROCESS_ATTACH: {}\n", (void*)hModule);

        DllLoader::start();
		break;
    }
    case DLL_PROCESS_DETACH:
    {
        break;
    }
    }
    return TRUE;
}

