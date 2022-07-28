#ifndef _IMAGE_BUTTON_H_
#define _IMAGE_BUTTON_H_

#include "TextButton.h"
#include <string>

#define _IBM_CLICKED _TBM_CLICKED

class CImageButton : public CTextButton
{
	std::string m_NoEnable;
	std::string m_CursorOut;
	std::string m_CursorInUp;
	std::string m_CursorInDown;

	int m_NoEnable_W, m_NoEnable_H;
	int m_CursorOut_W, m_CursorOut_H;
	int m_CursorInUp_W, m_CursorInUp_H;
	int m_CursorInDown_W, m_CursorInDown_H;

public:
	CImageButton(
		const char* no_enable, //未激活时显示的图像
		const char* cursor_out, //光标在外部时显示的图像
		const char* cursor_in_up, //光标在内部抬起时显示的图像
		const char* cursor_in_down, //光标在内部按下时显示的图像
		int X, int Y, int W, int H, bool Visible = true, bool Enable = true);

	//virtual void Init(); //初始化
	//virtual void Enter(); //所属场景进入
	//virtual void Quit(); //所属场景退出
	//virtual void End(); //退出
	//virtual void OnEvent(int Event, int X, int Y); //来自引擎的事件
	virtual void Render(bool Enable); //输出
};

#endif