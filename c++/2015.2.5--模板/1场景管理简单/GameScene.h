#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "Scene.h"

class CGameScene : public CScene
{
	int m_ix;
	int m_iy;
	bool m_bBeep;

public:
	CGameScene();
	void Run();
	bool ReturnBeep();
};

#endif