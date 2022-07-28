#ifndef _GAME_CLASS_H_
#define _GAME_CLASS_H_

class CGameClass
{
public:
	virtual const char* name() = 0;
	virtual void init() = 0;
	virtual void run() = 0;
	virtual void end() = 0;
};

//每个完成具体的游戏的DLL中都必须提供一个函数如下
//CGameClass* getGame()
//{
//	return new XXX;
//}

#endif