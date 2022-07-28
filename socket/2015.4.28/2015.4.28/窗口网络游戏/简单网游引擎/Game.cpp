#include "Game.h"
#include "GameEngine.h"
#include "TextButton.h"
#include "Begin.h"
#include <iostream>
#include <map>
#include <string>
 
void CGame::Init()
{
	
}

void CGame::Enter()
{

}

void CGame::OutputRun()
{
	CGameEngine::GetGE()->GetOutput()->DrawRectangle2(
		0, 0, 640, 480, RGB(0, 255, 0), RGB(0, 255, 0));

	//绘制所有玩家
	CBegin* pBegin = (CBegin*)CGameEngine::GetGE()->GetScene("开始场景");
	int gw = 640 / 32;
	int gh = 480 / 32;
	for (std::map<std::string, POINT>::iterator it = pBegin->all_player.begin(); it != pBegin->all_player.end(); ++it)
	{
		if (strcmp(pBegin->m_Nick_Name.c_str(), it->first.c_str()) == 0)
		{
			CGameEngine::GetGE()->GetOutput()->DrawEllipse2(
				it->second.x * gw, it->second.y * gh,
				it->second.x * gw + gw, it->second.y * gh + gh,
				RGB(255, 0, 0),
				RGB(255, 0, 0));
		}
		else
		{
			CGameEngine::GetGE()->GetOutput()->DrawEllipse2(
				it->second.x * gw, it->second.y * gh,
				it->second.x * gw + gw, it->second.y * gh + gh,
				RGB(255, 0, 0),
				RGB(255, 255, 0));
		}
	}
}

void CGame::InputRun()
{

}

void CGame::LogicRun()
{

}

void CGame::Quit()
{

}

void CGame::OnUIMessage(int message, const char* id)
{

}

void CGame::OnNetEvent(_TC_NET_EVENT* ptne)
{

}