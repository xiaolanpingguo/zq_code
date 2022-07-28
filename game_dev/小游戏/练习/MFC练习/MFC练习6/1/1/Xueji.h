#pragma once
#include "afxwin.h"


// Xueji 对话框

class Xueji : public CDialog
{
	DECLARE_DYNAMIC(Xueji)

public:
	Xueji(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Xueji();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox cb1;
public:
	CComboBox cb2;
public:
	CEdit ed1;
public:
	CEdit ed2;
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedOk();

protected:
	virtual void OnCancel();
};
