#pragma once


// CGameSel 对话框
#define _GS_CONTINUE  0//继续
#define _GS_STOP      1//停止
#define _GS_GIVEUP    2//放弃

class CGameSel : public CDialog
{
	DECLARE_DYNAMIC(CGameSel)

public:
	CGameSel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameSel();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	int m_iSel;
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	void EndDlg();
};
