#include "GameEngine.h"	
#include "Scene.h"
#include <time.h>
#include <iostream>

CGameEngine* CGameEngine::m_pGameEngine = 0;
LRESULT CALLBACK CGameEngine::_WindPorc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_ACTIVATEAPP:
		{
			GetGE()->m_Act = (BOOL)wParam;
			return 0;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}
 
	//构造析构 
	//单件模式
	//在整个工程中只有一个对象
	//其构造和析构必须是私有的
	//必须有一个本类的指针，而且必须是私有的静态成员
	//必须有一个公有的静态成员函数，用来返回静态的指针
CGameEngine::CGameEngine()
:
m_hWnd(0),
m_iClientW(0),
m_iClientH(0),
m_Act(TRUE),
m_iSleepTime(33),
m_pGI(0),
m_pGO(0),
m_pCurScene(0),
m_pNextScene(0)
{
	srand((unsigned int)time(0));
}
CGameEngine::~CGameEngine()
{}

CGameEngine* CGameEngine::GetGE()
{
	if(0 == m_pGameEngine)
		m_pGameEngine = new CGameEngine;
	return m_pGameEngine;
}

	//初始化
bool CGameEngine::Init(int ClientW,int ClientH)
{
	if(ClientW < 1 || ClientH < 1)
		return false;
	//得到宽高
	m_iClientW = ClientW;
	m_iClientH = ClientH;

	m_WndClass.style = CS_HREDRAW|CS_VREDRAW;
	m_WndClass.lpfnWndProc = _WindPorc;
	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hInstance = GetModuleHandle(0);
	m_WndClass.hIcon = LoadIcon(0,IDI_APPLICATION);
	m_WndClass.hCursor = LoadCursor(0,IDC_ARROW);
	m_WndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_WndClass.lpszMenuName = 0;

	for(int i = 0; i < 31; ++i)
	{
		m_WndClassName[i] = rand() % 26 + 'a';
	}
	m_WndClassName[31] = 0;

	m_WndClass.lpszClassName = m_WndClassName;
	RegisterClass(&m_WndClass);

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	RECT r = 
	{
		(sw - m_iClientW) / 2,
		(sh - m_iClientH) / 2,
		(sw - m_iClientW) / 2 + m_iClientW,
		(sh - m_iClientH) / 2 + m_iClientH
	};

	AdjustWindowRect(&r,
		WS_OVERLAPPED | WS_CAPTION 
		| WS_SYSMENU | WS_MINIMIZEBOX ,
		FALSE);

	m_hWnd = CreateWindow(
		m_WndClass.lpszClassName,
		0,
		WS_OVERLAPPED | WS_CAPTION 
		| WS_SYSMENU | WS_MINIMIZEBOX,
		r.left,
		r.top,
		r.right - r.left,
		r.bottom - r.top,
		HWND_DESKTOP,
		0,
		m_WndClass.hInstance,
		0);

	m_pGI = new CGameInput(m_hWnd);
	m_pGO = new CGameOutput(m_hWnd);
	return true;
}

//运行
void CGameEngine::Run()
{
	std::map<std::string, CScene*>::iterator i;
	//场景初始化
	for(i = m_Scene.begin(); i != m_Scene.end();++i)
		i->second->Init();//多态

	if(m_pCurScene)
		m_pCurScene->Enter();

	ShowWindow(m_hWnd,SW_SHOW);
	UpdateWindow(m_hWnd);

	MSG msg = {};
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(m_Act)
		{
			int bt = GetTickCount();
			m_pGI->Run();
			m_pGO->Begin();
			if(m_pCurScene)
				m_pCurScene->Run();

			
			m_pGO->End();
			int at = GetTickCount() - bt;
			Sleep((m_iSleepTime > at) ? (m_iSleepTime - at) : 1);
		}
		else
		{
			WaitMessage();
		}

		if(m_pNextScene)
		{
			m_pCurScene->Quit();
			m_pCurScene = m_pNextScene;
			m_pCurScene->Enter();
			m_pNextScene = 0;
		}
	}

	if(m_pCurScene)
	{
		m_pCurScene->Quit();
	}
	for(i = m_Scene.begin(); i != m_Scene.end();++i)
	{
		i->second->End();
		delete i->second;
	}
	delete m_pGO;
	delete m_pGI;
	delete m_pGameEngine;
}

//场景相关
bool CGameEngine::LoadScene(const char* id,CScene* pScene)
{
	return true;
}

bool CGameEngine::ReleaseScene(const char* id)
{
	return true;
}

bool CGameEngine::SetInitScene(const char* id)
{
	return true;
}

bool CGameEngine::SetCurScene(const char* id)
{
	return true;
}

CScene* CGameEngine::GetScene(const char* id)
{
	return 0;
}

//工具相关
CGameInput* CGameEngine::GetGI()
{
	return m_pGI;
}
CGameOutput* CGameEngine::GetGO()
{
	return m_pGO;
}
void CGameEngine::SetTitle(const char* Title)
{}
bool CGameEngine::SetSleepTime(int SleepTime)
{
	return true;
}

void CGameEngine::ExitGame()
{}