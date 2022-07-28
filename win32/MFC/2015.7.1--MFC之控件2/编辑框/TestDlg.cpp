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
	DDX_Control(pDX, IDC_EDIT4, e);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT1, &CTestDlg::OnEnChangeEdit1)
	ON_EN_UPDATE(IDC_EDIT1, &CTestDlg::OnEnUpdateEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTestDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CTestDlg::OnBnClickedButton8)
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


void CTestDlg::OnOK()
{
	//在多行编辑框中，一般允许回车换行，但是默认
	//的回车将引发本函数被调用，为了避免退出程序
	//把下面的代码注释了
	//CDialog::OnOK();
}

void CTestDlg::OnEnChangeEdit1()
{
	
}

void CTestDlg::OnEnUpdateEdit1()
{
	
}

void CTestDlg::OnBnClickedButton1()
{
	CString s;
	GetDlgItemTextA(IDC_EDIT1, s);
	GetDlgItem(IDC_EDIT2)->SetWindowTextA(s.GetString());
}

void CTestDlg::OnBnClickedButton2()
{
	CString s;
	GetDlgItem(IDC_EDIT3)->GetWindowTextA(s);
	MessageBoxA(s.GetString());

	//通过CWnd::ModifyStyle来去除密码风格？
	//((CEdit*)GetDlgItem(IDC_EDIT3))->ModifyStyle(ES_PASSWORD, 0);
}
void CTestDlg::OnBnClickedButton3()
{
	CString s;
	e.GetWindowTextA(s);
	MessageBoxA(s.GetString());
}

void CTestDlg::OnBnClickedButton4()
{
	CString s;
	s.Format("%d行", e.GetLineCount());
	MessageBoxA(s.GetString());
}

void CTestDlg::OnBnClickedButton5()
{
	char buf[32] = {};
	e.GetLine(1, buf, 32);
	MessageBoxA(buf);
}

void CTestDlg::OnBnClickedButton6()
{
	//根据传入的字符在整个字符串中的下标
	//得到该字符在哪一行，如果填写-1就得
	//到当前正在编辑的行
	int line = e.LineFromChar();
	CString s;
	s.Format("当前正在编辑%d行", line);
	MessageBoxA(s.GetString());
}

void CTestDlg::OnBnClickedButton7()
{
	//begin得到选择的首个字符的下标
	//end得到选择的最后字符的下标+1
	int begin, end;
	e.GetSel(begin, end);
	CString s;
	e.GetWindowTextA(s);
	if (begin < end)
	{
		char* p = new char[end - begin + 1];
		memcpy(p, s.GetString() + begin, end - begin);
		p[end - begin] = 0;
		MessageBoxA(p);
		delete [] p;
	}
	else
		MessageBoxA("没有选择！");
}

void CTestDlg::OnBnClickedButton8()
{
	CString s;
	e.GetWindowTextA(s);
	GetDlgItem(IDC_EDIT6)->SetWindowTextA(s.GetString());
}

//05)GetFont
//06)SetFont