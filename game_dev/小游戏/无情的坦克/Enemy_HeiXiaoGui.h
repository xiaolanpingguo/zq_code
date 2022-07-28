#ifndef _ENEMY_HEIXIAOGUI_H_
#define _ENEMY_HEIXIAOGUI_H_
#include "Enemy.h"
#include <windows.h>
class CEnemy_HeiXiaoGui : public CEnemy
{
	//血量
	int m_iHp;
	//攻击
	int m_iAttack;
	//运动方向
	int m_iDir;
	//敌人类型
	int m_iEnemyType;
	//敌人是否移动
	bool m_bMove;
	//位置
	POINT m_pPoint;
public:
	CEnemy_HeiXiaoGui(int hp,int att,int dir,int type,bool move,int x,int y);
	~CEnemy_HeiXiaoGui();
	//获得血量
	int GetHp();
	//设置血量
	void SetHp(int hp);
	//设置方向
	void SetDir(char dir);
	//获得方向
	int GetDir();
	//设置是否移动
	void SetMove(bool move);
	//获得移动的方向
	int GetMove();
	//获得敌人的类型
	int GetType();
	//获得敌人的位置
	POINT GetEnemyPoint();
	//设置敌人的位置
	void SetEnemyPoint(POINT p);
	//敌人运行
	void EnemyRun(int bianjieR,int bianjieD);
	//敌人攻击发子弹
	void EnemyAttack(POINT p,int dir,std::vector<CBullet*>& vBullet);
};

#endif