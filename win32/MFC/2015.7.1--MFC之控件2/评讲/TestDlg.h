// TestDlg.h : 头文件
//

#pragma once
#include <vector>

// CTestDlg 对话框
class CTestDlg : public CDialog
{
// 构造
public:
	CTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	CWnd* item[8];
public:
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedButton1();

	bool jx_ty;
	bool sjkg;
	bool sjhb;
	bool sjhs;
	bool flag;

	struct _TX
	{
		RECT r;
		COLORREF p, b;
	};
	std::vector<_TX> tx;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
