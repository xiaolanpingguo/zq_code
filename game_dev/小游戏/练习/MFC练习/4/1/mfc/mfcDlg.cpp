
// mfcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc.h"
#include "mfcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmfcDlg 对话框



CmfcDlg::CmfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CmfcDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CmfcDlg::OnBnClickedButton1)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON2, &CmfcDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CmfcDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CmfcDlg::OnBnClickedButton5)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CmfcDlg 消息处理程序

BOOL CmfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//滚动条
	hs_pos = 0;
	vs_pos = 0;
	((CScrollBar*)GetDlgItem(IDC_SCROLLBAR1))->SetScrollRange(hs_pos, VIEW_W);
	((CScrollBar*)GetDlgItem(IDC_SCROLLBAR2))->SetScrollRange(vs_pos, VIEW_H);

	color = RGB(255, 255, 255);

	for (int y = 0; y < MAP_H; ++y)
	{
		for (int x = 0; x < MAP_W; ++x)
		{
			map[x + y * MAP_W] = RGB(255, 255, 255);
		}
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmfcDlg::OnPaint()
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
		for (int y = 0; y < VIEW_H; ++y)
		{
			for (int x = 0; x < VIEW_W; ++x)
			{
				CBrush b;
				b.CreateSolidBrush(map[x + hs_pos + (vs_pos +y) * MAP_W] );
				CBrush* b0 = dc.SelectObject(&b);
				dc.Rectangle(x * GRID_W, y * GRID_H, x * GRID_W + GRID_W, y * GRID_H + GRID_H);
				b0->DeleteObject();
			}
		}
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfcDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	color = RGB(255, 0, 0);
	CString s;
	s += "当前选中颜色：红色";
	SetWindowText(s.GetString());
}


void CmfcDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	color = RGB(255, 255, 255);
	CString s;
	s += "当前选中颜色：白色";
	SetWindowText(s.GetString());
}


void CmfcDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

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
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
	{
						  pos = nPos;
						  break;
	}
	}

	hs_pos = pos;
	pScrollBar->SetScrollPos(hs_pos);
	InvalidateRect(0);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CmfcDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
	{
						  pos = nPos;
						  break;
	}
	}

	vs_pos = pos;
	pScrollBar->SetScrollPos(vs_pos);
	InvalidateRect(0);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CmfcDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	color = RGB(0, 255, 0);
	CString s;
	s += "当前选中颜色：绿色";
	SetWindowText(s.GetString());
}


void CmfcDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	color = RGB(0, 0, 255);
	CString s;
	s += "当前选中颜色：蓝色";
	SetWindowText(s.GetString());
}


void CmfcDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	color = RGB(0, 0, 0);
	CString s;
	s += "当前选中颜色：黑色";
	SetWindowText(s.GetString());
}


void CmfcDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CmfcDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (point.x >= 0 && point.x <= VIEW_W * GRID_W
		&& point.y >= 0 && point.y <= VIEW_H * GRID_H)
	{
		int x = point.x / GRID_W;
		int y = point.y / GRID_W;
		map[x + hs_pos + (y + vs_pos) * MAP_W] = color;
	}
	InvalidateRect(0);
	CDialogEx::OnLButtonDown(nFlags, point);
}
