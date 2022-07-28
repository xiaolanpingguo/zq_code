#include "Items.h"
CItems :: CItems()
{

}
CItems ::  ~CItems()
{
}
int CItems :: GetDefence()
{
	return this->m_iDefence;
}

int CItems :: GetAtt()
{
	return this->m_iAttack;
}
int CItems :: GetHp()
{
	return this->m_iHp;
}
std::string  CItems :: GetName()
{
	return this->m_sName;
}
void CItems :: SetRect(RECT r)
{
	this->m_rRect = r;
}
void CItems :: SetApper(bool apper)
{
}
bool CItems :: GetApper()
{
	return this-> m_bDisapper;
}
RECT CItems :: GetRect()
{
	return this->m_rRect;
}