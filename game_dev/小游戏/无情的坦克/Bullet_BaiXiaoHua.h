#ifndef _BULLET_BAIXIAOHUA_H_
#define _BULLET_BAIXIAOHUA_H_
#include "Bullet.h"
class CBullet_BaiXiaoHua : public CBullet
{
	//子弹位置，方向，子弹类型，攻击
	POINT m_pBulletPoint;
	char m_cDir;
	char m_cBulletType;
	int m_iAttack;
public:
	CBullet_BaiXiaoHua(POINT p,char dir,int att,char type);
	~CBullet_BaiXiaoHua();
	//获取子弹位置
	POINT GetBulletPoint();
	//子弹运行
	bool BulletRun(int bianjie_R,int bianjie_D);
	//获取攻击
	int GetAttack();
};
#endif