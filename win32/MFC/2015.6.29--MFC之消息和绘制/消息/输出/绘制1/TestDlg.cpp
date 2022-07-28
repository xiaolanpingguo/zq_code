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

//每个对话框程序的主对话框中，默认就为对话框添加了
//响应WM_PAINT消息的函数OnPaint，我们的所有绘制代码
//都应该放在OnPaint函数中，在OnPaint函数中我们使用
//CPaintDC来进行绘制，CPaintDC的构造、析构中就分别
//调用了BeginPaint和EndPaint了，所以我们不需要再去
//调用这两个函数，其它所有的绘制函数都被封装成为了
//CPaintDC的成员函数（严格来说这些绘制函数都不是CPaintDC
//的成员函数，而是CPaintDC继承自CDC的成员函数，而CDC
//的两个子类除了有OnPaint函数中专用的CPaintDC，还有
//一个叫CClientDC的子类，这个子类的构造和析构分别调
//用了GetDC和ReleaseDC两个函数）
//所有的GDI对象都被封装成为了类，分别如下
//CPen:CreatePen
//CBrush:CreateSolidBrush、CreateHatchBrush
//CFont:CreateFont
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

		//设置文字背景为透明
		dc.SetBkMode(TRANSPARENT);

		//创建画笔
		CPen p1;
		p1.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

		//将画笔选入到设备
		CPen* p0 = dc.SelectObject(&p1);

		//绘制矩形
		dc.Rectangle(100, 100, 200, 200);

		//创建画刷
		CBrush b1;
		b1.CreateHatchBrush(HS_DIAGCROSS, RGB(0, 255, 0));

		//将画刷选入到设备
		CBrush* b0 = dc.SelectObject(&b1);

		//绘制椭圆
		dc.Ellipse(50, 100, 300, 150);

		//创建字体
		CFont f1;
		f1.CreateFontA(
			30,
			15,
			0,
			0,
			FW_HEAVY,
			false,
			false,
			false,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			"黑体");

		//将字体选入到设备
		CFont* f0 = dc.SelectObject(&f1);

		dc.TextOutA(0, 0, "123abc你好", 10);

		//没有选入到设备中的GDI对象我们必须
		//手动释放，在设备中的对象会随着设备
		//一起被释放
		p0->DeleteObject();
		b0->DeleteObject();
		f0->DeleteObject();

		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

