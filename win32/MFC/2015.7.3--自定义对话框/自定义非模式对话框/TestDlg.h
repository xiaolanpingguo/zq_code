// TestDlg.h : 头文件
//

#pragma once
#include "dlg1.h"
#include <vector>
#include "afxwin.h"

// CTestDlg 对话框
class CTestDlg : public CDialog
{
	//非模式对话框不能用DoMadol呼叫出来，而且
	//模式对话框对象就是一个局部变量，一旦出了
	//呼叫它的函数，那么模式对话框就消失了，也
	//就是模式对话框的生存周期结束了
	
	//非模式对话框的生存周期应该和主对话框一样
	//所以直接定义非模式对话框类对象为主对话框
	//类的成员变量，然后可以用Create函数来创建
	//这个对话框，用ShowWindow来显示或隐藏它，
	//注意如果是非模式对话框，那么EndDialog的功
	//能也是隐藏它（OnOK和OnCancel中就调用了EndDialog的）
	dlg1 d;

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
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	struct TX
	{
		bool jx;
		POINT pos;
	};
	std::vector<TX> tx;
	afx_msg void OnEnChangeEdit1();
	CEdit e;
};
