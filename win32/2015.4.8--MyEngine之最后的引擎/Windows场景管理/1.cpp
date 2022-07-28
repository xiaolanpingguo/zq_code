#include "1.h"
#include "GameEngine.h"
#include "ButtonUI.h"
#include "EditUI.h"
#include "SelectUI.h"
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

	GetUI("结束按钮")->SetAct(false);

	LoadUI("编辑框1",new CEditUI(0,"123abc",150,200,200,80));
	LoadUI("编辑框2",new CEditUI(16,0,150,300,200,60));

	LoadUI("选择1",new CSelectUI("音乐",0,255,CGameEngine::GetGE()->GetAM()->GetLoopVolume(),150,100,200,60));
	LoadUI("选择2",new CSelectUI("音效",0,255,CGameEngine::GetGE()->GetAM()->GetOnceVolume(),400,100,160,40));

	CGameEngine::GetGE()->GetAM()->PushLoopAudio("m1","sound\\m1.mp3");
	CGameEngine::GetGE()->GetAM()->PushLoopAudio("m2","sound\\m2.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("e1","sound\\e1.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("e2","sound\\e2.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("e3","sound\\e3.mp3");
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
		{
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("e1");
			CGameEngine::GetGE()->SetCurScene("游戏场景");
		}
		else if (strcmp(id, "结束按钮") == 0)
			CGameEngine::GetGE()->ExitGame();
	}
	else if(UIMSG == _SELECT_NUM_CHANGE)
	{
		if(strcmp(id,"选择1") == 0)
		{
			int cur = ((CSelectUI*)GetUI("选择1"))->GetCur();
			CGameEngine::GetGE()->GetAM()->SetLoopVolume(cur);
		}
		else if(strcmp(id,"选择2") == 0)
		{
			int cur = ((CSelectUI*)GetUI("选择2"))->GetCur();
			CGameEngine::GetGE()->GetAM()->SetLoopVolume(cur);
		}
	}
}

void C1::Enter()
{
	CGameEngine::GetGE()->GetAM()->PlayLoopAudio("m1");
}
void C1::Quit()
{
	CGameEngine::GetGE()->GetAM()->StopLoopAudio("m1");
}
