#ifndef _PLANE_H_
#define _PLANE_H_
#include <windows.h>


class CPlane
{
	POINT m_Point;//记录飞机位置
	int m_iHp;//飞机血量
public:
	CPlane();
	virtual ~CPlane();

	//初始化函数，初始化飞机的位置，血量
	virtual void Init(POINT p);

	//设置飞机位置，主要用于英雄
	virtual void SetPlanePoint(POINT p);

	//设置飞机位置，主要用于敌机
	virtual void SetPlanePoint();

	//飞机运行，主要用于敌机
	virtual void Run();

	//设置血量
	virtual void SetHP(int hp);

	//获取血量
	virtual int GetHP();

	//获取位置
	virtual POINT GetPoint();

	//攻击
	virtual void Attack(POINT p);
}; 

#endif