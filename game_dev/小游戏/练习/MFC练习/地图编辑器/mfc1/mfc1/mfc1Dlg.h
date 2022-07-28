
// mfc1Dlg.h : 头文件
//
#include <string>
#pragma once

#define _GRID_W 60
#define _GRID_H 66
#define _VIEW_W 8
#define _VIEW_H 6

// Cmfc1Dlg 对话框
class Cmfc1Dlg : public CDialogEx
{
// 构造
public:
	Cmfc1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFC1_DIALOG };

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
	afx_msg void OnBnClickedButton1();

	bool init;
	char* map;
	int map_w;
	int map_h;
	int hero_x;
	int hero_y;
	int world_x;
	int world_y;
	CDC bmpdc[2];
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
