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
	DDX_Control(pDX, IDC_EDIT1, e1);
	DDX_Control(pDX, IDC_COMBO1, cb1);
	DDX_Control(pDX, IDC_COMBO2, cb2);
	DDX_Control(pDX, IDC_COMBO3, cb3);
	DDX_Control(pDX, IDC_COMBO4, cb4);
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
	ON_CBN_DROPDOWN(IDC_COMBO4, &CTestDlg::OnCbnDropdownCombo4)
	ON_BN_CLICKED(IDC_BUTTON7, &CTestDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CTestDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CTestDlg::OnBnClickedButton9)
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

	cb1.AddString(s.GetString());
	cb2.AddString(s.GetString());
	cb3.AddString(s.GetString());
}

void CTestDlg::OnBnClickedButton2()
{
	int pos = cb1.GetCurSel();
	if (pos != -1)
	{
		CString s;
		e1.GetWindowTextA(s);
		cb1.InsertString(pos, s.GetString());
		cb2.InsertString(pos, s.GetString());
		cb3.InsertString(pos, s.GetString());
	}
	else
		MessageBox("当前没有选择插入位置！");
}

void CTestDlg::OnBnClickedButton3()
{
	int pos = cb1.GetCurSel();
	if (pos != -1)
	{
		cb1.DeleteString(pos);
		cb2.DeleteString(pos);
		cb3.DeleteString(pos);
	}
	else
		MessageBox("当前没有选择删除位置！");
}

void CTestDlg::OnBnClickedButton4()
{
	cb1.ResetContent();
	cb2.ResetContent();
	cb3.ResetContent();
}

void CTestDlg::OnBnClickedButton5()
{
	CString s;
	s.Format("当前有%d个字符串！", cb1.GetCount());
	MessageBox(s.GetString());
}

void CTestDlg::OnBnClickedButton6()
{
	int pos = cb1.GetCurSel();
	if (pos != -1)
	{
		CString s;
		cb1.GetLBText(pos, s);
		int len = cb1.GetLBTextLen(pos);
		CString s2;
		s2.Format("第%d行的文字长度为%d，内容为\n%s", pos, len, s.GetString());
		MessageBox(s2.GetString());
	}
	else
		MessageBox("当前没有选择位置！");
}

void CTestDlg::OnCbnDropdownCombo4()
{
	cb4.ResetContent();
	CString s;
	for (int i = 0; i < cb1.GetCount(); ++i)
	{
		s.Format("%d", i);
		cb4.AddString(s.GetString());
	}
}

void CTestDlg::OnBnClickedButton7()
{
	if (cb4.GetCurSel() != -1)
	{
		cb1.SetCurSel(cb4.GetCurSel());
		cb2.SetCurSel(cb4.GetCurSel());
		cb3.SetCurSel(cb4.GetCurSel());
	}
}

void CTestDlg::OnBnClickedButton8()
{
	CString s, s1, s2, s3;
	cb1.GetWindowTextA(s1);
	cb2.GetWindowTextA(s2);
	cb3.GetWindowTextA(s3);
	s = s1 + s2 + s3;
	MessageBox(s.GetString());
}

void CTestDlg::OnBnClickedButton9()
{
	const char* s = "！！！";
	cb1.SetWindowTextA(s);
	cb2.SetWindowTextA(s);
	cb3.SetWindowTextA(s);
}
