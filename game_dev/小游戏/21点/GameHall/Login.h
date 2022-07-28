#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CLogin 对话框

class CLogin : public CDialog
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogin();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButton2();
public:
	afx_msg void OnBnClickedButton4();
public:
	afx_msg void OnBnClickedButton1();
public:
	CIPAddressCtrl m_IpAddr;
public:
	CEdit m_ID;
public:
	CEdit m_Password;
public:
	CButton m_Login;
public:
	CButton m_RG;
public:
	CButton m_CL;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
