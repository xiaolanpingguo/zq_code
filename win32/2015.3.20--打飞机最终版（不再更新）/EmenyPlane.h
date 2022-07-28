#ifndef _EMENYPLANE_H_
#define _EMENYPLANE_H_

#include "Plane.h"

class CBullet;

class CEmenyPlane : public CPlane
{
	POINT m_Point;//记录飞机位置
	int m_iHp;//飞机血量
	int m_iDirect;//记录飞机方向，0 向下，1 向左，2 ，向右
	int m_iTimeAtt;//发射子弹的时间间隔，这个数据应该是随机的.
public:
	CEmenyPlane();
	~CEmenyPlane();

	//初始化函数，初始化飞机的位置，血量
	void Init(POINT p);

	//飞机运行，主要用于敌机
	bool Run(int right,int bottom,std::vector<CBullet*>& vBullet);

	//设置血量
	void SetHP(int hp);

	//获取血量
	int GetHP();

	//获取位置
	POINT GetPoint();

	//攻击
	void Attack(POINT p,std::vector<CBullet*>& vBullet);
}; 

#endif