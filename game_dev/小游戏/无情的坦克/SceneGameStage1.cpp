#include "SceneGameStage1.h"
#include "GameEngine.h"
#include "BmpButtonUI.h"
#include "ButtonUI.h"
#include "Player.h"
#include "GameLogic.h"

CGameLogic* CSceneGameStage1:: GetLogicObject()
{
	return &stage1;
}
//场景初始化
void CSceneGameStage1::Init()
{
	SetEnterChange("入2");
	SetQuitChange("出2");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("玩家射击","sound\\sound194.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("敌人射击","sound\\sound195.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("爆炸","sound\\sound220.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("玩家死亡","sound\\死亡.mp3");
	LoadUI("存档",new CBmpButtonUI(
		"pic\\存档1.bmp",
		"pic\\存档2.bmp",
		"pic\\存档3.bmp",
		"pic\\存档4.bmp",
		700,30,66,38,true,RGB(255,255,255)));
	this->m_bIsRead = true;
}
//进入场景
void CSceneGameStage1::Enter()
{
	this->m_bBoFang = false;
	this->m_bGameEnd = true;
	if(this->m_bIsRead)
	{
		this->m_iStage = 1;
		stage1.GameInit();
	}
	stage1.SetMapStage1();
	stage1.SetStage(1);
	this->m_iTime = 0;
	CGameEngine::GetGE()->GetAM()->PlayLoopAudio("背景音乐");

}
//绘制地图元素的函数
void CSceneGameStage1::OutputRun()
{
	//绘制游戏元素
	stage1.Paint();
	//是否结束游戏
	if(!m_bGameEnd)
	{
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
		"pic\\游戏结束.bmp",
		100, 100, 486, 227,
		0, 0,486,227);
		if(!m_bBoFang)
		{
			CGameEngine::GetGE()->GetAM()->StopLoopAudio("背景音乐");
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("玩家死亡");
			m_bBoFang = true;
		}
	}
	if(m_iTime < 15)
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
		"pic\\第一关.bmp",200, 100, 294, 106,0, 0,294,106);
	//按键控制，i继续游戏，t退出游戏
	
}
//当前场景逻辑方面的函数
void CSceneGameStage1::LogicInputRun()
{
	//绘制“第一关”这张图片
	if(m_iTime<15)
	{
		m_iTime ++;
		if(m_iTime == 15)
			m_iTime =15;
	}
	//玩家生命小于0，游戏结束
	if(stage1.GetPlayerLife() <=0)
	{
		m_bGameEnd = false;
		this->m_bIsRead = true;
	}
	if(m_bGameEnd)
	{
		stage1.PlayerMove();
		stage1.GameRun();
	}
	else
	{
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_T) == _KS_DC)
			CGameEngine::GetGE()->ExitGame();
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_I) == _KS_DC)
			CGameEngine::GetGE()->SetCurScene("游戏开始");
	}
	//敌人数目达到规定数目，进入第二关
	if(stage1.GetEnemyNum()<=0)
	{
		CGameEngine::GetGE()->SetCurScene("关卡2");
	}
	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_T) == _KS_DC)
		CGameEngine::GetGE()->ExitGame();
}

//退出场景
void CSceneGameStage1::Quit()
{

}
void CSceneGameStage1::OnUIMsg(const char* id, int UIMSG)
{
	if (UIMSG == _BUTTON_CLICK)
	{
		if (strcmp(id, "存档") == 0)
		{
			stage1.WriteGame();
		}
	}
}
void CSceneGameStage1:: SetRead(bool set)
{
	this->m_bIsRead = set;
}
bool CSceneGameStage1::GetSetRead()
{
	return this->m_bIsRead;
}