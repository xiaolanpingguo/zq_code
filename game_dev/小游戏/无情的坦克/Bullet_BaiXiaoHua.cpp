#include "Bullet_BaiXiaoHua.h"
//狗仔
CBullet_BaiXiaoHua :: CBullet_BaiXiaoHua(POINT p,char dir,int att,char type)
	:
	m_pBulletPoint(p),
	m_cDir(dir),
	m_iAttack(att),
	m_cBulletType(type)
{
}
CBullet_BaiXiaoHua ::	~CBullet_BaiXiaoHua()
{

}
//获取攻击
int CBullet_BaiXiaoHua :: GetAttack()
{
	return this->m_iAttack;
}
//获取子弹位置
POINT CBullet_BaiXiaoHua :: GetBulletPoint()
{
	return this->m_pBulletPoint;
}
//子弹运行，超过边界返回FALSE
bool CBullet_BaiXiaoHua :: BulletRun(int bianjie_R,int bianjie_D)
{
	if(this->m_cDir == _DIR_UP_	)
		this->m_pBulletPoint.y -= BULLET_SPEED ;
	if(this->m_cDir == _DIR_DOWN_	)
		this->m_pBulletPoint.y += BULLET_SPEED ;
	if(this->m_cDir == _DIR_LEFT_	)
		this->m_pBulletPoint.x -= BULLET_SPEED ;
	if(this->m_cDir == _DIR_RIGHT_	)
		this->m_pBulletPoint.x += BULLET_SPEED ;
	if(this->m_pBulletPoint.x >bianjie_R || this->m_pBulletPoint.x <0
		|| this->m_pBulletPoint.y <80 || this->m_pBulletPoint.y > bianjie_D)
		return false;
	return true;
}
