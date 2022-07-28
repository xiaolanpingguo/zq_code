#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_
#include<windows.h>

#define SLOW 0
#define MID 1
#define QUICK 2

class CGameLogic
{
	int hp;
	int score;
	int speed;
	int flag;
public:
	CGameLogic();
	void isTouch();
	void addPlane();
	void isOut(HWND hwnd);
	void run();
	void addBullet();
	void setHp(int h);
	int getHp();
	void setScore(int s);
	int getScore();
	void setSpeed(int sp);
	int getSpeed();
	void setFlag(int h);
	int getFlag();
	void isDeath(HWND hwnd);
	
};

#endif 