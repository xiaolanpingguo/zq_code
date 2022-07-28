// GameHallDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "..\\GameProtocol\\Protocol.h"
#include "..\\GameProtocol\\LoginProtocol.h"
#include "..\\GameProtocol\\HallProtocol.h"
#include "..\\GameProtocol\\BlackJackProtocol.h"
#include <map>
#include <string>
#include "DataType.h"
#include "ProtocolTranslate.h"
#include "DataDefine.h"
#include "Game.h"

#define _POKERS_MAX        52
#define _PLAYER_MAX_POKERS  21

// CGameHallDlg 对话框
class CGameHallDlg : public CDialog
{
// 构造
public:
	CGameHallDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GAMEHALL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
// 实现
protected:
	HICON m_hIcon;

	CGame m_GameDlg;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CListBox m_lbOnlinePlayers;
	CListBox m_lbMessage;
	CEdit m_edSendMessage;
	CScrollBar m_sbRoomV;
	CStatic m_stName;
	CStatic m_stScore;
	CStatic m_stHistory;

	//游戏相关
	struct _POKER
	{
		int num;
		POINT tex;
	};

	_POKER m_Pokers[52];

	int m_MyPokers[_PLAYER_MAX_POKERS];
	int m_iPlayerCurPoint;
	int m_MyPokersNum;

	_PLAYER* m_Adversary;
	int m_AdversaryPokers[_PLAYER_MAX_POKERS];
	int m_AdversaryPokersNum;

protected:
	virtual void OnOK();
	virtual void OnCancel();
	
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnLbnDblclkList1();

	//-------------------------------------------------------------------
	//功能函数
	//-------------------------------------------------------------------
	void InitPMDispatcher();//初始化派发器内部的协议

	void gh_GameHallInit();//大厅初始化
	void gh_GameHallRun();//大厅运行
	void gh_GameHallEnd();//大厅结束

	//------------------
	//登陆相关
	//------------------
	void gh_LoginSuccess(_CNET_EVENT& ne);//登陆成功
	void gh_NewClientLogin(_CNET_EVENT& ne);//新玩家登入

	//------------------
	//大厅相关
	//------------------
	void gh_ChangeDataSuccess(_CNET_EVENT& ne);//修改玩家资料成功
	void gh_ChangeDataFailed(_CNET_EVENT& ne);//修改玩家资料失败
	void gh_PublicTalk(_CNET_EVENT& ne);//公共聊天
	void gh_PrivateTalk(_CNET_EVENT& ne);//私人聊天
	void gh_PlayerOffLine(_CNET_EVENT& ne);//玩家离线
	void gh_EnterRoomSuccess(_CNET_EVENT& ne);//进入房间成功
	void gh_EnterRoomFail(_CNET_EVENT& ne);//进入房间失败
	void gh_ReadSuccess(_CNET_EVENT& ne);//准备成功
	void gh_ExitRoomSuccess(_CNET_EVENT& ne);//退出房间成功
	void gh_ReadyCancelSuccess(_CNET_EVENT& ne);//取消准备成功

	//------------------
	//游戏相关
	//------------------
	void gh_NewGame(_CNET_EVENT& ne);//收到开始新游戏消息
	void gh_UpdatePlayerData(_CNET_EVENT& ne);//更新玩家状态
	void gh_MakeChoice(_CNET_EVENT& ne);//指定玩家做出选择
	void gh_TalkInGame(_CNET_EVENT& ne);//玩家进行聊天
	void gh_GetNew(_CNET_EVENT& ne);//玩家获取到新的牌
	void gh_Win_21(_CNET_EVENT& ne);//玩家获得21点胜利
	void gh_LoseOutRange(_CNET_EVENT& ne);//玩家因爆点失败
	void gh_LoseGiveUp(_CNET_EVENT& ne);//玩家因放弃本局失败
	void gh_LoseRunAway(_CNET_EVENT& ne);//玩家因逃跑本局失败
	void gh_WinBigger(_CNET_EVENT& ne);//玩家最终比点数获胜
	void gh_Draw(_CNET_EVENT& ne);//玩家最终比点数平局
	void gh_GameEnd(_CNET_EVENT& ne);//收到游戏结束消息

public:
	afx_msg void OnBnClickedButton2();
public:
	afx_msg void OnBnClickedButton5();
public:
	CButton m_btRead;
};