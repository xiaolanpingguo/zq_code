#pragma once
#include "afxwin.h"
#include "GameHallDlg.h"

// CPTalkDlg 对话框

class CPTalkDlg : public CDialog
{
	DECLARE_DYNAMIC(CPTalkDlg)

public:
	CPTalkDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPTalkDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lbMessage;
public:
	CEdit m_lbSendMessage;
	_PLAYER* player;
	CGameHallDlg* parent;
public:
	afx_msg void OnPaint();
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedButton2();
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
