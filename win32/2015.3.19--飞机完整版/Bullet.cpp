#include "Bullet.h"

CBullet::CBullet()
{}
CBullet::~CBullet()
{}
//初始化参数为位置和方向
void CBullet::BulletInit(POINT point,bool dir)
{
}

//子弹运行，返回假则飞出边界该销毁
bool CBullet::BulletRun(int bianjie)
{
	return true;
}

//获取子弹位置
POINT CBullet::GetBulletPoint()
{
	return this->m_BulletPoint;
}