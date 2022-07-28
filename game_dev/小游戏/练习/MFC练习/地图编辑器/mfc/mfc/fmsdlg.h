#pragma once


// fmsdlg 对话框

class fmsdlg : public CDialogEx
{
	DECLARE_DYNAMIC(fmsdlg)
	CDC bmpdc;

public:
	fmsdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~fmsdlg();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	char c;
	virtual void OnOK();
};
