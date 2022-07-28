#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

#include <windows.h>
#include <string>
#include <map>

#include "GameInput.h"
#include "GameOutput.h"

class CScene;
class CSceneChange;

class CGameEngine
{
	//窗口相关
	WNDCLASSA m_WndClass;
	char m_WndClassName[32];
	HWND m_hWnd;
	int m_iClientW;
	int m_iClientH;
	BOOL m_Act;
	int m_iSleepTime;//休眠时间

	//工具相关
	CGameInput* m_pGI;
	CGameOutput* m_pGO;

	//场景相关
	std::map<std::string,CScene*> m_Scene;//场景父类指针映射
	CScene* m_pCurScene;//当前场景
	CScene* m_pNextScene;//下个场景

	//消息处理函数
	static LRESULT CALLBACK _WindPorc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);

	//构造析构 
	//单件模式
	//在整个工程中只有一个对象
	//其构造和析构必须是私有的
	//必须有一个本类的指针，而且必须是私有的静态成员
	//必须有一个公有的静态成员函数，用来返回静态的指针
	CGameEngine();
	~CGameEngine();
	static CGameEngine* m_pGameEngine;

	int m_iRunState;//运行状态

	//切换相关
	CSceneChange* m_pEnterChange;
	CSceneChange* m_pQuitChange;

	std::map<std::string,CSceneChange*> m_SceneChange;//场景切换

public:
	//得到游戏引擎
	static CGameEngine* GetGE();
	//{
	//	m_pGameEngine = new CGameEngine;
	//	return m_pGameEngine;
	//}

	//初始化
	bool Init(int ClientW,int ClientH);

	//运行
	void Run();

	//场景相关
	bool LoadScene(const char* id,CScene* pScene);

	bool ReleaseScene(const char* id);

	bool SetInitScene(const char* id);

	bool SetCurScene(const char* id);

	CScene* GetScene(const char* id);

	//工具相关
	CGameInput* GetGI();
	CGameOutput* GetGO();
	void SetTitle(const char* Title);
	bool SetSleepTime(int SleepTime);
	
	void ExitGame();

	int GetW();

	int GetH();

	//加载场景切换
	bool LoadSceneChange(const char* id,CSceneChange* pSceneChange);
};

#endif