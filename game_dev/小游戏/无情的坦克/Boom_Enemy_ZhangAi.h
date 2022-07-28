#ifndef _ENEMY_ZHANGAI_H_
#define _ENEMY_ZHANGAI_H_
#include "Boom.h"
class CBoom_Enemy_ZhangAi : public CBoom
{
	//±¨’®Õº∆¨æÿ–Œ
	RECT m_rRect;
	//±¨’® ±º‰
	int m_iTime;
public:
	CBoom_Enemy_ZhangAi(RECT r,int time);
	~CBoom_Enemy_ZhangAi();
	//±¨’®ªÊ÷∆Õº∆¨
	void Paint();
	//±¨’®‘À––
	bool Run();
};
#endif