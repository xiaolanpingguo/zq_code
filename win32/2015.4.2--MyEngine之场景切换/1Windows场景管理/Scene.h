#ifndef _SCENE_H_
#define _SCENE_H_
#include <string>
class CScene
{
	friend class CGameEngine;
	std::string m_EnterChange;
	std::string m_QuitChange;
public:
	CScene();
	virtual ~CScene();
	virtual void Init();
	virtual void Enter();
	virtual void OutputRun();//绘制
	virtual void LogicInputRun();//逻辑输入
	virtual void Quit();
	virtual void End();

	//切换相关
	void SetEnterChange(const char* id);
	void SetQuitChange(const char* id);
};

#endif