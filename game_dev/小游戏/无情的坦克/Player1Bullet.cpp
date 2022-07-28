#include "Player1Bullet.h"
//构造
CPlayer1Bullet :: CPlayer1Bullet(POINT p,char dir,int att,char type)
	:
//位置，方向，攻击，类型
	m_pBulletPoint(p),
	m_cDir(dir),
	m_iAttack(att),
	m_cBulletType(type)
{
}
CPlayer1Bullet :: 	~CPlayer1Bullet()
{
}
//获得子弹位置
POINT CPlayer1Bullet :: GetBulletPoint()
{
	return this->m_pBulletPoint;
}
//获取子弹攻击
int CPlayer1Bullet :: GetAttack()
{
	return this->m_iAttack;
}
//子弹运行，超过边界返回FALSE
bool CPlayer1Bullet :: BulletRun(int bianjie_R,int bianjie_D)
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
