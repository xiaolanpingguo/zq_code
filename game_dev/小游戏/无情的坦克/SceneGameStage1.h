#ifndef _SCENE_GAMESTAGE1_H_
#define _SCENE_GAMESTAGE1_H_

#include "Scene.h"
#include "GameLogic.h"
class CSceneGameStage1 : public CScene
{
	//游戏是否结束
	bool m_bGameEnd;
	//绘制“第一关”这张图片的时间
	int m_iTime;
	//是否为读取存档进的游戏
	bool m_bIsRead;
	//当前关卡
	int m_iStage;
	//逻辑类对象
	CGameLogic  stage1;
	//是否播发最后的音乐
	bool m_bBoFang;
public:
	//场景初始化
	void Init();
	//场景进入
	void Enter();
	//输出
	void OutputRun(); 
	//逻辑运行
	void LogicInputRun(); 
	//退出场景
	void Quit();
	void SetRead(bool set);
	bool GetSetRead();
	//UI消息
	void OnUIMsg(const char* id, int UIMSG);
	//获得逻辑类指针
	CGameLogic* GetLogicObject();
};

#endif