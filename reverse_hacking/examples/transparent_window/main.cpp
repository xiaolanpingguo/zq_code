#include <windows.h>
#include <thread>
#include <clocale>
#include "r3/log.h"
#include "r3/imgui/imgui.h"
#include "r3/render_manager.h"


RenderManager g_renderManager;
void gameDraw()
{
    static bool showMenu = true;
    if (GetAsyncKeyState(VK_INSERT) & 1)
    {
        showMenu = !showMenu;
    }
    if (showMenu)
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    g_renderManager.drawStrokeText(50, 50, IM_COL32(255, 0, 0, 255), "StrokeText");
    g_renderManager.drawNewText(80, 80, IM_COL32(255, 0, 0, 255), "NewText");
    g_renderManager.drawRect(200, 200, 100, 100, IM_COL32(255, 0, 0, 255));
    g_renderManager.drawFilledRect(200, 300, 50, 50, IM_COL32(255, 0, 0, 255));
    g_renderManager.drawCircleFilled(300, 300, 20, IM_COL32(255, 0, 0, 255));
    g_renderManager.drawCircle(400, 400, 20, IM_COL32(255, 0, 0, 255));
    g_renderManager.drawTriangle(250, 200, 200, 300, 300, 300, IM_COL32(255, 0, 255, 255));
    g_renderManager.drawTriangleFilled(300, 300, 100, 400, 400, 400, IM_COL32(255, 0, 255, 255));
    g_renderManager.drawLine(200, 200, 100, 100, IM_COL32(255, 0, 0, 255));
}

int main()
{
    RenderConfig config
    {
        gameDraw, 800, 600, true, L"test"
    };

    g_renderManager.init(config);

    while (1)
    {
        g_renderManager.render();
    }

    return 0;
}
