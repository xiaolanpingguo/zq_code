#pragma once

#include <windows.h>
#include <string>
#include <format>


namespace Log
{

    static bool s_enableConsole = false;
    static void enableConsole()
    {
        FreeConsole();
        AllocConsole();
        SetConsoleTitleA("D3D11 - DEBUG");
        FILE* file = NULL;
        freopen_s(&file, "CON", "w", stdout);
        s_enableConsole = true;
    }

    template <typename ...Args>
    static void LogMsg(std::string_view formatStr, Args&& ...args)
    {
        std::string str = std::format(formatStr, std::forward<Args>(args)...);
        if (!s_enableConsole)
        {
            ::OutputDebugStringA(str.c_str());
            return;
        }

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        fprintf(stdout, "[");
        SetConsoleTextAttribute(hConsole, 11);
        fprintf(stdout, "Log:");
        SetConsoleTextAttribute(hConsole, 7);
        fprintf(stdout, "] %s\n", str.c_str());

        ::OutputDebugStringA(str.c_str());
    }
};

#define LOG_ENABLE_CONSOLE() Log::enableConsole()
#define LOG_INFO(TEXT, ...) Log::LogMsg(TEXT, __VA_ARGS__)
