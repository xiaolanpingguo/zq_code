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
	DDX_Control(pDX, IDC_EDIT1, id);
	DDX_Control(pDX, IDC_EDIT2, pw);
	DDX_Control(pDX, IDC_LIST1, lb);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_WM_TIMER()
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
	SetTimer(0, 20, 0);
	lb.ShowWindow(SW_HIDE);

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
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CTestDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnCancel();
}

void CTestDlg::OnBnClickedButton1()
{
	id.GetWindowTextA(s1);
	pw.GetWindowTextA(s2);
	if (s1.GetLength() == 0 || s2.GetLength() == 0)
	{
		MessageBox("信息不能为空");
		return;
	}
	act = 0; //表示注册
	tc.ConnectIP("192.168.1.3", 12345, 5, 10, 5);
}

void CTestDlg::OnBnClickedButton2()
{
	id.GetWindowTextA(s1);
	pw.GetWindowTextA(s2);
	if (s1.GetLength() == 0 || s2.GetLength() == 0)
	{
		MessageBox("信息不能为空");
		return;
	}
	act = 1; //表示登陆
	tc.ConnectIP("192.168.1.3", 12345, 5, 10, 5);
}

void CTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	tc.Run();

	_CNET_EVENT ne;
	while (tc.GetNetEvent(&ne))
	{
		switch (ne.type)
		{
			case _CNE_CONNECT_OK:
			{
				if (act == 0)
				{
					CS_ZC cs_zc;
					strcpy_s(cs_zc.id, 32, s1.GetString());
					strcpy_s(cs_zc.pw, 32, s2.GetString());
					tc.SendData(&cs_zc, sizeof(cs_zc));
				}
				else if (act == 1)
				{
					CS_DL cs_dl;
					strcpy_s(cs_dl.id, 32, s1.GetString());
					strcpy_s(cs_dl.pw, 32, s2.GetString());
					tc.SendData(&cs_dl, sizeof(cs_dl));
				}

				break;
			}
		case _CNE_CONNECT_FAIL:
			{
				MessageBox("连接失败！");
				break;
			}
		case _CNE_DATA:
			{
				_XY* xy = (_XY*)ne.data;
				switch (xy->type)
				{
				case 1:
					{
						MessageBox("没有指定的账号！");
						break;
					}
				case 2:
					{
						MessageBox("密码不正确！");
						break;
					}
				case 3:
					{
						lb.ShowWindow(SW_SHOW);
						GetDlgItem(IDC_BUTTON1)->EnableWindow(0);
						GetDlgItem(IDC_BUTTON2)->EnableWindow(0);

						lb.AddString(s1.GetString());

						SC_DL_OK* dl_ok = (SC_DL_OK*)ne.data;
						char* p = (char*)(dl_ok + 1);
						for (int i = 0; i < dl_ok->num; ++i)
						{
							lb.AddString(p);
							p += strlen(p) + 1;
						}

						break;
					}
				case 4:
					{
						SC_NEW_CLIENT* new_client = (SC_NEW_CLIENT*)ne.data;
						lb.AddString(new_client->id);

						break;
					}
				case 6:
					{
						MessageBox("账号已经存在！");
						break;
					}
				case 7:
					{
						MessageBox("注册成功！");
						break;
					}
				}

				break;
			}
		default: //三种断开事件
			{
				Beep(500, 500);
				break;
			}
		}

		tc.ReleaseNetEvent(&ne);
	}

	CDialog::OnTimer(nIDEvent);
}
