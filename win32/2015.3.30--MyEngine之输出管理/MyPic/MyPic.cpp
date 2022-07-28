// MyPic.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif
//动态链接库的入口点函数
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{

    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

