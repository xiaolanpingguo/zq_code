#ifndef __GAME_H__
#define __GAME_H__

#include "GameLayer.h"

class CGame : public CGameLayer
{
	CCTexture2D* t0;
	CCTexture2D* t1;

public:

	CGame();

	//virtual void Enter();
	//virtual void InputDown(CCPoint* p);
	//virtual void InputMove(CCPoint* p, int n);
	virtual void InputUp(CCPoint* p);
	virtual void Output();
	virtual void Logic(float dt);
	//virtual void Exit();
	void OnUIMessage(int id, int msg);
};

#endif