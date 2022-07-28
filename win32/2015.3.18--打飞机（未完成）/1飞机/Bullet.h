#ifndef _BULLET_H_
#define _BULLET_H_
#include <windows.h>

class CBullet
{
	POINT m_BulletPoint;//记录子弹位置
	bool m_bDirect;//方向，true上，false下
public:
	CBullet();
	virtual ~CBullet();

	//初始化参数为位置和方向
	virtual void BulletInit(POINT point,bool dir);

	//子弹运行，返回假则飞出边界该销毁
	virtual bool BulletRun(int bianjie);

	//获取子弹位置
	virtual POINT GetBulletPoint();
};

#endif