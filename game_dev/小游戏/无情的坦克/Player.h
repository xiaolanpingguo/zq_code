#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <Windows.h>
#include <vector>
#include "GameEngine.h"
#include "Bullet.h"
#include "Player1Bullet.h"
#define _GRIDE_W_ 40
#define _GRIDE_H_ 40

#define _DIR_UP_	0
#define _DIR_DOWN_	1
#define _DIR_LEFT_	2
#define _DIR_RIGHT_ 3
class CBullet;
class CPlayer
{
	//生命
	int m_iLife;
	//当前方向
	char m_iDir;
	//当前攻击
	int m_iAttack;
	//当前位置
	POINT m_pPlayerPoint;
public:
	CPlayer(int life,int dir,int att);
	~CPlayer();
	//设置当前方向和获得方向
	void SetDir(int dir);
	int GetDir();
	//获得当前位置和设置当前位置
	POINT GetPlayerPoint();
	void SetPlayerPoint(POINT p);
	//获得当前生命和设置生命
	void SetLife(int life);
	int GetLife();
	//获得当前攻击和设置攻击
	int GetAttack();
	void SetAttack(int attack);
	//攻击发子弹
	void PlayerAttack(POINT p,std::vector<CBullet*>& vBullet);
};
#endif