#include "Boom_Player_Enemy.h"
CBoom_Player_Enemy :: CBoom_Player_Enemy(RECT r,int time)
:
m_rRect(r),
m_iTime(time),
CBoom(r,time)
{
}
CBoom_Player_Enemy ::	~CBoom_Player_Enemy()
{
}
void CBoom_Player_Enemy :: Paint()
{
	CGameEngine::GetGE()->GetGO()->DrawBmp3(
				"pic\\boom1.bmp",m_rRect.left,m_rRect.top, 40, 40,
				m_iTime*54, 0,54,40,RGB(0,0,0));
}
bool CBoom_Player_Enemy :: Run()
{
	if(m_iTime == 9)
		return false;
	else
		m_iTime ++;
	return true;
}