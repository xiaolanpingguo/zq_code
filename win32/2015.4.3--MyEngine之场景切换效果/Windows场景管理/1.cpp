#include "1.h"
#include "GameEngine.h"

void C1::Init()
{
	CGameEngine::GetGE()->GetGO()->LoadDirectory("pic");
	CGameEngine::GetGE()->GetGO()->LoadFont(
		"开始场景字体",
		30, 20, 400, false, false, false, "隶书");

	SetEnterChange("入2");
	SetQuitChange("出2");
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
	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_RETURN) == _KS_UC)
		CGameEngine::GetGE()->SetCurScene("游戏场景");

	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_ESC) == _KS_UC)
		CGameEngine::GetGE()->ExitGame();
}

