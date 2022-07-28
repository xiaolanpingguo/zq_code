#include "Bullet_BaiXiaoGui.h"
CBullet_BaiXiaoGui :: CBullet_BaiXiaoGui(POINT p,char dir,int att,char type)
	:
	m_pBulletPoint(p),
	m_cDir(dir),
	m_iAttack(att),
	m_cBulletType(type)
{
}
CBullet_BaiXiaoGui ::	~CBullet_BaiXiaoGui()
{

}
//获取攻击
int CBullet_BaiXiaoGui :: GetAttack()
{
	return this->m_iAttack;
}
//获得子弹位置
POINT CBullet_BaiXiaoGui :: GetBulletPoint()
{
	return this->m_pBulletPoint;
}
//子弹运行，超过边界返回FALSE
bool CBullet_BaiXiaoGui :: BulletRun(int bianjie_R,int bianjie_D)
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
