#include "GameLogo.h"
#include "GameEngine.h"
//场景初始化
void CGameLogo :: Init()
{
	this->m_iTime = 0;
	SetEnterChange("入2");
	SetQuitChange("出2");
	CGameEngine::GetGE()->GetAM()->PushLoopAudio("泡沫","sound\\泡沫.mp3");
}
//输出
void CGameLogo :: OutputRun()
{
	CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\界面logo.bmp",
		0, 0, 800, 600,0, 0,641,508);
}
//逻辑运行
void CGameLogo :: LogicInputRun()
{
	if(m_iTime == 20)
		CGameEngine::GetGE()->SetCurScene("游戏开始");
	m_iTime++;
}
//进入场景
void CGameLogo :: Enter()
{
	CGameEngine::GetGE()->GetAM()->PlayLoopAudio("泡沫");
}