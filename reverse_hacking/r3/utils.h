#pragma once


#include <Windows.h>
#include <string>
#include <string_view>
#include <vector>


// dll module
struct ModuleData
{
	HANDLE handle;
	std::wstring name;
	std::uintptr_t address;
	int size;
};

class Utils
{
public:
	// win32
	static bool getModule(DWORD pid, std::wstring_view name, ModuleData* modudleData);
	static HWND findWindowByPid(DWORD pid, std::string_view className = nullptr);
	static bool hideThread(HANDLE hThread);

	// memory
	static std::size_t readMemory(HANDLE handle, std::uintptr_t address, void* buffer, int size);
	static std::size_t writeMemory(HANDLE handle, std::uintptr_t address, void* buffer, int size);
	static auto generateBadCharTable(std::string_view pattern) noexcept;
	static std::uintptr_t findPattern(std::uintptr_t moduleAdress, const char* signature);
	static std::uint8_t* findSignature(void* moduleBase, const char* szSignature) noexcept;
	static std::uintptr_t findPatternInMemory(HANDLE hPorcess, std::uintptr_t start, size_t size, const std::vector<std::uint8_t>& pattern) noexcept;

	// debug
	static void outputDebug(const char* pszFormat, ...);

	// math
	static bool worldToSceenDX(const float matrix[16], const float worldPos[3], int windoww, int windowh, int& screenx, int& screeny);
	static bool worldToSceenOpenGL(const float matrix[16], const float worldPos[3], int windoww, int windowh, int& screenx, int& screeny);
};
