// TestDlg.h : 头文件
//

#pragma once


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
};

//CWnd类是MFC中对窗口概念的类封装
//01)位置大小相关
//{
//	01)CalcWindowRect：根据客户区大小、位置计算窗口大小、位置
//	02)MoveWindow：移动窗口
//	03)GetClientRect：得到窗口的客户区大小
//}
//02)定时器相关
//{
//	01)SetTimer：设置定时器
//	02)KillTimer：销毁定时器
//}
//03)输出相关
//{
//	01)GetWindowText：得到窗口标题栏文字
//	02)GetWindowTextLength：得到窗口标题栏文字的长度
//	03)SetWindowText：设置窗口标题栏文字
//	04)MessageBox：消息框
//}
//04)状态相关
//{
//	01)ShowWindow：显示或隐藏窗口
//	02)EnableWindow：使窗口是否接收输入
//	03)InvalidateRect：设置窗口有无效区域（投递一个WM_PAINT消息）
//}
//05)风格相关
//{
//	01)GetStyle：得到风格
//	02)ModifyStyle：修改风格
//}
//06)控件相关
//{
//	01)GetDlgItem：得到对话框上面的控件，即返回这个控件窗口的地址CWnd*
//	02)GetDlgItemText：得到对话框上面控件上的文字
//	03)SetDlgItemText：设置对话框上面控件上的文字
//	04)GetDlgItemInt：得到对话框上面控件上的整数文字（文字必须全部是整数，若不是则得到的是0）
//	05)SetDlgItemInt：设置对话框上面控件上的整数文字（文字必须全部是整数）
//}