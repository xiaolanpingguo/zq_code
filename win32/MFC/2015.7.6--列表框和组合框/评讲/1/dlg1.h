#pragma once
#include "afxwin.h"


// dlg1 对话框

class dlg1 : public CDialog
{
	DECLARE_DYNAMIC(dlg1)

public:
	dlg1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~dlg1();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int w, h;
	CEdit e1;
	CEdit e2;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
