#pragma once
#include "afxwin.h"
#include "GameHall.h"
#include "afxcmn.h"
#include "DataDefine.h"
// CRegister 对话框

class CRegister : public CDialog
{
	DECLARE_DYNAMIC(CRegister)

public:
	CRegister(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegister();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedCancel();
public:
	CEdit m_ID;
public:
	CEdit m_Password;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	CIPAddressCtrl m_IP;
public:
	CButton m_RG;
public:
	CButton m_CL;
public:
	afx_msg void OnBnClickedRg();
public:
	afx_msg void OnBnClickedCl();
};
