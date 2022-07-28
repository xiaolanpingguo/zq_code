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
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
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

	//固定客户区大小的对话框窗口
	int sw = ::GetSystemMetrics(SM_CXSCREEN);
	int sh = ::GetSystemMetrics(SM_CYSCREEN);
	RECT r
		=
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		r.left + _CLIENT_W,
		r.top + _CLIENT_H
	};
	CalcWindowRect(&r);
	MoveWindow(&r);

	//得到主设备
	CClientDC dc(this);

	//加载位图到CDC中，位图在被选入到设备中的时候，实际上会
	//被复制一份到设备中，也就是说设备中有一幅和hbmp一模一样
	//的位图对象，所以我们选入之后可以直接把原来的hbmp删除了
	HBITMAP hbmp;
	hbmp = (HBITMAP)LoadImageA(0, "0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc[0].CreateCompatibleDC(&dc);
	::DeleteObject(bmpdc[0].SelectObject(hbmp));
	::DeleteObject(hbmp);
	hbmp = (HBITMAP)LoadImageA(0, "1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc[1].CreateCompatibleDC(&dc);
	::DeleteObject(bmpdc[1].SelectObject(hbmp));
	::DeleteObject(hbmp);

	x = y = 0;
	left_right = true;

	SetTimer(0, 33, 0);

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
		//主绘图设备
		CPaintDC dc(this);

		//绘制位图
		dc.BitBlt(0, 0, _CLIENT_W, _CLIENT_H, &bmpdc[0], 0, 0, SRCCOPY);

		dc.TransparentBlt(
			x, y, 100, 100,
			&bmpdc[1],
			0, 0, 100, 100,
			RGB(0, 255, 0));

		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	bmpdc[1].DeleteDC();
	bmpdc[0].DeleteDC();

	CDialog::OnCancel();
}

void CTestDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//对话框窗口对键盘的响应是有筛选的，比如VK_LEFT到VK_DOWN
	//是无法响应的，而有些是可以相应的比如字母键、数字键等是
	//可以的，如果要想得到原始的消息，可以通过重写PreTranslateMessage
	//来得到所有的消息

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

//BOOL CTestDlg::PreTranslateMessage(MSG* pMsg)
//{
//	switch (pMsg->message)
//	{
//	case WM_KEYDOWN:
//		{
//			bool move = true;
//			switch (pMsg->wParam)
//			{
//			case VK_UP: y -= _HERO_SPEED; break;
//			case VK_DOWN: y += _HERO_SPEED; break;
//			case VK_LEFT: x -= _HERO_SPEED; break;
//			case VK_RIGHT: x += _HERO_SPEED; break;
//			default: move = false;
//			}
//			if (move)
//				InvalidateRect(0);
//			break;
//		}
//	}
//
//	return CDialog::PreTranslateMessage(pMsg);
//}

void CTestDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (left_right)
	{
		x += 5;
		if (x >= _CLIENT_W - 100)
			left_right = false;
	}
	else
	{
		x -= 5;
		if (x < 0)
			left_right = true;
	}
	InvalidateRect(0);

	CDialog::OnTimer(nIDEvent);
}

void CTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	x = point.x;
	y = point.y;

	CDialog::OnLButtonDown(nFlags, point);
}

BOOL CTestDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//不让操作系统去刷新客户区背景
	return TRUE;

	return CDialog::OnEraseBkgnd(pDC);
}
