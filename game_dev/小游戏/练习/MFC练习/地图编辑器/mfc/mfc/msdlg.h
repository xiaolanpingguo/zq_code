#pragma once
#include "afxwin.h"


// msdlg 对话框



class msdlg : public CDialogEx
{
	DECLARE_DYNAMIC(msdlg)

public:
	msdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~msdlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	int w;
	int h;
	virtual BOOL OnInitDialog();
	CEdit e_w;
	CEdit e_h;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
};
