#include <windows.h>
#include <thread>
#include <clocale>
#include "hook/dx11hook.h"
#include "log.h"
#include "imgui/imgui.h"

int main()
{
    int a = 10;
    int* p = &a;

    LOG_ENABLE_CONSOLE();
    LOG_INFO("dwad:{:p}:{:d}", (void*)p, a);

    std::getchar();
    return 0;
}
