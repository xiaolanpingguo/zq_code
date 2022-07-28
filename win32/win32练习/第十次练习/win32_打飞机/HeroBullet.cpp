#include "HeroBullet.h"

CHeroBullet::CHeroBullet()
{}
CHeroBullet::~CHeroBullet()
{}
//初始化参数为位置和方向
void CHeroBullet::BulletInit(POINT point,bool dir)
{
	this->m_BulletPoint = point;
	this->m_bDirect = dir;
}

//子弹运行，返回假则飞出边界该销毁
bool CHeroBullet::BulletRun(int bianjie)
{
	if(this->m_bDirect)
		this->m_BulletPoint.y -= 5;
	else
		this->m_BulletPoint.y += 5;
	
	if((this->m_bDirect && this->m_BulletPoint.y < bianjie)
	||(!this->m_bDirect && this->m_BulletPoint.y > bianjie))
		return false;

	return true;
}

//获取子弹位置
POINT CHeroBullet::GetBulletPoint()
{
	return this->m_BulletPoint;
}