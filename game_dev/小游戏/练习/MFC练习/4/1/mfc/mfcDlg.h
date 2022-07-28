
// mfcDlg.h : 头文件
//

#pragma once
#define MAP_W 10
#define MAP_H 10

#define VIEW_W 5
#define VIEW_H 5

#define GRID_W 50
#define GRID_H 50

// CmfcDlg 对话框
class CmfcDlg : public CDialogEx
{
// 构造
public:
	CmfcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFC_DIALOG };

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
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();

	COLORREF map[MAP_W * MAP_H];
	int hs_pos;
	int vs_pos;
	COLORREF color;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	virtual void OnOK();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
