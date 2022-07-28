#ifndef _SCENE_GAMESTAGE_2_H_
#define _SCENE_GAMESTAGE_2_H_

#include "Scene.h"
#include "GameLogic.h"
class CSceneGameStage2 : public CScene
{
	//游戏是否结束
	bool m_bGameEnd;
	//游戏是否胜利
	bool m_bGameVictor;
	//图片加载时间
	int m_iTime;
	//是否通过读档进入的游戏
	bool m_bIsRead;
	//关卡
	int m_iStage;
	//是否播发游戏失败的音乐
	bool m_bBoFangshibai;
	//是否播发游戏胜利的音乐
	bool m_bBoFangWin;
	//逻辑类对象
	CGameLogic  stage2;
public:
	//初始化场景
	virtual void Init();
	//进入场景
	virtual void Enter();
	//输出
	virtual void OutputRun(); 
	//逻辑输出
	virtual void LogicInputRun(); 
	//退出
	virtual void Quit();
	//是否通过游戏读取进入的游戏
	virtual void SetRead(bool set);
	//UI消息
	virtual void OnUIMsg(const char* id, int UIMSG);
	//获取逻辑类对象
	CGameLogic* GetLogicObject();
};

#endif