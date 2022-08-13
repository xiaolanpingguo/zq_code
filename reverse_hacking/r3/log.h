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
        SetConsoleTitleA("Log Debug Window");
        m_enableConsole = true;
    }

	void logMsg(std::string&& str)
	{
		::OutputDebugStringA(str.c_str());
		if (m_enableConsole)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			fprintf(stdout, "[");
			SetConsoleTextAttribute(hConsole, 11);
			fprintf(stdout, "Log:");
			SetConsoleTextAttribute(hConsole, 7);
			fprintf(stdout, "] %s", str.c_str());
		}
	}

	void logMsg(std::wstring&& str)
	{
		::OutputDebugStringW(str.c_str());
		if (m_enableConsole)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			fprintf(stdout, "[");
			SetConsoleTextAttribute(hConsole, 11);
			fprintf(stdout, "Log:");
			SetConsoleTextAttribute(hConsole, 7);
			fprintf(stdout, "] %ls", str.c_str());
		}
	}

private:
    bool m_enableConsole = false;
};

#ifdef DEBUG
#define LOG_ENABLE_CONSOLE() Log::getInstance().enableConsole()
#define LOG_INFO(TEXT, ...)  Log::getInstance().logMsg(std::move(std::format(TEXT, __VA_ARGS__)))
#else
#define LOG_ENABLE_CONSOLE() 
#define LOG_INFO(TEXT, ...)  Log::getInstance().logMsg(std::move(std::format(TEXT, __VA_ARGS__)))
#endif

