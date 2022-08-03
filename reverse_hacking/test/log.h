#pragma once

#include <windows.h>
#include <string>
#include <format>


class Log
{
public:
    Log() = default;
    ~Log() = default;

    static Log& getInstance()
    {
        static Log log;
        return log;
    }

    void enableConsole()
    {
        FreeConsole();
        AllocConsole();
        SetConsoleTitleA("D3D11 - DEBUG");
        FILE* file = NULL;
        freopen_s(&file, "CON", "w", stdout);
        m_enableConsole = true;
    }

    template <typename ...Args>
    void LogMsg(std::string_view formatStr, Args&& ...args)
    {
        std::string str = std::format(formatStr, std::forward<Args>(args)...);
        if (!m_enableConsole)
        {
            ::OutputDebugStringA(str.c_str());
            return;
        }

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        fprintf(stdout, "[");
        SetConsoleTextAttribute(hConsole, 11);
        fprintf(stdout, "Log:");
        SetConsoleTextAttribute(hConsole, 7);
        fprintf(stdout, "] %s", str.c_str());

        ::OutputDebugStringA(str.c_str());
    }

private:
    bool m_enableConsole = false;
};

#define LOG_ENABLE_CONSOLE() Log::getInstance().enableConsole()
#define LOG_INFO(TEXT, ...)  Log::getInstance().LogMsg(TEXT, __VA_ARGS__)
