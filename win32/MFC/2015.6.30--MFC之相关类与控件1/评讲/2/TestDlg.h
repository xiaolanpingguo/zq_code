// TestDlg.h : 头文件
//

#pragma once

#define _GRID_W 64
#define _GRID_H 48
#define _VIEW_W 10
#define _VIEW_H 8
#define _MAP_W 32
#define _MAP_H 32
#define _CLIENT_W (_GRID_W * _VIEW_W) //没有计算滚动条的宽
#define _CLIENT_H (_GRID_H * _VIEW_H) //没有计算滚动条的高

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
	CDC bmpdc;
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
