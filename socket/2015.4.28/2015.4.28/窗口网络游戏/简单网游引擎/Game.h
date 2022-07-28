#ifndef _GAME_H_
#define _GAME_H_

#include "UI.h"
#include "Scene.h"

class CGame : public CScene
{
	//virtual ~CScene();
	virtual void Init();
	virtual void Enter();
	virtual void OutputRun();
	virtual void InputRun();
	virtual void LogicRun();
	virtual void Quit();
	//virtual void End();
	void OnUIMessage(int message, const char* id);
	void OnNetEvent(_TC_NET_EVENT* ptne);
};

#endif