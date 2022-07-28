#ifndef _GAME_INPUT_H_
#define _GAME_INPUT_H_

#define _KS_ERROR 0
#define _KS_KEEP_UP 1 //持续抬起
#define _KS_NOW_UP 2 //当前抬起
#define _KS_KEEP_DOWN 3 //持续按下
#define _KS_NOW_DOWN 4 //当前按下

class CGameInput
{
private:
	int m_KeyNum;
	int* m_Key;
	char* m_KeyState;
	
public:
	CGameInput(int* Key, int KeyNum);
	~CGameInput();

	void Run();

	//得到指定下标的那个键的当前状态
	char KeyState(int KeyIndex);
};

#endif