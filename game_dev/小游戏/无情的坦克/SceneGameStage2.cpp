#include "SceneGameStage2.h"
#include "GameEngine.h"
#include "BmpButtonUI.h"
#include "ButtonUI.h"
#include "Player.h"
#include "GameLogic.h"
//CGameLogic stage2;

CGameLogic* CSceneGameStage2:: GetLogicObject()
{
	return &stage2;
}
//场景2的初始化
void CSceneGameStage2::Init()
{
	SetEnterChange("入2");
	SetQuitChange("出2");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("玩家射击","sound\\sound194.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("游戏胜利","sound\\游戏胜利.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("敌人射击","sound\\sound195.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("爆炸","sound\\sound220.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("玩家死亡","sound\\死亡.mp3");
	LoadUI("存档",new CBmpButtonUI(
		"pic\\存档1.bmp",
		"pic\\存档2.bmp",
		"pic\\存档3.bmp",
		"pic\\存档4.bmp",
		700,30,66,38,true,RGB(255,255,255)));
	m_bIsRead = true;
}
//进入场景
void CSceneGameStage2::Enter()
{
	//是否是通过读取文件进入的
	if(m_bIsRead)
	{
		this->m_iStage = 2;
		stage2.GameInit();
	}
	this->m_bGameVictor = false;
	this->m_bGameEnd = true;
	m_bBoFangshibai = false;
	m_bBoFangWin = false;
	this->m_iTime = 0;
	stage2.SetStage(2);
	CGameEngine::GetGE()->GetAM()->PlayLoopAudio("背景音乐");
}
//绘制地图元素的函数
void CSceneGameStage2::OutputRun()
{
	stage2.Paint();
	if(!m_bGameEnd)
	{
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
		"pic\\游戏结束.bmp",
		100, 100, 486, 227,
		0, 0,486,227);
		if(!m_bBoFangshibai)
		{
			CGameEngine::GetGE()->GetAM()->StopLoopAudio("背景音乐");
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("玩家死亡");
			m_bBoFangshibai = true;
		}
	}
	if(m_bGameVictor)
	{
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
		"pic\\游戏胜利.bmp",
		100, 100, 486, 227,
		0, 0,403,232);
		if(!m_bBoFangWin)
		{
			CGameEngine::GetGE()->GetAM()->StopLoopAudio("背景音乐");
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("游戏胜利");
			m_bBoFangWin = true;
		}
	}
	if(m_iTime < 15)
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
		"pic\\第二关.bmp",200, 100, 294, 106,0, 0,294,106);
}
//当前场景逻辑方面的函数
void CSceneGameStage2::LogicInputRun()
{
	if(m_iTime<15)
	{
		m_iTime ++;
		if(m_iTime == 15)
			m_iTime =15;
	}
	//判断玩家生命，若小于0即结束游戏
	if(stage2.GetPlayerLife() <=0)
		m_bGameEnd = false;
	//游戏是否胜利
	if(stage2.GetEnemyNum()<=0)
		m_bGameVictor = true ;
	if(m_bGameEnd && !m_bGameVictor)
	{
		stage2.PlayerMove();
		stage2.GameRun();
	}
	else
	{
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_T) == _KS_DC)
			CGameEngine::GetGE()->ExitGame();
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_I) == _KS_DC)
			CGameEngine::GetGE()->SetCurScene("游戏开始");
	}
	if(m_bGameVictor)
	{
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_T) == _KS_DC)
			CGameEngine::GetGE()->ExitGame();
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_I) == _KS_DC)
			CGameEngine::GetGE()->SetCurScene("游戏开始");
	}
	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_T) == _KS_DC)
		CGameEngine::GetGE()->ExitGame();
}
//UI消息
void CSceneGameStage2::OnUIMsg(const char* id, int UIMSG)
{
	if (UIMSG == _BUTTON_CLICK)
	{
		if (strcmp(id, "存档") == 0)
		{
			stage2.WriteGame();
		}
	}
}
//设置是否是读档进的游戏
void CSceneGameStage2:: SetRead(bool set)
{
	this->m_bIsRead = set;
}
//退出场景
void CSceneGameStage2::Quit()
{
	CGameEngine::GetGE()->GetAM()->StopLoopAudio("退出场景");
}