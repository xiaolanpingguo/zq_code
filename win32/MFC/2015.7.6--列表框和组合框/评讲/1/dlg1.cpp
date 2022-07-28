// dlg1.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "dlg1.h"


// dlg1 对话框

IMPLEMENT_DYNAMIC(dlg1, CDialog)

dlg1::dlg1(CWnd* pParent /*=NULL*/)
	: CDialog(dlg1::IDD, pParent)
{

}

dlg1::~dlg1()
{
}

void dlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, e1);
	DDX_Control(pDX, IDC_EDIT2, e2);
}


BEGIN_MESSAGE_MAP(dlg1, CDialog)
	ON_BN_CLICKED(IDOK, &dlg1::OnBnClickedOk)
END_MESSAGE_MAP()


// dlg1 消息处理程序

void dlg1::OnBnClickedOk()
{
	CString s[2];
	e1.GetWindowTextA(s[0]);
	e2.GetWindowTextA(s[1]);
	if (s[0].GetLength() == 0 || s[1].GetLength() == 0)
	{
		MessageBox("有数据没有填写！");
		return;
	}
	w = atoi(s[0].GetString());
	h = atoi(s[1].GetString());
	if (w == 0 || h == 0)
	{
		MessageBox("数据有错误！");
		return;
	}
	if (w < 8 || w > 32 || h < 6 || h > 24)
	{
		MessageBox("数据超出范围！");
		return;
	}

	OnOK();
}

BOOL dlg1::OnInitDialog()
{
	CDialog::OnInitDialog();

	e1.SetWindowTextA("宽度8~32");
	e2.SetWindowTextA("宽度6~24");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
