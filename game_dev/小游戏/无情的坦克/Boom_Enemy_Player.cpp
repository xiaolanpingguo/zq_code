#include "Boom_Enemy_Player.h"
CBoom_Enemy_Player :: CBoom_Enemy_Player(RECT r,int time)
:
m_rRect(r),
m_iTime(time),
CBoom(r,time)
{
}
CBoom_Enemy_Player ::	~CBoom_Enemy_Player()
{
}
void CBoom_Enemy_Player :: Paint()
{
	CGameEngine::GetGE()->GetGO()->DrawBmp3(
				"pic\\boom2.bmp",m_rRect.left,m_rRect.top, 40, 40,
				m_iTime*50, 0,50,108,RGB(255,255,255));
}
bool CBoom_Enemy_Player :: Run()
{
	if(m_iTime == 8)
		return false;
	else
		m_iTime ++;
	return true;
}