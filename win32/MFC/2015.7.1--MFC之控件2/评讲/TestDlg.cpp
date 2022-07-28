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
	ON_BN_CLICKED(IDC_RADIO3, &CTestDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CTestDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
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

	//得到所有控件
	for (int i = 0; i < 8; ++i)
		item[i] = GetDlgItem(i + IDC_RADIO1);

	//设置初始情况
	((CButton*)(item[0]))->SetCheck(1);
	item[7]->EnableWindow(0);
	flag = false;

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

		for (int i = 0; i < tx.size(); ++i)
		{
			CPen p1;
			p1.CreatePen(PS_SOLID, 1, tx[i].p);
			CBrush b1;
			b1.CreateSolidBrush(tx[i].b);
			CPen* p0 = dc.SelectObject(&p1);
			CBrush* b0 = dc.SelectObject(&b1);

			if (jx_ty)
				dc.Rectangle(&tx[i].r);
			else
				dc.Ellipse(&tx[i].r);

			dc.SelectObject(p0);
			dc.SelectObject(b0);

			b1.DeleteObject();
			p1.DeleteObject();
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


void CTestDlg::OnBnClickedRadio3()
{
	item[7]->EnableWindow(1);
}

void CTestDlg::OnBnClickedRadio4()
{
	item[7]->EnableWindow(1);
}

void CTestDlg::OnBnClickedButton1()
{
	jx_ty = ((CButton*)item[0])->GetCheck() == TRUE;
	sjhb = ((CButton*)item[4])->GetCheck() == TRUE;
	sjhs = ((CButton*)item[5])->GetCheck() == TRUE;
	sjkg = ((CButton*)item[6])->GetCheck() == TRUE;
	flag = true;

	int w, h;
	if (((CButton*)item[2])->GetCheck())
	{
		w = 640;
		h = 480;
	}
	else
	{
		w = 800;
		h = 600;
	}

	MoveWindow(0, 0, w, h);

	for (int i = 0; i < 8; ++i)
		item[i]->ShowWindow(SW_HIDE);
}

void CTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (flag)
	{
		_TX t;
		t.r.left = point.x;
		t.r.top = point.y;
		if (sjkg)
		{
			t.r.right = t.r.left + (rand() % 50 + 50);
			t.r.bottom = t.r.top + (rand() % 50 + 50);
		}
		else
		{
			t.r.right = t.r.left + 75;
			t.r.bottom = t.r.top + 75;
		}
		t.p = sjhb ? RGB(rand() % 256, rand() % 256, rand() % 256) : RGB(0, 0, 0);
		t.b = sjhs ? RGB(rand() % 256, rand() % 256, rand() % 256) : RGB(255, 255, 255);
		tx.push_back(t);
		InvalidateRect(0);
	}

	CDialog::OnLButtonDown(nFlags, point);
}
