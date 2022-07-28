#pragma once


#include <Windows.h>
#include <string>
#include <vector>


// dll module
struct ModuleData
{
	HANDLE handle;//模块句柄
	std::wstring name;//模块名
	std::uintptr_t address;//模块基地址
	int size;//模块大小
};

class Utils
{
public:
	// win32
	static bool getModule(DWORD pid, const wchar_t* name, ModuleData* modudleData);
	HWND findWindowByPid(DWORD pid, const char* className = nullptr);
	bool hideThread(HANDLE hThread);

	// memory
	static std::size_t readMemory(HANDLE handle, std::uintptr_t address, void* buffer, int size);
	static std::size_t writeMemory(HANDLE handle, std::uintptr_t address, void* buffer, int size);
	static auto generateBadCharTable(std::string_view pattern) noexcept;
	static std::uintptr_t findPattern(const char* start, size_t size, std::string_view pattern, bool reportNotFound = true) noexcept;
	static std::uint8_t* findSignature(void* moduleBase, const char* szSignature) noexcept;
	static std::uintptr_t findPatternInMemory(HANDLE hPorcess, std::uintptr_t start, size_t size, const std::vector<std::uint8_t>& pattern) noexcept;

	// debug
	static void outputDebug(const char* pszFormat, ...);

	// math
	static bool worldToSceenDX(const float matrix[16], const float worldPos[3], int windoww, int windowh, int& screenx, int& screeny);
	static bool worldToSceenOpenGL(const float matrix[16], const float worldPos[3], int windoww, int windowh, int& screenx, int& screeny);
};

#define LOG_INFO(TEXT, ...) Utils::outputDebug(TEXT, __VA_ARGS__)
