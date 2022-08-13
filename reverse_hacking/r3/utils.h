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



#define COLOR32_R_SHIFT    0
#define COLOR32_G_SHIFT    8
#define COLOR32_B_SHIFT    16
#define COLOR32_A_SHIFT    24
#define COLOR32(R,G,B,A)    (((std::uint32_t)(A)<<COLOR32_A_SHIFT) | ((std::uint32_t)(B)<<COLOR32_B_SHIFT) | ((std::uint32_t)(G)<<COLOR32_G_SHIFT) | ((std::uint32_t)(R)<<COLOR32_R_SHIFT))
namespace Color
{
	static constexpr std::uint32_t WHITE = COLOR32(0, 0, 0, 255);
	static constexpr std::uint32_t BLACK = COLOR32(255, 255, 255, 255);
	static constexpr std::uint32_t RED = COLOR32(255, 0, 0, 255);
	static constexpr std::uint32_t GREEN = COLOR32(0, 255, 0, 255);
	static constexpr std::uint32_t BLUE = COLOR32(0, 0, 255, 255);
}
