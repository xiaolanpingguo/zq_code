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
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
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

	//滚动条的添加有两种
	//1）窗口风格的滚动条，通过ModifyStyle来添加
	//2）控件滚动条，通过拖动控件到窗口上来添加

	//修改窗口风格
	ModifyStyle(
		0, //要去除的窗口风格
		WS_HSCROLL | WS_VSCROLL); //要添加的窗口风格

	//所谓滚动条，其本质上和我们的窗口显示区域没有任何
	//关系，它只是提供了一个范围（min,max）以及一个在
	//这个范围中变化的当前值pos，这个pos的变化可以通过
	//滚动条消息来确定，只不过我们程序中往往通过这个pos
	//来确定我们绘制时候的x,y位置，就象我们处理视口的
	//方式，比如下面是整个地图（12 X 6）
	//◆■■■■■■■■■■■
	//■■■■■■■■■■■■
	//■■■■■■◆■■■■■
	//■■■■■■■■■■■■
	//■■■■■■■■■■■■
	//■■■■■■■■■■■■
	//但是视口（6 X 4）只能显示
	//■■■■■■
	//■■■■■■
	//■■■■■■
	//■■■■■■
	//那么视口左上角在大地图上面的范围就是(0,0)到(6,2)
	//那么可以设置水平滚动条的min、max是0~6，设置垂直
	//滚动条的区间为0~2，那么我们就可以通过滚动条来改
	//变视口左上角在大地图上面的位置，进一步就可以通过
	//这个左上角位置来确定我们要绘制大地图的哪个部分

	//设置水平滚动条范围和位置
	SetScrollRange(SB_HORZ, 0, 9);
	SetScrollPos(SB_HORZ, 0);

	//设置垂直滚动条范围和位置
	SetScrollRange(SB_VERT, 0, 5);
	SetScrollPos(SB_VERT, 2);

	UpdateScroll();

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


void CTestDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//只要在水平滚动条上进行输入，都会触发本
	//消息，一般来说我们只关心滚动条的6种事件

	//得到水平滚动条的范围和位置
	int min, max, pos;
	GetScrollRange(SB_HORZ, &min, &max);
	pos = GetScrollPos(SB_HORZ);

	//对水平滚动条的事件进行分类处理
	switch (nSBCode)
	{
	case SB_LINELEFT:
		{
			pos -= 1;
			break;
		}
	case SB_LINERIGHT:
		{
			pos += 1;
			break;
		}
	case SB_PAGELEFT:
		{
			pos -= 2;
			break;
		}
	case SB_PAGERIGHT:
		{
			pos += 2;
			break;
		}
		//无论是拖动还是放开，nPos都会传入当前滚动块的位置
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		{
			pos = nPos;
			break;
		}
	}

	//这个检查是滚动条自己会处理的，我们也可以自己完成
	if (pos < min)
		pos = min;
	if (pos > max)
		pos = max;

	SetScrollPos(SB_HORZ, pos);
	UpdateScroll();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTestDlg::UpdateScroll()
{
	int hmin, hmax, hpos;
	GetScrollRange(SB_HORZ, &hmin, &hmax);
	hpos = GetScrollPos(SB_HORZ);

	int vmin, vmax, vpos;
	GetScrollRange(SB_VERT, &vmin, &vmax);
	vpos = GetScrollPos(SB_VERT);

	char buf[64];
	sprintf_s(buf, 64, "水平(%d-%d-%d)，垂直(%d-%d-%d)", hmin, hpos, hmax, vmin, vpos, vmax);
	//SetWindowTextA(buf);
}
void CTestDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int min, max, pos;
	GetScrollRange(SB_VERT, &min, &max);
	pos = GetScrollPos(SB_VERT);

	//对水平滚动条的事件进行分类处理
	switch (nSBCode)
	{
	case SB_LINEUP:
		{
			pos -= 1;
			break;
		}
	case SB_LINEDOWN:
		{
			pos += 1;
			break;
		}
	case SB_PAGEUP:
		{
			pos -= 2;
			break;
		}
	case SB_PAGEDOWN:
		{
			pos += 2;
			break;
		}
		//无论是拖动还是放开，nPos都会传入当前滚动块的位置
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		{
			pos = nPos;
			break;
		}
	}

	//这个检查是滚动条自己会处理的，我们也可以自己完成
	if (pos < min)
		pos = min;
	if (pos > max)
		pos = max;

	SetScrollPos(SB_VERT, pos);
	UpdateScroll();

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
