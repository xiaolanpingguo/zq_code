#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#include "TcpClient.h"
#include <windows.h>
#include <string>
#include "Map.h"
#include "GameInput.h"
#include "GameOutput.h"
#include "AudioManager.h"

class CScene;

class CGameEngine
{
	static CGameEngine* m_GE;
	int m_ClientW, m_ClientH;
	int m_SleepTime;
	WNDCLASS m_WndClass;
	HWND m_hWnd;
	BOOL m_Active;
	POINT m_PrePos;
	bool m_DB; //双字节标志
	char m_HeadByte; //双字节文字首字节

	//工具相关
	CGameInput* m_Input;
	CGameOutput* m_Output;
	CAudioManager* m_AudioManager;
	CTcpClient m_TcpClient;

	//场景相关数据
	CMap<std::string, CScene*> m_Scenes; //场景映射
	CScene* m_CurScene; //当前场景
	CScene* m_NextScene; //下一个场景

	CGameEngine();
	CGameEngine(const CGameEngine& that);
	~CGameEngine();

	//如果窗口消息函数不是静态的话，那么其实形式参数
	//有5个，多了一个CGameEngine* this，那么就和WNDPROC
	//不匹配了，所以写为静态成员函数
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	bool Init(int ClientW, int ClientH, int SleepTime);
	void Run();

	//得到引擎
	static CGameEngine* GetGE();

	//得到工具
	CGameInput* GetInput();
	CGameOutput* GetOutput();
	CAudioManager* GetAudioManager();
	CTcpClient* GetTcpClient();

	//场景相关函数
	bool LoadScene(const char* id, CScene* pScene);
	bool SetFirstScene(const char* id);
	bool SetCurScene(const char* id);
	CScene* GetScene(const char* id);
	void Exit();

	//其它
	static int GetRandomInt(int min, int max);
};

#endif