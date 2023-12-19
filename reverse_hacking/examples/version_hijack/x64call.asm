extern g_call:far

.code

GetFileVersionInfoA proc
jmp qword ptr [g_call + 8 * 1];jump real addreess
GetFileVersionInfoA endp

GetFileVersionInfoByHandle proc
jmp qword ptr [g_call + 8 * 2]
GetFileVersionInfoByHandle endp

GetFileVersionInfoExA proc
jmp qword ptr [g_call + 8 * 3]
GetFileVersionInfoExA endp

GetFileVersionInfoExW proc
jmp qword ptr [g_call + 8 * 4]
GetFileVersionInfoExW endp

GetFileVersionInfoSizeA proc
jmp qword ptr [g_call + 8 * 5]
GetFileVersionInfoSizeA endp

GetFileVersionInfoSizeExA proc
jmp qword ptr [g_call + 8 * 6]
GetFileVersionInfoSizeExA endp

GetFileVersionInfoSizeExW proc
jmp qword ptr [g_call + 8 * 7]
GetFileVersionInfoSizeExW endp

GetFileVersionInfoSizeW proc
jmp qword ptr [g_call + 8 * 8]
GetFileVersionInfoSizeW endp

GetFileVersionInfoW proc
jmp qword ptr [g_call + 8 * 9]
GetFileVersionInfoW endp

VerFindFileA proc
jmp qword ptr [g_call + 8 * 10]
VerFindFileA endp

VerFindFileW proc
jmp qword ptr [g_call + 8 * 11]
VerFindFileW endp

VerInstallFileA proc
jmp qword ptr [g_call + 8 * 12]
VerInstallFileA endp

VerInstallFileW proc
jmp qword ptr [g_call + 8 * 13]
VerInstallFileW endp

VerLanguageNameA proc
jmp qword ptr [g_call + 8 * 14]
VerLanguageNameA endp

VerLanguageNameW proc
jmp qword ptr [g_call + 8 * 15]
VerLanguageNameW endp

VerQueryValueA proc
jmp qword ptr [g_call + 8 * 16]
VerQueryValueA endp

VerQueryValueW proc
jmp qword ptr [g_call + 8 * 17]
VerQueryValueW endp


end