#ifndef _GAMELOGO_H_
#define _GAMELOGO_H_

#include "Scene.h"

class CGameLogo : public CScene
{
	//界面LOGO出现的时间
	int m_iTime;
public:
	//场景初始化
	virtual void Init();
	//输出
	virtual void OutputRun(); 
	//逻辑运行
	virtual void LogicInputRun(); 
	//进入场景
	virtual void Enter();
};

#endif