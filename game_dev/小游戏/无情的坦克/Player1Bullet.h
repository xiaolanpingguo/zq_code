#ifndef _PLAYER1BULLET_H_
#define _PLAYER1BULLET_H_
#include "Bullet.h"
class CPlayer1Bullet : public CBullet
{
	//子弹位置
	POINT m_pBulletPoint;
	//子弹方向
	char m_cDir;
	//子弹类型
	char m_cBulletType;
	//子弹攻击
	int m_iAttack;
public:
	//构造和析构
	CPlayer1Bullet(POINT p,char dir,int att,char type);
	~CPlayer1Bullet();
	//获取子弹位置
	POINT GetBulletPoint();
	//获取子弹攻击力
	int GetAttack();
	//子弹运行
	bool BulletRun(int bianjie_R,int bianjie_D);
};
#endif