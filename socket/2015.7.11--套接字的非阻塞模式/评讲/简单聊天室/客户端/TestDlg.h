// TestDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#define FD_SETSIZE 256
#include <Winsock2.h>
#include "afxwin.h"
#pragma comment(lib, "Ws2_32.lib")


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
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButton1();
	CString nick_name;
	CIPAddressCtrl piac;
	SOCKET s_server;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListBox lb;
	afx_msg void OnBnClickedButton2();
	bool connect_ok;
};
