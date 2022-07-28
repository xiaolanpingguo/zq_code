// 3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3.h"
#include "3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMy3Dlg 对话框




CMy3Dlg::CMy3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy3Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, &CMy3Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_RADIO3, &CMy3Dlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CMy3Dlg::OnBnClickedRadio4)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMy3Dlg 消息处理程序

BOOL CMy3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);

	flag = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		for(int i = 0; i < v_tx.size(); ++i)
		{
			CPen p1;
			p1.CreatePen(PS_SOLID, 1, v_tx[i].color1);
			CPen* p0 = dc.SelectObject(&p1);

			CBrush b1;
			b1.CreateSolidBrush(v_tx[i].color2);
			CBrush* b0 = dc.SelectObject(&b1);
			if (v_tx[i].juxing)
				Rectangle(dc, v_tx[i].r.left, v_tx[i].r.top,
							v_tx[i].r.right,v_tx[i].r.bottom);
			else
				Ellipse(dc, v_tx[i].r.left, v_tx[i].r.top,
							v_tx[i].r.right, v_tx[i].r.bottom);
			p0->DeleteObject();
			b0->DeleteObject();
		}
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMy3Dlg::OnBnClickedButton2()
{
	if (((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck())
	{
		client_w = 640;
		client_h = 480;
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO4))->GetCheck())
	{
		client_w = 800;
		client_h = 600;
	}
	int sw = ::GetSystemMetrics(SM_CXSCREEN);
	int sh = ::GetSystemMetrics(SM_CYSCREEN);

	RECT r =
	{
		(sw - client_w ) / 2,
		(sh - client_h ) / 2,
		r.left + client_w ,
		r.top + client_h 
	};
	CalcWindowRect(&r);
	MoveWindow(&r);

	int id[] = 
		{
			IDC_RADIO1,IDC_RADIO2,IDC_RADIO3,IDC_RADIO4,IDC_BUTTON2,
			IDC_CHECK3,IDC_CHECK2,IDC_CHECK1
		};
	for (int i = 0; i < sizeof(id) / sizeof(id[0]); ++i)
	{
		((CButton*)GetDlgItem(id[i]))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(id[i]))->ShowWindow(FALSE);
	}
	flag = true;
}

void CMy3Dlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
		((CButton*)GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);

}

void CMy3Dlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
		((CButton*)GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);

}

void CMy3Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (flag)
	{
		_TX tx;
		int sj = 20;
		if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())	
			sj = rand() % 20 + 1;
		tx.r.left = point.x - sj;
		tx.r.top = point.y - sj;
		tx.r.right = point.x + sj;
		tx.r.bottom = point.y + sj;
		tx.color1 = RGB(0, 0, 0);
		if (((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck())
			tx.color1 = RGB(rand() % 255, rand() % 255, rand() % 255);
		tx.color2 = RGB(255, 255, 255);
		if (((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck())
			tx.color2 = RGB(rand() % 255, rand() % 255, rand() % 255);
		if (((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())
			tx.juxing = true;
		else if (((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck())
			tx.juxing = false;

		v_tx.push_back(tx);
		
		InvalidateRect(0);
	}
	CDialog::OnLButtonDown(nFlags, point);
}
