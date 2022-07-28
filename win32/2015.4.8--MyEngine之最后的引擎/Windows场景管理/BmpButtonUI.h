#ifndef _BMP_BUTTON_UI_H_
#define _BMP_BUTTON_UI_H_

#include "ButtonUI.h"
#include <string>
#include <windows.h>


class CBmpButtonUI : public CButtonUI
{
	std::string s[4];
	bool m_Transparent;//是否要透明
	unsigned int m_TC;//透明颜色
public:
	CBmpButtonUI(const char* bmp_act_cursor_out,
		const char* bmp_act_cursor_in_up,
		const char* bmp_act_cursor_in_down,
		const char* bmp_unact,
		int x,
		int y,
		int w,
		int h,
		bool t = true,//透明标记
		unsigned int tc = RGB(0,255,0),//透明颜色
		bool v = true,
		bool a = true);

	//virtual void Init();
	virtual void ActRender();
	virtual void UnactRender();
	//virtual void OnMsg(int Msg, int p1, int p2);
	//virtual void End();

	//void SetText(const char* t);
	//const char* GetText();
};

#endif