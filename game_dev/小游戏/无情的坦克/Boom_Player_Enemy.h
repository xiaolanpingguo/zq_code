#ifndef _BOOM_PLAYER_ENEMY_H_
#define _BOOM_PLAYER_ENEMY_H_
#include "Boom.h"
class CBoom_Player_Enemy : public CBoom
{
	//±¨’®Õº∆¨æÿ–Œ
	RECT m_rRect;
	//±¨’® ±º‰
	int m_iTime;
public:
	CBoom_Player_Enemy(RECT r,int time);
	~CBoom_Player_Enemy();
	//±¨’®ªÊ÷∆Õº∆¨
	void Paint();
	//±¨’®‘À––
	bool Run();
};
#endif