#include "1.h"
#include "GameEngine.h"
#include "ButtonUI.h"

void C1::Init()
{
	CGameEngine::GetGE()->GetGO()->LoadDirectory("pic");
	CGameEngine::GetGE()->GetGO()->LoadFont(
		"开始场景字体",
		30, 20, 400, false, false, false, "隶书");

	SetEnterChange("入4");
	SetQuitChange("出4");

	LoadUI("开始按钮", new CButtonUI("Start", 0, 0, 100, 30));
	LoadUI("结束按钮", new CButtonUI("Exit", 0, 200, 100, 30));
}

void C1::OutputRun()
{
	CGameEngine::GetGE()->GetGO()->DrawBmp2(
		"pic\\Bliss.bmp",
		0, 0, 640, 480,
		0, 0);

	CGameEngine::GetGE()->GetGO()->DrawString1(
		"开始场景字体", 0, 0, "按回车进入游戏", RGB(255, 0, 0));

	CGameEngine::GetGE()->GetGO()->DrawString1(
		"开始场景字体", 0, 50, "按ESC退出游戏", RGB(255, 0, 255));
}

void C1::LogicInputRun()
{
}

void C1::OnUIMsg(const char* id, int UIMSG)
{
	if (UIMSG == _BUTTON_CLICK)
	{
		if (strcmp(id, "开始按钮") == 0)
			CGameEngine::GetGE()->SetCurScene("游戏场景");
		else if (strcmp(id, "结束按钮") == 0)
			CGameEngine::GetGE()->ExitGame();
	}
}
