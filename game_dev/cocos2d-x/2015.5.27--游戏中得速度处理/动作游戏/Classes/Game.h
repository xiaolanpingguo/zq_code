#ifndef __GAME_H__
#define __GAME_H__

#include "GameLayer.h"
#include "ActGame.h"

class CGame : public CGameLayer
{
	CActGame ag;
	_OBJECT* hero;

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