#ifndef _BOOM_H_
#define _BOOM_H_
#include <windows.h>
#include "GameEngine.h"
class CBoom
{
	//爆炸物的矩形
	RECT m_rRect;
	//设置的时间
	int m_iTime;
public:
	CBoom(RECT r,int time);
	virtual ~CBoom();
	//绘制爆炸类型
	virtual void Paint();
	//爆炸逻辑函数
	virtual bool Run();
};
#endif