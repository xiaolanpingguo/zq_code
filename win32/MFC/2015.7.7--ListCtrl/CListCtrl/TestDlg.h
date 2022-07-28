// TestDlg.h : 头文件
//

#pragma once
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
public:
	CListCtrl lc;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnDropdownCombo1();
	CComboBox cb;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};

//01)风格
//{
//	01)LVS_EX_GRIDLINES：带表格线风格
//}
//02)相关消息
//{
//	01)LVN_COLUMNCLICK：列按下
//	02)NM_CLICK：被点击
//}
//03)相关结构体
//{
//	01)POSITION
//	02)LVHITTESTINFO
//}
//04)相关函数
//{
//	01)SetExtendedStyle
//	02)InsertColumn：插入列
//	03)SetColumnWidth：设置列宽（单位是像素）
//	04)GetColumnWidth：得到列宽
//	05)InsertItem：插入一行的首列
//	06)SetItemText：设置指定行中指定列的字符串
//	07)GetItemText：得到指定行中指定列的字符串
//	08)GetItemPosition：得到指定行的左上角坐标
//	09)GetItemRect：得到指定行的矩形
//	10)DeleteItem：删除指定行
//	11)DeleteAllItems：清空
//	12)GetItemCount：得到当前的行数
//	13)GetSelectedCount：得到选择的行的数量
//	14)GetFirstSelectedItemPosition：得到最初选择的行
//	15)GetNextSelectedItem：得到下一个选择的行
//	16)SubItemHitTest：点击测试
//}