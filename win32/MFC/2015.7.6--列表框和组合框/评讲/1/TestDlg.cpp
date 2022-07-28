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
	DDX_Control(pDX, IDC_SCROLLBAR2, vsb);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
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

	// TODO: 在此添加额外的初始化代码
	LoadBmp(&bmpdc, "bmp\\0.bmp");

	//调整界面
	hsb.MoveWindow(0, _GRID_H * _VIEW_H, _GRID_W * _VIEW_W, ::GetSystemMetrics(SM_CYHSCROLL));
	vsb.MoveWindow(_GRID_W * _VIEW_W, 0, ::GetSystemMetrics(SM_CXVSCROLL), _GRID_H * _VIEW_H);

	//初始化数据
	w = _INIT_MAP_W;
	h = _INIT_MAP_H;
	map = new char[w * h];
	for (int i = 0; i < w * h; ++i)
		map[i] = 0;

	//初始化滚动条
	hsb.SetScrollRange(0, w - _VIEW_W);
	hsb.SetScrollPos(0);
	vsb.SetScrollRange(0, h - _VIEW_H);
	vsb.SetScrollPos(0);

	d2.Create(MAKEINTRESOURCE(IDD_DIALOG2), this);

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

		int offsetx = hsb.GetScrollPos();
		int offsety = vsb.GetScrollPos();
		for (int i = 0; i < _VIEW_W * _VIEW_H; ++i)
		{
			int cx = i % _VIEW_W;
			int cy = i / _VIEW_W;
			int dx = cx * _GRID_W;
			int dy = cy * _GRID_H;
			dc.BitBlt(
				dx, dy, _GRID_W, _GRID_H,
				&bmpdc,
				map[(cx + offsetx) + (cy + offsety) * w] * _GRID_W,
				0,
				SRCCOPY);
		}

		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestDlg::LoadBmp(CDC* bmpdc, const char* fn)
{
	HBITMAP hbmp = (HBITMAP)::LoadImageA(0, fn, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!hbmp)
		return;
	CClientDC dc(this);
	bmpdc->CreateCompatibleDC(&dc);
	DeleteObject(bmpdc->SelectObject(hbmp));
	DeleteObject(hbmp);
}
void CTestDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CTestDlg::OnCancel()
{
	delete [] map;
	bmpdc.DeleteDC();
	CDialog::OnCancel();
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

void CTestDlg::OnBnClickedButton2()
{
	dlg1 d;
	if (IDOK == d.DoModal())
	{
		w = d.w;
		h = d.h;
		delete []  map;
		map = new char[w * h];
		for (int i = 0; i < w * h; ++i)
			map[i] = 0;
	}
}

void CTestDlg::OnBnClickedButton3()
{
	d2.ShowWindow(SW_SHOW);
}

void CTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (point.x >= 0 && point.x < _GRID_W * _VIEW_W && point.y >= 0 && point.y < _GRID_H * _VIEW_H)
	{
		int x = point.x / _GRID_W;
		int y = point.y / _GRID_H;
		int offsetx = hsb.GetScrollPos();
		int offsety = vsb.GetScrollPos();
		map[(x + offsetx) + (y + offsety) * w] = d2.sel;
		InvalidateRect(0);
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CTestDlg::OnBnClickedButton1()
{
	CFileDialog fd(FALSE);
	if (IDOK == fd.DoModal())
	{
		CString s = fd.GetPathName();
		//宽4字节
		//高4字节
		//地图:w*h字节
		FILE* pf;
		fopen_s(&pf, s.GetString(), "wb");
		fwrite(&w, 1, 4, pf);
		fwrite(&h, 1, 4, pf);
		fwrite(map, 1, w * h, pf);
		fclose(pf);

		MessageBox("保存成功！");
	}
}
