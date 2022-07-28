// TestDlg.h : 头文件
//

#pragma once

#include "TcpClient.h"
#include "..\\GameProtocol.h"
#include <string>
#include <map>
#include "afxcmn.h"
#include "afxwin.h"

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

	//客户端
	CTcpClient tc;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void SetScene(bool p);
	afx_msg void OnBnClickedButton1();
	std::string m_IP, m_Nick_Name;
	CIPAddressCtrl ip_a_c;

	//游戏
	char map[_GAME_MAP_S]; //地图
	std::map<std::string, POINT> all_player; //游戏玩家
	CListBox lb;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
