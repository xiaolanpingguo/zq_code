#include <windows.h>
#include <thread>
#include <clocale>
#include "hook/dx11hook.h"
#include "log.h"
#include "imgui/imgui.h"

void DrawImGui()
{
    ImGui::Begin("ImGui D3D11", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);
    ImGui::Spacing();

    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    static bool bShowDemo = false;
    ImGui::Checkbox("Show Demo Window", &bShowDemo);

    ImGui::Spacing();
    ImGui::End();

    if (bShowDemo)
    {
        ImGui::ShowDemoWindow(&bShowDemo);
    }
}

static DWORD WINAPI Start(LPVOID)
{
    HWND gameWindow = FindWindowA(0, "test");
    Dx11Hook::ConfigData data{ gameWindow, DrawImGui };
    Dx11Hook::start(data);
    return 0;
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
        LOG_INFO("DLL_PROCESS_ATTACH: {:x}", (std::uintptr_t)hModule);

        std::thread thr(&Start, nullptr);
        thr.detach();
        break;
    }
    case DLL_PROCESS_DETACH:
    { 
        Dx11Hook::shutdown();
        LOG_INFO("DLL_PROCESS_DETACH: {:x}", (std::uintptr_t)hModule);
        Sleep(1500);
        break;
    }
    }

    return TRUE;
}