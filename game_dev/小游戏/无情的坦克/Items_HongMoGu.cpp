#include "Items_HongMoGu.h"
CHongMoGU :: CHongMoGU(std::string s,int de,int att,int hp,bool apper)
	:
	m_sName(s),
	m_iDefence(de),
	m_iAttack(att),
	m_iHp(hp),
	m_bDisapper(apper)
{
}
CHongMoGU :: ~CHongMoGU()
{
}
int CHongMoGU :: GetDefence()
{
	return this->m_iDefence;
}
int CHongMoGU :: GetAtt()
{
	return this->m_iAttack;
}
int CHongMoGU :: GetHp()
{
	return this->m_iHp;
}
std::string  CHongMoGU :: GetName()
{
	return this->m_sName;
}
void CHongMoGU :: SetRect(RECT r)
{
	this->m_rRect = r;
}
void CHongMoGU :: SetApper(bool apper)
{
	this->m_bDisapper = apper;
}
bool CHongMoGU :: GetApper()
{
	return this-> m_bDisapper;
}
RECT CHongMoGU :: GetRect()
{
	return this->m_rRect;
}