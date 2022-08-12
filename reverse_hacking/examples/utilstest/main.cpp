#include <windows.h>
#include <thread>
#include <clocale>
#include "r3/hook/dx11hook.h"
#include "r3/log.h"
#include "r3/imgui/imgui.h"

int main()
{
    int a = 10;
    int* p = &a;

    LOG_ENABLE_CONSOLE();
    LOG_INFO("dwad:{}:{:d}", (void*)p, a);

    std::getchar();
    return 0;
}
