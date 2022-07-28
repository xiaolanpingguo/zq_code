//------------------------
//CGameInput:游戏输入类
//主要负责游戏中键盘输入的键值
//------------------------

#ifndef _GAMEINPUT_H_
#define _GAMEINPUT_H_

#define _KEY_UP   0   //键抬起
#define _KEY_DOWN 1   //键按下

class CGameInput
{
	int m_iKeyCount;//按键的数量
	char* m_pKey;//记录需要的键值，在这里记录键盘上的所有的大写字母形式
	char* m_pKeyState;//键的状态
public:
	CGameInput();
	~CGameInput();

	//设置键的状态
	void SetKeyState(char state);

	//获取指定的键的状态 返回index为下标的键的状态
	char GetKeyState(int index);

	//获取指定的键的状态返回按下的键
	char GetKeyState();
};

#endif