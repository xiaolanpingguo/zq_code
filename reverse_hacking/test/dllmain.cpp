#include <windows.h>
#include <thread>
#include <clocale>
#include "hook/dx11hook.h"
#include "hook/dx9hook.h"
#include "hook/dx12hook.h"
#include "log.h"
#include "imgui/imgui.h"


//#define DX9_HOOK
#define DX11_HOOK
//#define DX12_HOOK

#ifdef DX9_HOOK

void DrawImGui()
{
    static bool showMenu = true;
    if (GetAsyncKeyState(VK_INSERT) & 1)
    {
        showMenu = !showMenu;
    }

    if (!showMenu)
    {
        return;
    }

    ImGui::Begin("ImGui dx9 test", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);
    ImGui::Spacing();

    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::End();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        // 当dll使用静态C运行时库进行链接不要使用该函数，因为此时dll需要DLL_THREAD_ATTACH 和DLL_THREAD_DETATCH通知才能发挥正常作用
       // DisableThreadLibraryCalls(hModule);

        LOG_ENABLE_CONSOLE();
        LOG_INFO("DLL_PROCESS_ATTACH: {}\n", (void*)hModule);

        static constexpr const char* WINDOWS_NAME = "test";
        HWND gameWindow = FindWindowA(0, WINDOWS_NAME);
        Dx9Hook::ConfigData data{ gameWindow, DrawImGui };
        Dx9Hook::start(data);
        break;
    }
    case DLL_PROCESS_DETACH:
    {
        LOG_INFO("DLL_PROCESS_DETACH: {}", (void*)hModule);
        break;
    }
    }

    return TRUE;
}

#endif

#ifdef DX11_HOOK

void DrawImGui()
{
    static bool showMenu = true;
    if (GetAsyncKeyState(VK_INSERT) & 1)
    {
        showMenu = !showMenu;
    }

    if (!showMenu)
    {
        return;
    }

    ImGui::Begin("ImGui dx11 test", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);
    ImGui::Spacing();

    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::End();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        // 当dll使用静态C运行时库进行链接不要使用该函数，因为此时dll需要DLL_THREAD_ATTACH 和DLL_THREAD_DETATCH通知才能发挥正常作用
       // DisableThreadLibraryCalls(hModule);

        LOG_ENABLE_CONSOLE();
        LOG_INFO("DLL_PROCESS_ATTACH: {}\n", (void*)hModule);

        static constexpr const char* WINDOWS_NAME = "test";
        HWND gameWindow = FindWindowA(0, WINDOWS_NAME);
        Dx11Hook::ConfigData data{ gameWindow, DrawImGui };
        Dx11Hook::start(data);
        break;
    }
    case DLL_PROCESS_DETACH:
    { 
        LOG_INFO("DLL_PROCESS_DETACH: {}", (void*)hModule);
        break;
    }
    }

    return TRUE;
}

#endif

#ifdef DX12_HOOK

void DrawImGui()
{
    static bool showMenu = true;
    if (GetAsyncKeyState(VK_INSERT) & 1)
    {
        showMenu = !showMenu;
    }

    if (!showMenu)
    {
        return;
    }

   // ImGui::GetIO().MouseDrawCursor = showMenu;

    ImGui::Begin("ImGui dx12 test", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);
    ImGui::Spacing();

    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Spacing();
    ImGui::End();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        // 当dll使用静态C运行时库进行链接不要使用该函数，因为此时dll需要DLL_THREAD_ATTACH 和DLL_THREAD_DETATCH通知才能发挥正常作用
       // DisableThreadLibraryCalls(hModule);

        LOG_ENABLE_CONSOLE();
        LOG_INFO("DLL_PROCESS_ATTACH: {}\n", (void*)hModule);

        static constexpr const char* WINDOWS_NAME = "test";
        HWND gameWindow = FindWindowA(0, WINDOWS_NAME);
        Dx12Hook::ConfigData data{ gameWindow, DrawImGui };
        Dx12Hook::start(data);
        break;
    }
    case DLL_PROCESS_DETACH:
    {
        LOG_INFO("DLL_PROCESS_DETACH: {}", (void*)hModule);
        break;
    }
    }

    return TRUE;
}

#endif

