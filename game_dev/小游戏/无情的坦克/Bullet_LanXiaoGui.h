#ifndef _BULLET_LANXIAOGUI_H_
#define _BULLET_LANXIAOGUI_H_
#include "Bullet.h"
class CBullet_LanXiaoGui : public CBullet
{
	POINT m_pBulletPoint;
	char m_cDir;
	char m_cBulletType;
	int m_iAttack;
public:
	CBullet_LanXiaoGui(POINT p,char dir,int att,char type);
	~CBullet_LanXiaoGui();
	POINT GetBulletPoint();
	bool BulletRun(int bianjie_R,int bianjie_D);
	int GetAttack();
};
#endif