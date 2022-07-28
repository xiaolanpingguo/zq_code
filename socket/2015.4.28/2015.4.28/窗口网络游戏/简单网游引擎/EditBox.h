#ifndef _EDIT_BOX_H_
#define _EDIT_BOX_H_

#include "UI.h"

#define _EBM_CHANGE 101 //文字内容一旦被改变触发的消息
#define _MAX_LENGTH 1023 //最大文字数量

class CEditBox : public CUI
{
protected:
	char m_Str[_MAX_LENGTH + 1]; //文字
	int m_StrLen; //文字长度
	int m_Color; //颜色
	char m_Face[256]; //外观名称
	int m_Length; //输入的文字数量
	char m_FontID[32]; //文字的ID号

public:
	CEditBox(
		const char* face, //字体外观名称
		int Color, //字体颜色
		int Length, //输入的文字数量
		const char* Text, //默认已经有的文字
		int X, int Y, int W, int H, bool Visible = true, bool Enable = true);

	//得到编辑框上面的文字
	const char* GetText();

	virtual void Init(); //初始化
	//virtual void Enter(); //所属场景进入
	//virtual void Quit(); //所属场景退出
	virtual void End(); //退出
	virtual void OnEvent(int Event, int X, int Y);
	virtual void Render(bool Enable);
};

#endif