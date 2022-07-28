#include "HeroPlane.h"
#include "HeroBullet.h"

CHeroPlane::CHeroPlane()
{}
CHeroPlane::~CHeroPlane()
{}

//初始化函数，初始化飞机的位置，血量
void CHeroPlane::Init(POINT p)
{
	this->m_Point = p;
	this->m_iHp = 100;
}

//设置飞机位置，主要用于英雄
void CHeroPlane::SetPlanePoint(POINT p)
{
	this->m_Point = p;
}

//设置血量
void CHeroPlane::SetHP(int hp)
{
	this->m_iHp = hp;
}

//获取血量
int CHeroPlane::GetHP()
{
	return this->m_iHp;
}

//获取位置
POINT CHeroPlane::GetPoint()
{
	return this->m_Point;
}

//攻击
void CHeroPlane::Attack(POINT p,std::vector<CBullet*>& vBullet)
{
	CBullet* bullet = new CHeroBullet;
	bullet->BulletInit(p,true);
	vBullet.push_back(bullet);
}