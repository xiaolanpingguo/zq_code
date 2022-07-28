#include "SceneGameBegin.h"
#include "GameEngine.h"
#include "ButtonUI.h"
#include "BmpButtonUI.h"
#include "SceneGameStage1.h"
#include "SceneGameStage2.h"
//场景初始化
void CSceneGameBegin::Init()
{
	CGameEngine::GetGE()->GetGO()->LoadDirectory("pic");
	SetEnterChange("入2");
	SetQuitChange("出2");
	LoadUI("开始游戏",new CBmpButtonUI(
		"pic\\开始游戏1.bmp",
		"pic\\开始游戏2.bmp",
		"pic\\开始游戏3.bmp",
		"pic\\开始游戏4.bmp",
		320,250,100,40,true,RGB(255,255,255)));
	LoadUI("游戏说明",new CBmpButtonUI(
		"pic\\游戏说明1.bmp",
		"pic\\游戏说明2.bmp",
		"pic\\游戏说明3.bmp",
		"pic\\游戏说明4.bmp",
		320,310,100,40,true,RGB(255,255,255)));
	LoadUI("退出游戏",new CBmpButtonUI(
		"pic\\退出游戏1.bmp",
		"pic\\退出游戏2.bmp",
		"pic\\退出游戏3.bmp",
		"pic\\退出游戏4.bmp",
		320,370,100,40,true,RGB(255,255,255)));
	LoadUI("读档",new CBmpButtonUI(
		"pic\\读档1.bmp",
		"pic\\读档2.bmp",
		"pic\\读档3.bmp",
		"pic\\读档4.bmp",
		600,50,66,38,true,RGB(255,255,255)));
	LoadUI("确定",new CButtonUI("确定",230,400,100,30));
	GetUI("确定")->SetView(false);
	GetUI("确定")->SetAct(false);
	CGameEngine::GetGE()->GetAM()->PushLoopAudio("背景音乐","sound\\背景音乐.mp3");
}
//绘制信息
void CSceneGameBegin::OutputRun()
{
	CGameEngine::GetGE()->GetGO()->DrawBmp3(
		"pic\\开始界面.bmp",
		0, 0, 800, 600,
		0, 0,583,400);
	if(m_bJieShaoTu)
	{
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
			"pic\\介绍图.bmp",150, 150, 162, 284,0, 0,162,320);
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
			"pic\\确定.bmp",260, 150, 50, 50,0, 0,66,38);

	}
}

void CSceneGameBegin::LogicInputRun()
{
}
//进入场景
void CSceneGameBegin::Enter()
{
	CGameEngine::GetGE()->GetAM()->PlayLoopAudio("背景音乐");
	this->m_bJieShaoTu = false;
}
//推出场景
void CSceneGameBegin::Quit()
{
	
}
//UI消息
void CSceneGameBegin::OnUIMsg(const char* id, int UIMSG)
{
	if (UIMSG == _BUTTON_CLICK)
	{
		if (strcmp(id, "开始游戏") == 0)
		{
			CGameEngine::GetGE()->GetScene("关卡1")->SetRead(true);
			CGameEngine::GetGE()->GetScene("关卡2")->SetRead(true);
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("e1");
			CGameEngine::GetGE()->SetCurScene("关卡1");
		}
		else if (strcmp(id, "退出游戏") == 0)
			CGameEngine::GetGE()->ExitGame();
		else if (strcmp(id, "游戏说明") == 0)
		{
			this->m_bJieShaoTu = true;
			GetUI("确定")->SetView(true);
			GetUI("确定")->SetAct(true);
		}
		else if (strcmp(id, "确定") == 0)
		{
			this->m_bJieShaoTu = false;
			GetUI("确定")->SetView(false);
			GetUI("确定")->SetAct(false);
		}
		else if (strcmp(id, "读档") == 0)
		{
			if(CGameEngine::GetGE()->GetRF()->Open("save\\save1"))
			{
				int stage;
				int BianJieR;
				int BianJieD;
				int Score;
				int ItemsNum;
				int EnemyNum;
				int att;
				int dir;
				int life;
				POINT p;
				CGameEngine::GetGE()->GetRF()->ReadMemory(&stage,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&BianJieD,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&BianJieR,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&EnemyNum,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&Score,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&ItemsNum,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&att,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&dir,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&life,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&p,sizeof(POINT));
				//读取文件并设置相应关卡
				if(stage == 1)
				{
					CGameEngine::GetGE()->GetScene("关卡1")->GetLogicObject()->SetBianjieD(BianJieD);
					CGameEngine::GetGE()->GetScene("关卡1")->GetLogicObject()->SetBianjieR(BianJieR);
					CGameEngine::GetGE()->GetScene("关卡1")->GetLogicObject()->SetEnemyNum(EnemyNum);
					CGameEngine::GetGE()->GetScene("关卡1")->GetLogicObject()->SetScore(Score);
					CGameEngine::GetGE()->GetScene("关卡1")->GetLogicObject()->SetItemsNum(ItemsNum);
					CGameEngine::GetGE()->GetScene("关卡1")->GetLogicObject()->SetPlayerAtt(att);
					CGameEngine::GetGE()->GetScene("关卡1")->GetLogicObject()->SetPlayerDir(dir);
					CGameEngine::GetGE()->GetScene("关卡1")->GetLogicObject()->SetPlayerLife(life);
					CGameEngine::GetGE()->GetScene("关卡1")->GetLogicObject()->SetPlayerPoint(p);
					CGameEngine::GetGE()->GetScene("关卡1")->SetRead(false);
					CGameEngine::GetGE()->SetCurScene("关卡1");
				}
				if(stage == 2)
				{
					CGameEngine::GetGE()->GetScene("关卡2")->GetLogicObject()->SetBianjieD(BianJieD);
					CGameEngine::GetGE()->GetScene("关卡2")->GetLogicObject()->SetBianjieR(BianJieR);
					CGameEngine::GetGE()->GetScene("关卡2")->GetLogicObject()->SetEnemyNum(EnemyNum);
					CGameEngine::GetGE()->GetScene("关卡2")->GetLogicObject()->SetScore(Score);
					CGameEngine::GetGE()->GetScene("关卡2")->GetLogicObject()->SetItemsNum(ItemsNum);
					CGameEngine::GetGE()->GetScene("关卡2")->GetLogicObject()->SetPlayerAtt(att);
					CGameEngine::GetGE()->GetScene("关卡2")->GetLogicObject()->SetPlayerDir(dir);
					CGameEngine::GetGE()->GetScene("关卡2")->GetLogicObject()->SetPlayerLife(life);
					CGameEngine::GetGE()->GetScene("关卡2")->GetLogicObject()->SetPlayerPoint(p);
					CGameEngine::GetGE()->GetScene("关卡2")->SetRead(false);
					CGameEngine::GetGE()->SetCurScene("关卡2");
				}
			}
			
		}
	}	
}
