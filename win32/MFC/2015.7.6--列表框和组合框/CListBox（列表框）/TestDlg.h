// TestDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


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
public:
	CListBox lb;
	afx_msg void OnBnClickedButton1();
	CEdit e1;
	CEdit e2;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnLbnSelchangeList1();
};

//01)AddString：添加字符串
//02)GetTextLen：得到指定位置的字符串的长度
//03)GetText：得到指定位置的字符串
//04)GetCurSel：得到当前的选择位置
//05)SetCurSel：设置当前的选择位置
//06)InsertString：插入字符串
//07)GetCount：得到字符串数量
//08)DeleteString：删除字符串
//09)ResetContent：清空