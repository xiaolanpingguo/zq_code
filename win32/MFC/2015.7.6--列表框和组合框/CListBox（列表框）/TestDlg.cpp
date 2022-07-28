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
	DDX_Control(pDX, IDC_LIST1, lb);
	DDX_Control(pDX, IDC_EDIT1, e1);
	DDX_Control(pDX, IDC_EDIT2, e2);
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
	ON_BN_CLICKED(IDC_BUTTON6, &CTestDlg::OnBnClickedButton6)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTestDlg::OnLbnSelchangeList1)
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


void CTestDlg::OnBnClickedButton1()
{
	CString s;
	e1.GetWindowTextA(s);
	if (s.GetLength() > 0)
		lb.AddString(s.GetString());
	else
		MessageBox("内容不能为空！");
}

void CTestDlg::OnBnClickedButton2()
{
	CString s1, s2;
	e1.GetWindowTextA(s1);
	e2.GetWindowTextA(s2);
	if (s1.GetLength() > 0)
	{
		//得到插入的位置，atoi一旦发现不能把
		//字符串转化为整数那么其返回值就为0

		bool bz = true;
		const char* p = s2.GetString();
		if (p[0] != '+' && p[0] != '-' && (p[0] < '0' || p[0] > '9'))
			bz = false;
		if (bz)
		{
			for (int i = 1; i < s2.GetLength(); ++i)
			{
				if (p[i] < '0' || p[i] > '9')
				{
					bz = false;
					break;
				}
			}
		}

		if (!bz)
		{
			MessageBox("位置非法！");
			return;
		}

		int pos = atoi(s2.GetString());

		//GetDlgItemInt
		//{
		//	GetDlgItem->GetWindowTextA(s);
		//	return atoi(s)
		//}

		//得到当前的字符串表长
		int count = lb.GetCount();

		if (pos >= 0 && pos <= count)
			lb.InsertString(pos, s1.GetString());
		else
			MessageBox("插入位置非法！");
	}
	else
		MessageBox("内容不能为空！");
}

void CTestDlg::OnBnClickedButton3()
{
	CString s;
	e2.GetWindowTextA(s);
	if (s.GetLength() > 0)
	{
		bool bz = true;
		const char* p = s.GetString();
		if (p[0] != '+' && p[0] != '-' && (p[0] < '0' || p[0] > '9'))
			bz = false;
		if (bz)
		{
			for (int i = 1; i < s.GetLength(); ++i)
			{
				if (p[i] < '0' || p[i] > '9')
				{
					bz = false;
					break;
				}
			}
		}
		if (!bz)
		{
			MessageBox("位置非法！");
			return;
		}
		
		int pos = atoi(s.GetString());
		
		//得到当前的字符串表长
		int count = lb.GetCount();

		if (pos >= 0 && pos < count)
			lb.DeleteString(pos);
		else
			MessageBox("删除位置非法！");
	}
	else
		MessageBox("内容不能为空！");
}

void CTestDlg::OnBnClickedButton4()
{
	lb.ResetContent();
}

void CTestDlg::OnBnClickedButton5()
{
	//得到当前选择的位置，如果没有选择就返回-1
	int pos = lb.GetCurSel();
	if (pos != -1)
	{
		CString s;

		//得到指定位置上面的字符串
		lb.GetText(pos, s);

		//得到指定位置上面的字符串长度
		int len = lb.GetTextLen(pos);

		CString s2;
		s2.Format("第%d行中的文字长度为%d，内容为\n%s", pos, len, s.GetString());
		MessageBox(s2.GetString());
	}
	else
		MessageBox("没有选择！");
}

void CTestDlg::OnBnClickedButton6()
{
	CString s;
	e2.GetWindowTextA(s);
	if (s.GetLength() > 0)
	{
		bool bz = true;
		const char* p = s.GetString();
		if (p[0] != '+' && p[0] != '-' && (p[0] < '0' || p[0] > '9'))
			bz = false;
		if (bz)
		{
			for (int i = 1; i < s.GetLength(); ++i)
			{
				if (p[i] < '0' || p[i] > '9')
				{
					bz = false;
					break;
				}
			}
		}
		if (!bz)
		{
			MessageBox("位置非法！");
			return;
		}
		
		int pos = atoi(s.GetString());
		
		//得到当前的字符串表长
		int count = lb.GetCount();

		if (pos >= 0 && pos < count)
			lb.SetCurSel(pos);
		else
			MessageBox("选择位置非法！");
	}
	else
		MessageBox("内容不能为空！");
}

void CTestDlg::OnLbnSelchangeList1()
{
	//LBN_SELCHANGE是一旦选择项发生变化就会触发本消息
	//但是只能是通过鼠标点击发生的改变才可以，用SetCurSel
	//是不行的
	int pos = lb.GetCurSel();
	CString s;
	s.Format("当前选择了%d行", pos);
	SetWindowTextA(s.GetString());
}
