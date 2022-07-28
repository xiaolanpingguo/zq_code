// TestDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "dlg1.h"
#include "dlg2.h"

#define _GRID_W 60 
#define _GRID_H 66
#define _VIEW_W 8
#define _VIEW_H 6
#define _INIT_MAP_W 16
#define _INIT_MAP_H 12

// CTestDlg 对话框
class CTestDlg : public CDialog
{
	dlg2 d2;

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
	//加载位图
	void LoadBmp(CDC* bmpdc, const char* fn);
	CDC bmpdc;
	virtual void OnOK();
	virtual void OnCancel();

public:
	CScrollBar hsb;
	CScrollBar vsb;
	int w, h;
	char* map;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
};
