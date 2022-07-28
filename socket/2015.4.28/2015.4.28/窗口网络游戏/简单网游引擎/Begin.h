#ifndef _BEGIN_H_
#define _BEGIN_H_

#include "UI.h"
#include "Scene.h"
#include <string>
#include <map>
#include "..\\GameProtocol.h"

class CBegin : public CScene
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
public:
	std::string m_Nick_Name;
	char map[_GAME_MAP_S]; //µØÍ¼
	std::map<std::string, POINT> all_player; //ÓÎÏ·Íæ¼Ò
};

#endif