#ifndef _BULLET_H_
#define _BULLET_H_
#include <Windows.h>
//运动的方向
#define _DIR_UP_	0
#define _DIR_DOWN_	1
#define _DIR_LEFT_	2
#define _DIR_RIGHT_ 3

//子弹运行速度
#define BULLET_SPEED 15

class CBullet
{
	//子弹位置
	POINT m_pBulletPoint;
	//子弹方向
	char m_cDir;
	//子弹类型
	char m_cBulletType;
	//子弹的攻击
	int m_iAttack;
public:
	CBullet();
	virtual ~CBullet();
	//通过子弹所属的敌人的攻击力
	virtual int GetAttack();
	//获得子弹位置
	virtual POINT GetBulletPoint();
	//子弹运行，超过边界就销毁
	virtual bool BulletRun(int bianjie_R,int bianjie_D);
};
#endif