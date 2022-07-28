#include "utils.h"
#include <assert.h>
#include <vector>
#include <array> // patten
#include <tlhelp32.h> // module



bool Utils::getModule(DWORD pid, const wchar_t* name, ModuleData* modudleData)
{
	if (modudleData == nullptr || name == nullptr)
	{
		return false;
	}

	HANDLE hand = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (hand == INVALID_HANDLE_VALUE) 
	{
		return false;
	}

	MODULEENTRY32 moduleInfo = {0};
	moduleInfo.dwSize = sizeof(moduleInfo);
	BOOL state = Module32First(hand, &moduleInfo);
	while (state) 
	{
		if (wcsncmp(moduleInfo.szModule, name, wcslen(name)) == 0)
		{		
			modudleData->size = moduleInfo.modBaseSize;
			modudleData->address = (std::uintptr_t)moduleInfo.modBaseAddr;
			modudleData->handle = moduleInfo.hModule;
			modudleData->name = moduleInfo.szModule;

			::CloseHandle(hand);
			return true;
		}

		state = Module32Next(hand, &moduleInfo);
	}

	return false;
}

void Utils::outputDebug(const char* pszFormat, ...)
{
	char buf[1024];
	va_list argList;
	va_start(argList, pszFormat);
	vsprintf_s(buf, pszFormat, argList);
	::OutputDebugStringA(buf);
	va_end(argList);
}

bool Utils::worldToSceenDX(const float matrix[16], const float worldPos[3], int windoww, int windowh, int& screenx, int& screeny)
{
	// TopLeftX和TopLeftY为视平面在左上角的坐标点，一般来说都为0。Width为视平面的宽度，Height为视平面的高度，MinDepth为顶点的最小深度(Z缓存),
	// MaxDepth为顶点的最大深度(Z缓存), 一般来说MinDepth为0，MaxDepth为1.
						/*
							2/w,			0,					0,					0
							0,				-h/2,				0,					0
	[Xn, Yn, Zn, 1]	*		0,				0,					MaxDepth-MinDepth	0
							TopLeft+w/2,	TopLeftY + h/2		MinDepth,			1
						*/

	float worldPosx = worldPos[0]; 
	float worldPosy = worldPos[1];
	float worldPosz = worldPos[2];

	float clipCoordsx = worldPosx * matrix[0] + worldPosy * matrix[1] + worldPosz * matrix[2] + matrix[3] * 1;
	float clipCoordsy = worldPosx * matrix[4] + worldPosy * matrix[5] + worldPosz * matrix[6] + matrix[7] * 1;
	float clipCoordsz = worldPosx * matrix[8] + worldPosy * matrix[9] + worldPosz * matrix[10] + matrix[11] * 1;
	float clipCoordsw = worldPosx * matrix[12] + worldPosy * matrix[13] + worldPosz * matrix[14] + matrix[15] * 1;

	if (clipCoordsw < 0.01f)
	{
		return false;
	}

	// clipCoords -> NDC 
	float NDCx = clipCoordsx / clipCoordsw;
	float NDCy = clipCoordsy / clipCoordsw;

	// NDC -> screen coords
	screenx = (int)(windoww * 0.5 * (1.f + NDCx));
	screeny = (int)(windowh * 0.5 * (1.f - NDCy));

return true;
}

bool Utils::worldToSceenOpenGL(const float matrix[16], const float worldPos[3], int windoww, int windowh, int& screenx, int& screeny)
{
	// 对于2D屏幕，f和n一般为0，因此第三行都为0
	/*
		2/w,	0,		0,			x + w/2
		0,		h/2,	0,			y + h/2
		0,		0,		(f-n)/2,	(f+n)/2			*  [Xn, Yn, Zn, 1]
		0,		0,		0,			1
	*/
	float worldPosx = worldPos[0];
	float worldPosy = worldPos[1];
	float worldPosz = worldPos[2];

	float clipCoordsx = worldPosx * matrix[0] + worldPosy * matrix[4] + worldPosz * matrix[8] + matrix[12] * 1;
	float clipCoordsy = worldPosx * matrix[1] + worldPosy * matrix[5] + worldPosz * matrix[9] + matrix[13] * 1;
	float clipCoordsz = worldPosx * matrix[2] + worldPosy * matrix[6] + worldPosz * matrix[10] + matrix[14] * 1;
	float clipCoordsw = worldPosx * matrix[3] + worldPosy * matrix[7] + worldPosz * matrix[11] + matrix[15] * 1;

	if (clipCoordsw < 0.01f)
	{
		return false;
	}

	// clipCoords -> NDC 
	float NDCx = clipCoordsx / clipCoordsw;
	float NDCy = clipCoordsy / clipCoordsw;

	// NDC -> screen coords
	screenx = (int)(windoww / 2 * NDCx + NDCx + windoww / 2);
	screeny = (int)(-windowh / 2 * NDCy + NDCy + windowh / 2); // reverse Y

	return true;
}

std::size_t Utils::readMemory(HANDLE handle, std::uintptr_t address, void* buffer, int size)
{
	SIZE_T read_zise;
	::ReadProcessMemory(handle, (LPCVOID)address, buffer, (SIZE_T)size, &read_zise);
	return (std::size_t)read_zise;
}

std::size_t Utils::writeMemory(HANDLE handle, std::uintptr_t address, void* buffer, int size)
{
	SIZE_T write_zise;
	::WriteProcessMemory(handle, (LPVOID)address, buffer, (SIZE_T)size, &write_zise);
	return (std::size_t)write_zise;
}

auto Utils::generateBadCharTable(std::string_view pattern) noexcept
{
	assert(!pattern.empty());

	std::array<std::size_t, (std::numeric_limits<std::uint8_t>::max)() + 1> table;
	size_t lastWildcard = pattern.rfind('?');
	if (lastWildcard == std::string_view::npos)
	{
		lastWildcard = 0;
	}

	const size_t defaultShift = (std::max)(std::size_t(1), pattern.length() - 1 - lastWildcard);
	table.fill(defaultShift);

	for (auto i = lastWildcard; i < pattern.length() - 1; ++i)
	{
		table[static_cast<std::uint8_t>(pattern[i])] = pattern.length() - 1 - i;
	}

	return table;
}

std::uintptr_t Utils::findPattern(const char* start, size_t size, std::string_view pattern, bool reportNotFound) noexcept
{
	if (start == nullptr || size == 0)
	{
		return 0;
	}

	const size_t lastIdx = pattern.length() - 1;
	const std::array<std::size_t, (std::numeric_limits<std::uint8_t>::max)() + 1> badCharTable = generateBadCharTable(pattern);;
	const char* end = start + size - pattern.length();

	while (start <= end) 
	{
		size_t i = lastIdx;
		if (pattern[i] == '?')
		{

		}
		if (start[i] == pattern[i])
		{

		}
		while (i >= 0 && (pattern[i] == '?' || start[i] == pattern[i]))
		{
			--i;
		}

		if (i < 0)
		{
			return reinterpret_cast<std::uintptr_t>(start);
		}

		start += badCharTable[static_cast<std::uint8_t>(start[lastIdx])];
	}

	if (reportNotFound)
	{
		assert(false);
		MessageBoxA(nullptr, ("Failed to find pattern #" + std::string(pattern) + '!').c_str(), "Osiris", MB_OK | MB_ICONWARNING);
	}

	return 0;
}

std::uint8_t* Utils::findSignature(void* moduleBase, const char* szSignature) noexcept
{
	using bytes_t = std::vector<std::int32_t>;

	static const auto pattern_to_byte = [](const char* pattern) noexcept -> bytes_t
	{
		bytes_t bytes{};
		const auto start{ const_cast<char*>(pattern) };
		const auto end{ const_cast<char*>(pattern) + strlen(pattern) };

		for (auto current{ start }; current < end; ++current)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?')
				{
					++current;
				}

				bytes.push_back(-1);
			}
			else
			{
				bytes.push_back(strtoul(current, &current, 16));
			}
		}

		return bytes;
	};

	const auto dosHeader{ (PIMAGE_DOS_HEADER)moduleBase };
	const auto ntHeaders{ (PIMAGE_NT_HEADERS)((std::uint8_t*)moduleBase + dosHeader->e_lfanew) };
	const auto textSection{ IMAGE_FIRST_SECTION(ntHeaders) };

	const auto sizeOfImage{ textSection->SizeOfRawData };
	const auto patternBytes{ pattern_to_byte(szSignature) };
	const auto scanBytes{ reinterpret_cast<std::uint8_t*>(moduleBase) + textSection->VirtualAddress };

	const auto s{ patternBytes.size() };
	const auto d{ patternBytes.data() };

	MEMORY_BASIC_INFORMATION mbi{ 0 };
	std::uint8_t* next_check_address{ 0 };

	for (size_t i = 0; i < sizeOfImage - s; ++i)
	{
		bool found{ true };
		for (auto j{ 0ul }; j < s; ++j)
		{
			const auto current_address{ scanBytes + i + j };
			if (current_address >= next_check_address)
			{
				if (!::VirtualQuery(reinterpret_cast<void*>(current_address), &mbi, sizeof(mbi)))
				{
					break;
				}

				if (mbi.Protect == PAGE_NOACCESS)
				{
					i += ((std::uintptr_t(mbi.BaseAddress) + mbi.RegionSize) - (std::uintptr_t(scanBytes) + i));
					i--;
					found = false;
					break;
				}
				else
				{
					next_check_address = reinterpret_cast<std::uint8_t*>(mbi.BaseAddress) + mbi.RegionSize;
				}
			}

			if (scanBytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}
		}

		if (found)
		{
			return &scanBytes[i];
		}
	}

	return nullptr;
}

std::uintptr_t Utils::findPatternInMemory(HANDLE hPorcess, std::uintptr_t start, size_t size, const std::vector<std::uint8_t>& pattern) noexcept
{
	std::uint8_t buffer[0x1000] = { 0 };
	std::uintptr_t endAddr = start + size;
	size_t patternLen = pattern.size();
	for (std::uintptr_t readAddr = start; readAddr <= endAddr - 0x1000; readAddr += (0x1000 - patternLen))
	{
		memset(buffer, 0, sizeof(buffer));
		BOOL r = ::ReadProcessMemory(hPorcess, (LPCVOID)readAddr, buffer, sizeof(buffer), nullptr);
		if (r == 0)
		{
			continue;
		}

		for (size_t i = 0; i < 0x1000 - patternLen; ++i)
		{
			bool found = true;
			for (size_t j = 0, k = i; j < patternLen; ++j, ++k)
			{
				if (pattern[j] == '?')
				{
					continue;
				}

				if (pattern[j] != buffer[k])
				{
					found = false;
					break;
				}
			}

			if (found)
			{
				return std::uintptr_t(readAddr + i);
			}
		}
	}

	return 0;
}

HWND Utils::findWindowByPid(DWORD pid, const char* className)
{
    HWND hCurWnd = GetTopWindow(0);
    while (hCurWnd != NULL)
    {
        DWORD cur_pid;
        DWORD dwTheardId = GetWindowThreadProcessId(hCurWnd, &cur_pid);

        if (cur_pid == pid)
        {
			if (className == nullptr)
			{
				return hCurWnd;
			}

            if (IsWindowVisible(hCurWnd) != 0)
            {
                char szClassName[256];
                GetClassNameA(hCurWnd, szClassName, 256);
                if (strcmp(szClassName, className) == 0)
                {
                    return hCurWnd;
                }
            }
        }

        hCurWnd = GetNextWindow(hCurWnd, GW_HWNDNEXT);
    }

    return nullptr;
}

bool Utils::hideThread(HANDLE hThread)
{
    __try
    {
        using FnSetInformationThread = NTSTATUS(NTAPI*)(HANDLE, UINT, PVOID, ULONG);
        const auto NtSetInformationThread{ reinterpret_cast<FnSetInformationThread>(::GetProcAddress(::GetModuleHandle(L"ntdll.dll"), "NtSetInformationThread")) };
        if (NtSetInformationThread == nullptr)
        {
            return false;
        }

        const auto status = NtSetInformationThread(hThread, 0x11u, NULL, 0ul);
        if (status == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    __except (1)
    {
        return false;
    }
}