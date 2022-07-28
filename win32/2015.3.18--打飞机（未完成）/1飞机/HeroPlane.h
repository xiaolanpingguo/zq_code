#ifndef _HEROPLANE_H_
#define _HEROPLANE_H_

#include "Plane.h"

class CBullet;

class CHeroPlane : public CPlane
{
	POINT m_Point;//记录飞机位置
	int m_iHp;//飞机血量
public:
	CHeroPlane();
	~CHeroPlane();

	//初始化函数，初始化飞机的位置，血量
	void Init(POINT p);

	//设置飞机位置，主要用于英雄
	void SetPlanePoint(POINT p);

	//设置血量
	void SetHP(int hp);

	//获取血量
	int GetHP();

	//获取位置
	POINT GetPoint();

	//攻击
	void Attack(POINT p,std::vector<CBullet*> vBullet);
}; 

#endif