#include "GameInput.h"

CGameInput::CGameInput()
:
m_iKeyCount(26),
m_pKey(new char[m_iKeyCount]),
m_pKeyState(new char[m_iKeyCount])
{
	for(int i = 0; i < this->m_iKeyCount; ++i)
	{
		this->m_pKey[i] = 'A' + i;
		this->m_pKeyState[i] = _KEY_UP;
	}
}
CGameInput::~CGameInput()
{
	if(this->m_pKey)
		delete []this->m_pKey;
	if(this->m_pKeyState)
		delete []this->m_pKeyState;
}

//void Destroy()
//{
//	if(this->m_pKey)
//		delete []this->m_pKey;
//	if(this->m_pKeyState)
//		delete []this->m_pKeyState;
//	this->m_pKey = 0;
//	this->m_pKeyState = 0;
//}

//设置键的状态
void CGameInput::SetKeyState(char state)
{
	for(int i = 0; i < this->m_iKeyCount; ++i)
	{
		if(this->m_pKey[i] == state 
		|| this->m_pKey[i] + 32 == state)
			this->m_pKeyState[i] = _KEY_DOWN;
		else
			this->m_pKeyState[i] = _KEY_UP;
	}
}

//获取指定的键的状态
char CGameInput::GetKeyState(int index)
{
	return this->m_pKeyState[index];
}

char CGameInput::GetKeyState()
{
	for(int i = 0; i < this->m_iKeyCount; ++i)
	{
		if(this->m_pKeyState[i] == _KEY_DOWN)
			return this->m_pKey[i];
	}

	return 0;
}