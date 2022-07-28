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

	struct _TX
	{
		POINT pos; //位置
		char dir; //方向
		COLORREF color; //颜色
		bool jx; //矩形
	};
	std::vector<_TX> tx;
	
public:
	void createTX(bool jx, CPoint point)
	{
		_TX tuxing;
		tuxing.pos.x = point.x;
		tuxing.pos.y = point.y;
		tuxing.dir = rand() % 4;
		tuxing.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		tuxing.jx = jx;
		tx.push_back(tuxing);
	}
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
