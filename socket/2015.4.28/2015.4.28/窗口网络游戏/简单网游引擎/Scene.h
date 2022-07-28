#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>
#include "Map.h"
#include "TcpClient.h"

class CUI;

class CScene
{
	friend class CGameEngine;

protected:
	CMap<std::string, CUI*> m_UIs;
	CUI* m_KeyUI; //拥有键盘焦点的控件

public:
	CScene();
	virtual ~CScene();

	//只在最初的时候执行一次本场景Init函数
	virtual void Init();

	//当从其它场景进入到本场景的时候执行本场景Enter函数
	virtual void Enter();

	//输出、输入、逻辑
	virtual void OutputRun();
	virtual void InputRun();
	virtual void LogicRun();

	//当从本场景进入到的其它场景时候执行本场景Quit函数
	virtual void Quit();

	//只在最后的时候执行一次本场景End函数
	virtual void End();

	//UI相关
	bool LoadUI(CUI* pUI, const char* id);
	CUI* GetUI(const char* id);
	bool SetKeyUI(const char* id);
	CUI* GetKeyUI();
	virtual void OnUIMessage(int message, const char* id);

	//网络相关
	virtual void OnNetEvent(_TC_NET_EVENT* ptne);
};

#endif