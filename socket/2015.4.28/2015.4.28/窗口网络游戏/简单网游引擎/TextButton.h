#ifndef _TEXT_BUTTON_H_
#define _TEXT_BUTTON_H_

#include "UI.h"

#define _CURSOR_OUT 0 //光标在外部
#define _CURSOR_IN_UP 1 //光标在内部抬起
#define _CURSOR_IN_DOWN 2 //光标在内部按下

#define _TBM_CLICKED 100

class CTextButton : public CUI
{
protected:
	std::string m_Text; //文本
	int m_State; //状态
	bool m_Down; //按下标志

public:
	CTextButton(
		const char* Text, //按钮上面的文字
		int X, int Y, int W, int H, bool Visible = true, bool Enable = true);

	//设置按钮上面的文字
	void SetText(const char Text);

	//得到按钮上面的文字
	const char* GetText();

	//virtual void Init(); //初始化
	virtual void Enter(); //所属场景进入
	//virtual void Quit(); //所属场景退出
	//virtual void End(); //退出
	virtual void OnEvent(int Event, int X, int Y); //来自引擎的事件
	virtual void Render(bool Enable); //输出
};

#endif