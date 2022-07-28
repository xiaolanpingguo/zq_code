#ifndef _UI_H_
#define _UI_H_

#include <string>

//UI的状态
//1)可见
//  1)可用
//  2)不可用
//2)不可见

//UI的功能
//接收输入
//进行输出
//通知场景

//UI接收的来自引擎的事件，而每种UI要根据
//自己的特点判断来自引擎的事件然后产生UI
//自己的消息，比如我们写一个按钮UI，那么
//一个按钮UI收到了鼠标左键在内部按下、鼠
//标左键在内部抬起，我们就可以判断出来用
//户在这个按钮UI上做了一个点击操作，然后
//我们就可以把这个点击操作写成一个按钮的
//消息，并且通知所属的场景
#define _UIE_CURSOR_ENTER 0 //光标进入
#define _UIE_CURSOR_QUIT 1 //光标退出
#define _UIE_CURSOR_MOVE_IN 2 //光标在内部移动
#define _UIE_CURSOR_MOVE_OUT 3 //光标在外部移动
#define _UIE_L_DOWN_IN 4 //鼠标左键在内部按下
#define _UIE_L_DOWN_OUT 5 //鼠标左键在外部按下
#define _UIE_L_UP_IN 6 //鼠标左键在内部抬起
#define _UIE_L_UP_OUT 7 //鼠标左键在外部抬起
#define _UIE_R_DOWN_IN 8 //鼠标右键在内部按下
#define _UIE_R_DOWN_OUT 9 //鼠标右键在外部按下
#define _UIE_R_UP_IN 10 //鼠标右键在内部抬起
#define _UIE_R_UP_OUT 11 //鼠标右键在外部抬起
#define _UIE_K_DOWN 12 //键盘按下
#define _UIE_K_UP 13 //键盘抬起
#define _UIE_CHAR 14 //字符

class CScene;

class CUI
{
	friend class CGameEngine;
	friend class CScene;

protected:
	int m_X, m_Y, m_W, m_H; //矩形
	bool m_Visible; //可见性
	bool m_Enable; //可用性
	std::string m_ID; //名字
	CScene* m_Scene; //所属的场景

public:
	CUI(int X, int Y, int W, int H, bool Visible = true, bool Enable = true);
	virtual ~CUI();

	void SetRect(int X, int Y, int W, int H);
	void GetRect(int* X, int* Y, int* W, int* H);
	void SetVisible(bool Visible);
	bool GetVisible();
	void SetEnable(bool Enable);
	bool GetEnable();

	virtual void Init(); //初始化
	virtual void Enter(); //所属场景进入
	virtual void Quit(); //所属场景退出
	virtual void End(); //退出
	
	//当Event是鼠标事件的时候，X、Y表示当前光标的位置
	//当Event是_UIE_K_DOWN或_UIE_K_UP的时候，X为按下的键的键值
	//当Event是_UIE_CHAR的时候，X为字符的编码，Y为双字节标志（为0表示单字节文字，为1表示双字节文字）
	virtual void OnEvent(int Event, int X, int Y); //来自引擎的事件
	virtual void Render(bool Enable); //输出
};

#endif