// 2Dlg.h : 头文件
//

#pragma once
#define _CLIENT_W 640
#define _CLIENT_H 480

#include <list>
// CMy2Dlg 对话框
class CMy2Dlg : public CDialog
{
// 构造
public:
	CMy2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY2_DIALOG };

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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	struct OBJ
	{
		POINT p;
		int color;
		int dir;
		int flag;
	};
	std::list<OBJ> l_obj;
protected:
	virtual void OnOK();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
