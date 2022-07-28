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
	DDX_Control(pDX, IDC_SCROLLBAR1, hsb);
	DDX_Control(pDX, IDC_SCROLLBAR3, vsb);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDlg::OnBnClickedButton5)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CTestDlg 消息处理程序

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

	//设置初始地图和颜色
	update_color(4);
	for (int i = 0; i < _MAP_S; ++i)
		map[i] = cur_color;

	//设置滚动条
	hsb.MoveWindow(0, _GRID_H * _VIEW_H, _GRID_W * _VIEW_W, ::GetSystemMetrics(SM_CYHSCROLL));
	vsb.MoveWindow(_GRID_W * _VIEW_W, 0, ::GetSystemMetrics(SM_CXVSCROLL), _GRID_H * _VIEW_H);
	hsb.SetScrollRange(0, _MAP_W - _VIEW_W);
	hsb.SetScrollPos(0);
	vsb.SetScrollRange(0, _MAP_H - _VIEW_H);
	vsb.SetScrollPos(0);

	COLORREF color[]
	= 
	{
		RGB(255, 0, 0),
		RGB(0, 255, 0),
		RGB(0, 0, 255),
		RGB(127, 127, 127),
		RGB(255, 255, 255),
	};
	for (int i = 0; i < 5; ++i)
		b[i].CreateSolidBrush(color[i]);

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
		CPaintDC dc(this);

		//得到老的画刷
		CBrush* old_brush = dc.GetCurrentBrush();

		int vx = hsb.GetScrollPos();
		int vy = vsb.GetScrollPos();

		for (int i = 0; i < _VIEW_W * _VIEW_H; ++i)
		{
			int x = i % _VIEW_W;
			int y = i / _VIEW_W;
			int dx = x * _GRID_W;
			int dy = y * _GRID_H;
			char color = map[(x + vx) + (y + vy) * _MAP_W];
			dc.SelectObject(&b[color]);
			dc.Rectangle(dx, dy, dx + _GRID_W, dy + _GRID_H);
		}

		dc.SelectObject(old_brush);
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestDlg::OnBnClickedButton1()
{
	update_color(0);
}

void CTestDlg::OnBnClickedButton2()
{
	update_color(1);
}

void CTestDlg::OnBnClickedButton3()
{
	update_color(2);
}

void CTestDlg::OnBnClickedButton4()
{
	update_color(3);
}

void CTestDlg::OnBnClickedButton5()
{
	update_color(4);
}

void CTestDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int pos = pScrollBar->GetScrollPos();
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
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		{
			pos = nPos;
			break;
		}
	}

	pScrollBar->SetScrollPos(pos);
	InvalidateRect(0);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTestDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = pScrollBar->GetScrollPos();
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
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		{
			pos = nPos;
			break;
		}
	}

	pScrollBar->SetScrollPos(pos);
	InvalidateRect(0);

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CTestDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CTestDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	for (int i = 0; i < 5; ++i)
		b[i].DeleteObject();

	CDialog::OnCancel();
}

void CTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x >= 0 && point.x < _VIEW_W * _GRID_W &&
		point.y >= 0 && point.y < _VIEW_H * _GRID_H)
	{
		int vx = hsb.GetScrollPos();
		int vy = vsb.GetScrollPos();
		int cx = point.x / _GRID_W;
		int cy = point.y / _GRID_H;
		map[(cx + vx) + (cy + vy) * _MAP_W] = cur_color;
		InvalidateRect(0);
	}

	CDialog::OnLButtonDown(nFlags, point);
}
