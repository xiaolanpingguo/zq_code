#ifndef _SETSCENE_H_
#define _SETSCENE_H_
#include "Scene.h"


//游戏设置场景类
class CSetScene : public CScene
{
	int sel;
public:
	CSetScene();
	void Run();
};

#endif