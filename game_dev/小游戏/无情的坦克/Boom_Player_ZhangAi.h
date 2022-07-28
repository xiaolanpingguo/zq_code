#ifndef _PLAYER_ZHANGAI_H_
#define _PLAYER_ZHANGAI_H_
#include "Boom.h"
class CBoom_Player_ZhangAi : public CBoom
{
	//±¨’®Õº∆¨æÿ–Œ
	RECT m_rRect;
	//±¨’® ±º‰
	int m_iTime;
public:
	CBoom_Player_ZhangAi(RECT r,int time);
	~CBoom_Player_ZhangAi();
	//±¨’®ªÊ÷∆Õº∆¨
	void Paint();
	//±¨’®‘À––
	bool Run();
};
#endif