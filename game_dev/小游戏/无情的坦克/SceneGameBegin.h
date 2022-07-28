#ifndef _SCENE_GAMEBEGIN_H_
#define _SCENE_GAMEBEGIN_H_

#include "Scene.h"


class CSceneGameBegin : public CScene
{
	bool m_bJieShaoTu;
public:
	//场景初始化
	virtual void Init();
	//场景进入
	virtual void Enter();
	//输出
	virtual void OutputRun(); 
	//逻辑运行
	virtual void LogicInputRun();
	//推出场景
	virtual void Quit();
	//UI消息
	void OnUIMsg(const char* id, int UIMSG);
};

#endif