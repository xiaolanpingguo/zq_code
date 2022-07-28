#pragma once

#include "DataDefine.h"
#include "afxwin.h"
#include "GameSel.h"
// CGame 对话框

class CGame : public CDialog
{
	DECLARE_DYNAMIC(CGame)

public:
	CGame(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGame();

	int game_MakeChoice();
	CGameSel gs;
	bool showsel;


// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	CListBox m_lbMessage;
public:
	CEdit m_edSendMessage;
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
