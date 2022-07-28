// fmsdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc.h"
#include "fmsdlg.h"
#include "afxdialogex.h"


// fmsdlg 对话框

IMPLEMENT_DYNAMIC(fmsdlg, CDialogEx)

fmsdlg::fmsdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(fmsdlg::IDD, pParent)
{

}

fmsdlg::~fmsdlg()
{
}

void fmsdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(fmsdlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// fmsdlg 消息处理程序


void fmsdlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 180, 66, &bmpdc, 0, 0, SRCCOPY);

}


BOOL fmsdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CClientDC dc(this);
	HBITMAP hbmp;
	hbmp = (HBITMAP)LoadImageA(0, "0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc.CreateCompatibleDC(&dc);
	::DeleteObject(bmpdc.SelectObject(hbmp));
	::DeleteObject(hbmp);

	c = 0;

	CString s;
	s = "当前选择为：草";
	SetWindowText(s);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void fmsdlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (point.y >= 0 && point.y <= 66)
	{
		CString s;
		if (point.x >= 0 && point.x <= 60)
		{
			s = "当前选择为：草";
			SetWindowText(s);
			c = 0;
		}
		if (point.x >60 && point.x <= 120)
		{
			s = "当前选择为：树";
			SetWindowText(s);
			c = 1;
		}
		if (point.x >120 && point.x <= 180)
		{
			s = "当前选择为：障碍";
			SetWindowText(s);
			c = 2;
		}
	}
	InvalidateRect(0);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void fmsdlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	c = -1;
	CDialogEx::OnOK();
}
