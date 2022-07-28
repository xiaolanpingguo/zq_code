#pragma once
#include "afxwin.h"


// dlg1 对话框

class dlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(dlg1)

public:
	dlg1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~dlg1();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();

	struct STUDENT
	{
		CString name;
		CString sex;
		short age;
		int id;
	};

	STUDENT stu;
	int hang;
	int lie;
	bool add;

	CEdit id_edit;
	CEdit name_edit;
	CComboBox sex_cb;
	CComboBox age_cb;

	afx_msg void OnCbnDropdownCombo1();
	afx_msg void OnCbnDropdownCombo2();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBnClickedButton2();
};
