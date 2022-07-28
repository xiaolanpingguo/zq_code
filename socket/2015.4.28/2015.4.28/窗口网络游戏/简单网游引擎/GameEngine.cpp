#include <time.h>
#include "GameEngine.h"
#include "Scene.h"
#include "UI.h"

CGameEngine* CGameEngine::m_GE = 0;

CGameEngine::CGameEngine()
:
m_hWnd(0),
m_Active(TRUE),
m_Input(0),
m_Output(0),
m_CurScene(0),
m_NextScene(0)
{}

CGameEngine::CGameEngine(const CGameEngine& that)
{}

CGameEngine::~CGameEngine()
{}

LRESULT CALLBACK CGameEngine::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		{
			if (GetGE()->m_CurScene)
			{
				//得到本次的光标位置
				POINT CurPos = {LOWORD(lParam), HIWORD(lParam)};

				//循环该场景的所有UI
				for (int i = 0; i < GetGE()->m_CurScene->m_UIs.Length(); ++i)
				{
					CUI* pUI = GetGE()->m_CurScene->m_UIs.At(i)->data;

					//状态判断
					if (pUI->GetVisible() && pUI->GetEnable())
					{
						//当前UI矩形
						RECT r = {pUI->m_X, pUI->m_Y, pUI->m_X + pUI->m_W, pUI->m_Y + pUI->m_H};

						//得到光标上次、本次与当前UI矩形的碰撞关系
						BOOL b1 = PtInRect(&r, GetGE()->m_PrePos);
						BOOL b2 = PtInRect(&r, CurPos);

						if (b1 && b2)
							pUI->OnEvent(_UIE_CURSOR_MOVE_IN, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y);
						else if (b1 && !b2)
							pUI->OnEvent(_UIE_CURSOR_QUIT, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y);
						else if (!b1 && b2)
							pUI->OnEvent(_UIE_CURSOR_ENTER, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y);
						else
							pUI->OnEvent(_UIE_CURSOR_MOVE_OUT, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y);
					}
				}

				//将本次位置设置为下一次的前次位置
				GetGE()->m_PrePos = CurPos;
			}

			return 0;
		}
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		{
			if (GetGE()->m_CurScene)
			{
				//得到本次的光标位置
				POINT CurPos = {LOWORD(lParam), HIWORD(lParam)};

				//循环该场景的所有UI
				for (int i = 0; i < GetGE()->m_CurScene->m_UIs.Length(); ++i)
				{
					CUI* pUI = GetGE()->m_CurScene->m_UIs.At(i)->data;

					//状态判断
					if (pUI->GetVisible() && pUI->GetEnable())
					{
						//当前UI矩形
						RECT r = {pUI->m_X, pUI->m_Y, pUI->m_X + pUI->m_W, pUI->m_Y + pUI->m_H};

						//得到本次与当前UI矩形的碰撞关系
						BOOL b = PtInRect(&r, CurPos);
						
						//根据碰撞关系进行不同的处理
						if (b)
						{
							switch (uMsg)
							{
							case WM_LBUTTONDOWN: pUI->OnEvent(_UIE_L_DOWN_IN, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							case WM_LBUTTONUP: pUI->OnEvent(_UIE_L_UP_IN, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							case WM_RBUTTONDOWN: pUI->OnEvent(_UIE_R_DOWN_IN, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							case WM_RBUTTONUP: pUI->OnEvent(_UIE_R_UP_IN, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							}
						}
						else
						{
							switch (uMsg)
							{
							case WM_LBUTTONDOWN: pUI->OnEvent(_UIE_L_DOWN_OUT, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							case WM_LBUTTONUP: pUI->OnEvent(_UIE_L_UP_OUT, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							case WM_RBUTTONDOWN: pUI->OnEvent(_UIE_R_DOWN_OUT, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							case WM_RBUTTONUP: pUI->OnEvent(_UIE_R_UP_OUT, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							}
						}
					}
				}
			}

			return 0;
		}
	case WM_KEYDOWN:
		{
			if (GetGE()->m_CurScene &&
				GetGE()->m_CurScene->m_KeyUI &&
				GetGE()->m_CurScene->m_KeyUI->GetVisible() &&
				GetGE()->m_CurScene->m_KeyUI->GetEnable())
			{
				GetGE()->m_CurScene->m_KeyUI->OnEvent(_UIE_K_DOWN, (int)wParam, 0);
			}

			return 0;
		}
	case WM_KEYUP:
		{
			if (GetGE()->m_CurScene &&
				GetGE()->m_CurScene->m_KeyUI &&
				GetGE()->m_CurScene->m_KeyUI->GetVisible() &&
				GetGE()->m_CurScene->m_KeyUI->GetEnable())
			{
				GetGE()->m_CurScene->m_KeyUI->OnEvent(_UIE_K_UP, (int)wParam, 0);
			}

			return 0;
		}
	case WM_CHAR:
		{
			if (GetGE()->m_CurScene &&
				GetGE()->m_CurScene->m_KeyUI &&
				GetGE()->m_CurScene->m_KeyUI->GetVisible() &&
				GetGE()->m_CurScene->m_KeyUI->GetEnable())
			{
				//如果已经收到单字节文字的首字节
				if (GetGE()->m_DB)
				{
					//组合之前的字节和当前的字节
					int c = 0;
					((char*)&c)[0] = GetGE()->m_HeadByte;
					((char*)&c)[1] = (char)wParam;

					//传入双字节文字
					GetGE()->m_CurScene->m_KeyUI->OnEvent(_UIE_CHAR, c, 1);
					GetGE()->m_DB = false;
					return 0;
				}

				//判断是否是双字节文字的首字节
				if (IsDBCSLeadByte((char)wParam))
				{
					GetGE()->m_HeadByte = (char)wParam;
					GetGE()->m_DB = true;
				}
				else
				{
					//传入单字节文字
					GetGE()->m_CurScene->m_KeyUI->OnEvent(_UIE_CHAR, (char)wParam, 0);
				}
			}

			return 0;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_ACTIVATEAPP:
		{
			GetGE()->m_Active = (BOOL)wParam;
			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool CGameEngine::Init(int ClientW, int ClientH, int SleepTime)
{
	srand((unsigned int)time(0));

	//参数检查
	if (ClientW < 1 || ClientH < 1 || SleepTime < 1)
		return false;

	//得到参数
	m_ClientW = ClientW;
	m_ClientH = ClientH;
	m_SleepTime = SleepTime;

	//填充窗口类别结构体
	m_WndClass.style = CS_HREDRAW | CS_VREDRAW;
	m_WndClass.lpfnWndProc = WindowProc;
	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hInstance = GetModuleHandle(0);
	m_WndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	m_WndClass.hCursor = LoadCursor(0, IDC_ARROW);
	m_WndClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND ;
	m_WndClass.lpszMenuName = 0;
	m_WndClass.lpszClassName = __TEXT("gamfe-cd-cx-66");

	//注册窗口类别结构体
	RegisterClass(&m_WndClass);

	//创建窗口
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	RECT rclient
		=
	{
		(sw - m_ClientW) / 2,
		(sh - m_ClientH) / 2,
		rclient.left + m_ClientW,
		rclient.top + m_ClientH
	};
	AdjustWindowRect(&rclient, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);
	m_hWnd = CreateWindow(
		m_WndClass.lpszClassName,
		0,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		rclient.left,
		rclient.top,
		rclient.right - rclient.left,
		rclient.bottom - rclient.top,
		HWND_DESKTOP,
		0,
		m_WndClass.hInstance,
		0);

	//初始化工具
	m_Input = new CGameInput(m_hWnd);
	m_Output = new CGameOutput(m_hWnd);
	m_AudioManager = new CAudioManager;

	//得到光标位置
	GetCursorPos(&m_PrePos);
	ScreenToClient(m_hWnd, &m_PrePos);

	//设置双字节表示为假
	m_DB = false;

	return true;
}

void CGameEngine::Run()
{
	//初始化所有场景
	for (int i = 0; i < m_Scenes.Length(); ++i)
	{
		//得到当前场景
		CScene* p = m_Scenes.At(i)->data;

		p->Init(); //初始化当前场景：多态

		for (int j = 0; j < p->m_UIs.Length(); ++j)
			p->m_UIs.At(j)->data->Init(); //初始化当前场景的所有UI：多态
	}

	if (m_CurScene)
	{
		m_CurScene->Enter(); //最初的场景的入：多态

		for (int i = 0; i < m_CurScene->m_UIs.Length(); ++i)
			m_CurScene->m_UIs.At(i)->data->Enter(); //最初的场景的所有UI的入：多态
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		int bt = GetTickCount();

		m_Input->Run();

		//游戏循环
		if (m_CurScene)
		{
			m_Output->Begin();

			m_CurScene->OutputRun(); //场景输出：多态

			for (int i = 0; i < m_CurScene->m_UIs.Length(); ++i)
			{
				CUI* pUI = m_CurScene->m_UIs.At(i)->data;
				pUI->Render(pUI->GetEnable()); //当前场景UI输出：多态
			}

			m_Output->End();

			m_CurScene->InputRun(); //场景输入：多态
			m_CurScene->LogicRun(); //场景逻辑：多态

			//网络部分运行
			m_TcpClient.Run();
			_TC_NET_EVENT tne;
			while (m_TcpClient.GetTCNetEvent(&tne))
			{
				//场景响应网络事件：多态
				m_CurScene->OnNetEvent(&tne);
				m_TcpClient.ReleaseTSNetEvent(&tne);
			}
		}

		int at = GetTickCount() - bt;
		Sleep(at < m_SleepTime ? m_SleepTime - at : 1);

		//说明游戏循环调用了SetCurScene，在此处执行当前场景
		//指针的改变，并且执行两个场景的Quit、Enter函数，假
		//设当前要从场景a切换到场景b，那么下面就会执行a->Quit，
		//再执行b->Enter
		if (m_NextScene)
		{
			for (int i = 0; i < m_CurScene->m_UIs.Length(); ++i)
				m_CurScene->m_UIs.At(i)->data->Quit(); //当前场景所有UI的出：多态

			m_CurScene->Quit(); //当前场景的出：多态

			m_CurScene = m_NextScene;

			m_CurScene->Enter(); //当前场景的入：多态

			for (int i = 0; i < m_CurScene->m_UIs.Length(); ++i)
				m_CurScene->m_UIs.At(i)->data->Enter(); //当前场景所有UI的入：多态

			m_NextScene = 0;
		}
	}

	if (m_CurScene)
	{
		for (int i = 0; i < m_CurScene->m_UIs.Length(); ++i)
			m_CurScene->m_UIs.At(i)->data->Quit(); //最后的场景的所有UI的出：多态

		m_CurScene->Quit(); //最后的场景的出：多态
	}

	//结束所有场景
	for (int i = 0; i < m_Scenes.Length(); ++i)
	{
		//得到当前场景
		CScene* p = m_Scenes.At(i)->data;


		for (int j = 0; j < p->m_UIs.Length(); ++j)
		{
			p->m_UIs.At(j)->data->End(); //结束当前场景的所有UI：多态
			delete p->m_UIs.At(j)->data; //删除UI
		}

		p->End(); //结束当前场景：多态
		delete p;
	}

	//释放工具
	delete m_AudioManager;
	delete m_Output;
	delete m_Input;

	delete m_GE;
}

CGameEngine* CGameEngine::GetGE()
{
	if (0 == m_GE)
		m_GE = new CGameEngine;
	return m_GE;
}

CGameInput* CGameEngine::GetInput()
{
	return m_Input;
}

CGameOutput* CGameEngine::GetOutput()
{
	return m_Output;
}

CAudioManager* CGameEngine::GetAudioManager()
{
	return m_AudioManager;
}

CTcpClient* CGameEngine::GetTcpClient()
{
	return &m_TcpClient;
}

bool CGameEngine::LoadScene(const char* id, CScene* pScene)
{
	std::string str = id;
	if (m_Scenes.Find(str))
		return false;

	m_Scenes.Insert(str, pScene);
	return true;
}

bool CGameEngine::SetFirstScene(const char* id)
{
	std::string str = id;
	CMap<std::string, CScene*>::PAIR* p = m_Scenes.Find(str);
	if (!p)
		return false;
	m_CurScene = p->data; //设置当前场景指针
	return true;
}

bool CGameEngine::SetCurScene(const char* id)
{
	std::string str = id;
	CMap<std::string, CScene*>::PAIR* p = m_Scenes.Find(str);
	if (!p)
		return false;
	m_NextScene = p->data; //设置下一个场景指针
	return true;
}

CScene* CGameEngine::GetScene(const char* id)
{
	std::string str = id;
	CMap<std::string, CScene*>::PAIR* p = m_Scenes.Find(str);
	return p ? p->data : 0;
}

void CGameEngine::Exit()
{
	PostQuitMessage(0);
}

int CGameEngine::GetRandomInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}