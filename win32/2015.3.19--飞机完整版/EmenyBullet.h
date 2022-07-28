#ifndef _EMENYBULLET_H_
#define _EMENYBULLET_H_
#include "Bullet.h"

class CEmenyBullet : public CBullet
{
	POINT m_BulletPoint;//记录子弹位置
	bool m_bDirect;//方向，true上，false下
public:
	CEmenyBullet();
	~CEmenyBullet();

	//初始化参数为位置和方向
	void BulletInit(POINT point,bool dir);

	//子弹运行，返回假则飞出边界该销毁
	bool BulletRun(int bianjie);

	//获取子弹位置
	POINT GetBulletPoint();
};

#endif