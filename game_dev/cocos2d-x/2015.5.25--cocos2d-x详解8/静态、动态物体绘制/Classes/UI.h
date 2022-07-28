#ifndef _UI_H_
#define _UI_H_

#include "cocos2d.h"

using namespace cocos2d;

class CGameLayer;

#define _UE_IN_DOWN 0 //内部按下
#define _UE_IN_UP 1 //内部抬起
#define _UE_OUT_DOWN 2 //外部按下
#define _UE_OUT_UP 3 //外部抬起

class CUI
{
public:
	CCRect m_Rect; //位置和尺寸
	bool m_Visible; //可见性
	bool m_Active; //激活性
	int m_ID; //标示
	CGameLayer* m_Layer; //层

	//构造
	CUI(const CCRect& r,
		bool v = true,
		bool a = true);

	//析构
	virtual ~CUI();

	//虚函数
	virtual void Enter();
	virtual void Render();
	virtual void OnMessage(int e, int x, int y);
	virtual void Exit();
};

#endif