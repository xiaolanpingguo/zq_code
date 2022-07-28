// 3Dlg.h : 头文件
//

#pragma once
#include <vector>

// CMy3Dlg 对话框
class CMy3Dlg : public CDialog
{
// 构造
public:
	CMy3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY3_DIALOG };

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

	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	struct _TX
	{
		bool juxing;
		RECT r;
		COLORREF color1;
		COLORREF color2;
	};
	int client_w;
	int client_h;
	bool flag;
	std::vector<_TX> v_tx;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
