#include "Items_ShenLvMoGu.h"
CShenLvMoGU :: CShenLvMoGU(std::string s,int de,int att,int hp,bool apper)
	:
	m_sName(s),
	m_iDefence(de),
	m_iAttack(att),
	m_iHp(hp),
	m_bDisapper(apper)
{
}
CShenLvMoGU :: ~CShenLvMoGU()
{
}
int CShenLvMoGU :: GetDefence()
{
	return this->m_iDefence;
}
int CShenLvMoGU :: GetAtt()
{
	return this->m_iAttack;
}
int CShenLvMoGU :: GetHp()
{
	return this->m_iHp;
}
std::string  CShenLvMoGU :: GetName()
{
	return this->m_sName;
}
void CShenLvMoGU :: SetRect(RECT r)
{
	this->m_rRect = r;
}
void CShenLvMoGU :: SetApper(bool apper)
{
	this->m_bDisapper = apper;
}
bool CShenLvMoGU :: GetApper()
{
	return this-> m_bDisapper;
}
RECT CShenLvMoGU :: GetRect()
{
	return this->m_rRect;
}