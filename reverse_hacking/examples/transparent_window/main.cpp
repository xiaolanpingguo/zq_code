#include <windows.h>
#include <thread>
#include <clocale>
#include "r3/log.h"
#include "r3/imgui/imgui.h"
#include "r3/application.h"
#include "r3/render_manager.h"


struct TestApp : public Application
{
	void drawGame()
	{
		static bool showMenu = true;
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			showMenu = !showMenu;
		}
		::ShowCursor(showMenu);
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

		m_renderManager->drawNewText(80, 80, IM_COL32(255, 0, 0, 255), "NewText");
		m_renderManager->drawRect(200, 200, 100, 100, IM_COL32(255, 0, 0, 255));
		m_renderManager->drawLine(200, 200, 100, 100, IM_COL32(255, 0, 0, 255));
	}

	bool init()
	{
		return Application::init();
	}

	void run()
	{
		Application::run();
	}

	ApplicationConfig getApplicationConfig() override
	{
		return ApplicationConfig
		{
			std::bind(&TestApp::drawGame, this), 800, 600, L"test", true,
		};
	}

	void update() override
	{
	}
};
int main()
{
	TestApp app;
	app.init();
	app.run();

    return 0;
}
