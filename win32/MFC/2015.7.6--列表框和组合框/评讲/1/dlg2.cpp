// dlg2.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "dlg2.h"
#include "TestDlg.h"

// dlg2 对话框

IMPLEMENT_DYNAMIC(dlg2, CDialog)

dlg2::dlg2(CWnd* pParent /*=NULL*/)
	: CDialog(dlg2::IDD, pParent)
{

}

dlg2::~dlg2()
{
}

void dlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(dlg2, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// dlg2 消息处理程序

void dlg2::OnPaint()
{
	CPaintDC dc(this);

	CTestDlg* p = (CTestDlg*)GetParent();

	dc.BitBlt(0, 0, 180, 66, &p->bmpdc, 0, 0, SRCCOPY);

	dc.TextOutA(60 * sel, 0, "★", 2);
}

BOOL dlg2::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	sel = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void dlg2::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (point.x >= 0 && point.x < 180 && point.y >= 0 && point.y < 66)
	{
		sel = point.x / 60;
		InvalidateRect(0);
	}

	CDialog::OnLButtonDown(nFlags, point);
}
