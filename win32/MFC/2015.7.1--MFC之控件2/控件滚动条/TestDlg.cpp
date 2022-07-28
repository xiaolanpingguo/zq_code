// TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"

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


// CTestDlg 对话框




CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR1, hs1);
	DDX_Control(pDX, IDC_SCROLLBAR3, vs1);
	DDX_Control(pDX, IDC_SCROLLBAR2, hs2);
	DDX_Control(pDX, IDC_SCROLLBAR4, vs2);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CTestDlg 消息处理程序

void CTestDlg::f()
{
	int pos[]
	=
	{
		hs1.GetScrollPos(),
		vs1.GetScrollPos(),
		hs2.GetScrollPos(),
		vs2.GetScrollPos(),
		GetScrollPos(SB_HORZ),
		GetScrollPos(SB_VERT)
	};
	CString s;
	s.Format(
		"水平1(0-%d-5)、垂直1(0-%d-7)、水平2(0-%d-9)、垂直2(0-%d-11)、水平3(0-%d-13)、垂直3(0-%d-15)",
		pos[0], pos[1], pos[2], pos[3], pos[4], pos[5]);
	SetWindowTextA(s.GetString());
}

BOOL CTestDlg::OnInitDialog()
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
	ModifyStyle(0, WS_HSCROLL | WS_VSCROLL);

	//设置滚动条范围
	hs1.SetScrollRange(0, 5); //CScrollBar::SetScrollRange
	vs1.SetScrollRange(0, 7);
	hs2.SetScrollRange(0, 9);
	vs2.SetScrollRange(0, 11);
	SetScrollRange(SB_HORZ, 0, 13); //CWnd::SetScrollRange
	SetScrollRange(SB_VERT, 0, 15);

	//设置滚动条位置
	hs1.SetScrollPos(1); //CScrollBar::SetScrollPos
	vs1.SetScrollPos(2);
	hs2.SetScrollPos(3);
	vs2.SetScrollPos(4);
	SetScrollPos(SB_HORZ, 5); //CWnd::SetScrollPos
	SetScrollPos(SB_VERT, 6);

	f();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//如果是风格的滚动条，那么pScrollBar会被设置为0，如果是
//控件滚动条那么pScrollBar会被设置会触发该消息的控件滚动
//条的地址
void CTestDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int pos;
	if (pScrollBar)
		pos = pScrollBar->GetScrollPos();
	else
		pos = GetScrollPos(SB_HORZ);

	switch (nSBCode)
	{
	case SB_LINELEFT:
	case SB_PAGELEFT:
		{
			pos -= 1;
			break;
		}
	case SB_LINERIGHT:
	case SB_PAGERIGHT:
		{
			pos += 1;
			break;
		}
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK :
		{
			pos = nPos;
			break;
		}
	}

	if (pScrollBar)
		pScrollBar->SetScrollPos(pos);
	else
		SetScrollPos(SB_HORZ, pos);

	f();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTestDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos;
	if (pScrollBar)
		pos = pScrollBar->GetScrollPos();
	else
		pos = GetScrollPos(SB_VERT);

	switch (nSBCode)
	{
	case SB_LINEUP:
	case SB_PAGEUP:
		{
			pos -= 1;
			break;
		}
	case SB_LINEDOWN:
	case SB_PAGEDOWN:
		{
			pos += 1;
			break;
		}
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK :
		{
			pos = nPos;
			break;
		}
	}

	if (pScrollBar)
		pScrollBar->SetScrollPos(pos);
	else
		SetScrollPos(SB_VERT, pos);

	f();

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
