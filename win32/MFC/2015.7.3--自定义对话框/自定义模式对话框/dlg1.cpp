// dlg1.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
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
	DDX_Control(pDX, IDC_EDIT1, e);
}


BEGIN_MESSAGE_MAP(dlg1, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// dlg1 消息处理程序

BOOL dlg1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//首先得到父对话框的地址，然后强转为
	//父对话框类就可以访问它的数据了
	CTestDlg* p = (CTestDlg*)GetParent();
	c = p->color;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void dlg1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	CBrush b1;
	b1.CreateSolidBrush(c);
	CBrush* b0 = dc.SelectObject(&b1);

	dc.Rectangle(0, 0, 100, 100);

	dc.SelectObject(b0);
	b1.DeleteObject();
}

void dlg1::OnOK()
{
	e.GetWindowTextA(str);
	if (str.GetLength() == 0)
	{
		MessageBox("编辑框不能为空！");
		return;
	}
	else
		CDialog::OnOK();
}
