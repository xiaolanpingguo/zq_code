#include "GameInput.h"
#include <windows.h>

CGameInput::CGameInput(int* Key, int KeyNum)
:
m_KeyNum(KeyNum),m_Key(new int[m_KeyNum]),m_KeyState(new char[m_KeyNum])
{
	for(int i = 0; i < m_KeyNum; ++i)
	{
		m_Key[i] = Key[i];
		m_KeyState[i] = _KS_KEEP_UP;
	}
}

CGameInput::~CGameInput()
{
	if(m_Key)
		delete []m_Key;
	if(m_KeyState)
		delete []m_KeyState;
}

void CGameInput::Run()
{
	for(int i = 0; i < m_KeyNum; ++i)
	{
		//本次游戏循环下该按键是否被按下
		if(GetAsyncKeyState(m_Key[i])& 0x8000)
		{
			if(m_KeyState[i] == _KS_KEEP_UP
			|| m_KeyState[i] == _KS_NOW_UP)
				m_KeyState[i]  = _KS_NOW_DOWN;
			else 
				m_KeyState[i]  = _KS_KEEP_DOWN;
		}
		else //当前被抬起
		{
			if(m_KeyState[i] == _KS_KEEP_DOWN
			|| m_KeyState[i] == _KS_NOW_DOWN)
				m_KeyState[i]  = _KS_NOW_UP;
			else 
				m_KeyState[i]  = _KS_KEEP_UP;
		}
	}
}

//得到指定下标的那个键的当前状态
char CGameInput::KeyState(int KeyIndex)
{
	if(KeyIndex < 0 || KeyIndex >= m_KeyNum)
		return _KS_ERROR;
	else 
		return m_KeyState[KeyIndex];
}