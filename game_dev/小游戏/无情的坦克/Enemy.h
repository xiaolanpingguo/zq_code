#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <windows.h>
#include <vector>
#include "Bullet.h"
#include "GameEngine.h"
//敌人图片像素宽高
#define ENEMY_W 40
#define ENEMY_H 40
//敌人运动的时间
#define ENEMY_TIME 70
//敌人循环一次移动多少像素
#define PIXEL_MOVE 5
class CBullet;
class CEnemy
{
	//血量
	int m_iHp;
	//攻击力
	int m_iAttack;
	//方向
	int m_iDir;
	//敌人类型
	int m_iEnemyType;
	//是否移动（用于检测碰撞的时候四周都是障碍的时候便无法移动）
	bool m_bMove;
	//位置
	POINT m_pPoint;
public:
	CEnemy();
	virtual ~CEnemy();
	//获得血量
	virtual int GetHp();
	//设置血量
	virtual void SetHp(int hp);
	//设置方向
	virtual void SetDir(char dir);
	//获得方向
	virtual int GetDir();
	//设置是否移动（只要用于碰撞检测）
	virtual void SetMove(bool move);
	//获得当前是否移动
	virtual int GetMove();
	//获得敌人类型
	virtual int GetType();
	//获得敌人位置
	virtual POINT GetEnemyPoint();
	//设置敌人位置
	virtual void SetEnemyPoint(POINT p);
	//敌人运行
	virtual void EnemyRun(int bianjieR,int bianjieD);
	//敌人攻击，发子弹
	virtual void EnemyAttack(POINT p,int dir,std::vector<CBullet*>& vBullet);
};
#endif