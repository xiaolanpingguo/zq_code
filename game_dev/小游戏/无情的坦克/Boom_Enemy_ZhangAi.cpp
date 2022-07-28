#include "Boom_Enemy_ZhangAi.h"
CBoom_Enemy_ZhangAi :: CBoom_Enemy_ZhangAi(RECT r,int time)
:
m_rRect(r),
m_iTime(time),
CBoom(r,time)
{
}
CBoom_Enemy_ZhangAi ::	~CBoom_Enemy_ZhangAi()
{
}
void CBoom_Enemy_ZhangAi :: Paint()
{
	CGameEngine::GetGE()->GetGO()->DrawBmp3(
				"pic\\boom.bmp",m_rRect.left,m_rRect.top, 40, 40,
				m_iTime*40, 0,40,40);
}
bool CBoom_Enemy_ZhangAi :: Run()
{
	if(m_iTime == 8)
		return false;
	else
		m_iTime ++;
	return true;
}