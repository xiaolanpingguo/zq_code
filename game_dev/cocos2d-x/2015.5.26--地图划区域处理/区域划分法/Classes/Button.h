#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "UI.h"

#define _BUTTON_CLICK 1001

class CButton : public CUI
{
	CCTexture2D* inactive;
	CCTexture2D* normal;
	CCTexture2D* down;
	bool click_down;

public:

	CButton(
		const CCRect& r,
		const char* inactive_image,
		const char* inactive_normal,
		const char* inactive_down);

	//Ðéº¯Êý
	virtual void Enter();
	virtual void Render();
	virtual void OnMessage(int e, int x, int y);
	//virtual void Exit();
};

#endif