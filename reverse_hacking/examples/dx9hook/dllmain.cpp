#include <windows.h>
#include <thread>
#include <clocale>
#include "r3/hook/dx9hook.h"
#include "r3/log.h"
#include "r3/imgui/imgui.h"


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


