#ifndef _BOOM_ENEMY_PLAYER_H_
#define _BOOM_ENEMY_PLAYER_H_
#include "Boom.h"
class CBoom_Enemy_Player : public CBoom
{
	//±¨’®Õº∆¨æÿ–Œ
	RECT m_rRect;
	//±¨’® ±º‰
	int m_iTime;
public:
	CBoom_Enemy_Player(RECT r,int time);
	~CBoom_Enemy_Player();
	//±¨’®ªÊ÷∆Õº∆¨
	void Paint();
	//±¨’®‘À––
	bool Run();
};
#endif