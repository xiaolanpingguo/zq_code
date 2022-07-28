#ifndef _BUTTON_UI_H_
#define _BUTTON_UI_H_

#include "UI.h"
#include <string>

#define _BUTTON_CLICK 0 //按钮被按下消息

class CButtonUI : public CUI
{
	bool m_In; //光标在按钮内
	std::string m_Text; //按钮的文字

public:
	CButtonUI(const char* t, int x, int y, int w, int h, bool v = true, bool a = true);

	//virtual void Init();
	virtual void ActRender();
	virtual void UnactRender();
	virtual void OnMsg(int Msg, int p1, int p2);
	//virtual void End();

	void SetText(const char* t);
	const char* GetText();
};

#endif