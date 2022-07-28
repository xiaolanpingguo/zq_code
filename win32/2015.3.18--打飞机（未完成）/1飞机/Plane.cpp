#include "Plane.h"

CPlane::CPlane()
{
}
CPlane::~CPlane()
{}

//初始化函数，初始化飞机的位置，血量
void CPlane::Init(POINT p)
{}
//设置飞机位置，主要用于英雄
void CPlane::SetPlanePoint(POINT p)
{}

//飞机运行，主要用于敌机
bool CPlane::Run(int right,int bottom,std::vector<CBullet*> vBullet)
{
	return true;
}

//设置血量
void CPlane::SetHP(int hp)
{}

//获取血量
int CPlane::GetHP()
{
	return m_iHp;
}

//获取位置
POINT CPlane::GetPoint()
{
	return m_Point;
}

//攻击
void CPlane::Attack(POINT p,std::vector<CBullet*> vBullet)
{}