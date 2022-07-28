#ifndef _BUTTON2_H_
#define _BUTTON2_H_

#include "Button.h"

#define _BUTTON2_DOWN 1002

class CButton2 : public CButton
{
public:

	CButton2(
		const CCRect& r,
		const char* inactive_image,
		const char* inactive_normal,
		const char* inactive_down);

	//Ðéº¯Êý
	//virtual void Enter();
	//virtual void Render();
	virtual void OnMessage(int e, int x, int y);
	virtual void Logic();
	//virtual void Exit();
};

#endif