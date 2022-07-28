#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>
#include <map>
class CUI;
class CScene
{
	friend class CGameEngine;

	//入出切换名字
	std::string m_EnterChange;
	std::string	m_QuitChange;

	//控件管理表
	std::map<std::string,CUI*> m_UI;
public:
	CScene();
	virtual ~CScene();

	virtual void Init();
	virtual void Enter();
	virtual void OutputRun(); //绘制
	virtual void LogicInputRun(); //逻辑、输入
	virtual void Quit();
	virtual void End();

	//切换相关
	void SetEnterChange(const char* id);
	void SetQuitChange(const char* id);

	//控件相关
	//加载相关
	//卸载相关
	//得到控件
};

#endif