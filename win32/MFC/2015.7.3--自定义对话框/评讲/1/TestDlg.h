// TestDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#define _GRID_W 30
#define _GRID_H 30
#define _VIEW_W 5
#define _VIEW_H 5
#define _MAP_W 32
#define _MAP_H 32
#define _MAP_S (_MAP_W * _MAP_H)

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

	char map[_MAP_W * _MAP_H];
	char cur_color;
	void update_color(char color)
	{
		//0~4
		cur_color = color;
		CWnd* button[5];
		for (int i = IDC_BUTTON1; i <= IDC_BUTTON5; ++i)
		{
			button[i - IDC_BUTTON1] = GetDlgItem(i);
			button[i - IDC_BUTTON1]->SetWindowTextA("");
		}
		button[cur_color]->SetWindowTextA("√");
	}
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CScrollBar hsb;
	CScrollBar vsb;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CBrush b[5];
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
