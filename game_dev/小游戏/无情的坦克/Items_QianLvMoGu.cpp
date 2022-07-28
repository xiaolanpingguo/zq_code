#include "Items_QianLvMoGu.h"
CQianLvMoGU :: CQianLvMoGU(std::string s,int de,int att,int hp,bool apper)
	:
	m_sName(s),
	m_iDefence(de),
	m_iAttack(att),
	m_iHp(hp),
	m_bDisapper(apper)
{
}
CQianLvMoGU :: ~CQianLvMoGU()
{
}
int CQianLvMoGU :: GetDefence()
{
	return this->m_iDefence;
}
int CQianLvMoGU :: GetAtt()
{
	return this->m_iAttack;
}
int CQianLvMoGU :: GetHp()
{
	return this->m_iHp;
}
std::string  CQianLvMoGU :: GetName()
{
	return this->m_sName;
}
void CQianLvMoGU :: SetRect(RECT r)
{
	this->m_rRect = r;
}
void CQianLvMoGU :: SetApper(bool apper)
{
	this->m_bDisapper = apper;
}
bool CQianLvMoGU :: GetApper()
{
	return this-> m_bDisapper;
}
RECT CQianLvMoGU :: GetRect()
{
	return this->m_rRect;
}