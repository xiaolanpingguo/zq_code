#include "GameRole.h"

//游戏角色初始化函数,x,y,r代表x坐标，y坐标，r角色类型
void CGameRole::Init(int x,int y,Role r)
{
	this->m_iX = x;
	this->m_iY = y;
	this->m_role = r;
}
//坐标设置函数
void CGameRole::SetZuoBiao(int x,int y)
{
	this->m_iX = x;
	this->m_iY = y;
}

//设置角色类型
void CGameRole::SetEnumRole(Role r)
{
	this->m_role = r;
}

//获取角色的X坐标
int CGameRole::GetZBX()
{
	return this->m_iX;
}

//获取角色的Y坐标
int CGameRole::GetZBY()
{
	return this->m_iY;
}

//获取角色类型
Role CGameRole::GetRole()
{
	return this->m_role;
}