#ifndef _BULLET_HEIXIAOGUI_H_
#define _BULLET_HEIXIAOGUI_H_
#include "Bullet.h"
class CBullet_HeiXiaoGui : public CBullet
{
	POINT m_pBulletPoint;
	char m_cDir;
	char m_cBulletType;
	int m_iAttack;
public:
	CBullet_HeiXiaoGui(POINT p,char dir,int att,char type);
	~CBullet_HeiXiaoGui();
	POINT GetBulletPoint();
	bool BulletRun(int bianjie_R,int bianjie_D);
	int GetAttack();
};
#endif