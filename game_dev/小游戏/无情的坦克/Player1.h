#ifndef _PLAYER1_H
#define _PLAYER1_H
#include "Player.h"
#include "GameEngine.h"
#include "Player1Bullet.h"
#define _GRIDE_W_ 40
#define _GRIDE_H_ 40

#define _DIR_UP_	0
#define _DIR_DOWN_	1
#define _DIR_LEFT_	2
#define _DIR_RIGHT_ 3
class CPlayer1 : public CPlayer
{
	int m_iLife;
	int m_iDir;
	int m_iAttack;
	POINT m_pPlayerPoint;
public:
	CPlayer1(int life,int dir,int att);
	~CPlayer1();
};
#endif