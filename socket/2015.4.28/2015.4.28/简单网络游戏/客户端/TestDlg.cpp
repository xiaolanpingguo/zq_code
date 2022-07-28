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
	DDX_Control(pDX, IDC_IPADDRESS1, ip_a_c);
	DDX_Control(pDX, IDC_LIST1, lb);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
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

	//设置初始控件
	SetScene(false);

	//开启游戏循环
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

#define _GRID_W 15
#define _GRID_H 15
#define _RENDER_W (_GRID_W * _GAME_MAP_W)
#define _RENDER_H (_GRID_H * _GAME_MAP_H)

		CBrush red;
		red.CreateSolidBrush(RGB(255, 0, 0));

		dc.SetBkMode(TRANSPARENT);

		dc.Rectangle(0, 0, _RENDER_W, _RENDER_H);

		if (all_player.size() > 0)
		{
			for (std::map<std::string, POINT>::iterator it = all_player.begin(); it != all_player.end(); ++it)
			{
				int x = it->second.x * _GRID_W;
				int y = it->second.y * _GRID_H;

				if (strcmp(it->first.c_str(), m_Nick_Name.c_str()) == 0)
				{
					CBrush* old = dc.SelectObject(&red);
					dc.Ellipse(x, y, x + _GRID_W, y + _GRID_H);
					dc.SelectObject(old);
				}
				else
					dc.Rectangle(x, y, x + _GRID_W, y + _GRID_H);

				dc.TextOutA(x, y, it->first.c_str(), it->first.length());
			}
		}

		red.DeleteObject();

		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestDlg::SetScene(bool p)
{
	CWnd* p1[]
	= 
	{
		GetDlgItem(IDC_BUTTON1),
		GetDlgItem(IDC_IPADDRESS1),
		GetDlgItem(IDC_EDIT1),
		GetDlgItem(IDC_STATIC1),
	};
	CWnd* p2[]
	= 
	{
		GetDlgItem(IDC_LIST1),
		GetDlgItem(IDC_EDIT3),
		GetDlgItem(IDC_BUTTON3),
		GetDlgItem(IDC_BUTTON4),
	};

	for (int i = 0; i < 4; ++i)
		p1[i]->ShowWindow(p ? SW_HIDE : SW_SHOW);

	for (int i = 0; i < 4; ++i)
		p2[i]->ShowWindow(p ? SW_SHOW : SW_HIDE);
}

void CTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	tc.Run();

	_TC_NET_EVENT tne;
	while (tc.GetTCNetEvent(&tne))
	{
		switch (tne.type)
		{
		case _TCNE_CONNECT_FAIL:
			{
				MessageBox("无法连接服务器!");
				break;
			}
		case _TCNE_CONNECT_OK:
			{
				//发送1号协议
				_C_S_GP1 csgp1;
				strcpy_s(csgp1.nick_name, 32, m_Nick_Name.c_str());
				tc.SendData((char*)&csgp1, sizeof(csgp1));
				break;
			}
		case _TCNE_S_DISCONNECT:
		case _TCNE_C_DISCONNECT:
		case _TCNE_E_DISCONNECT:
			{
				SetScene(false);
				all_player.clear();
				break;
			}
		case _TCNE_DATA:
			{
				_GAME_PROTOCOL* pgp = (_GAME_PROTOCOL*)tne.data;
				switch (pgp->id)
				{
				case _NICK_NAME_LAWLESS:
					{
						MessageBox("昵称非法！");
						tc.Disconnect();
						CWnd* p1[]
						= 
						{
							GetDlgItem(IDC_BUTTON1),
							GetDlgItem(IDC_IPADDRESS1),
							GetDlgItem(IDC_EDIT1),
							GetDlgItem(IDC_STATIC1),
						};
						for (int i = 0; i < 4; ++i)
							p1[i]->EnableWindow(TRUE);
						break;
					}
				case _NICK_NAME_LEGALITY:
					{
						_S_C_GP3* p = (_S_C_GP3*)tne.data;

						//初始化游戏地图
						for (int i = 0; i < _GAME_MAP_S; ++i)
							map[i] = p->map[i];

						//得到所有玩家的信息
						for (int i = 0; i < p->player_num; ++i)
						{
							std::string str = p->player[i].nick_name;
							POINT pos = {p->player[i].x, p->player[i].y};
							all_player.insert(std::pair<std::string, POINT>(str, pos));
						}

						SetScene(true);

						SetFocus();

						break;
					}
				case _NEW_PLAYER_ENTER:
					{
						_S_C_GP4* p = (_S_C_GP4*)tne.data;
						std::string str = p->new_player.nick_name;
						POINT pos = {p->new_player.x, p->new_player.y};
						all_player.insert(std::pair<std::string, POINT>(str, pos));
						std::string enter_msg = str + "进入游戏！";
						lb.AddString(enter_msg.c_str());

						break;
					}
				case _PLAYER_TALK:
					{
						_S_C_GP6* p = (_S_C_GP6*)tne.data;
						lb.AddString(p->talk);
						break;
					}
				case _PLAYER_WALK:
					{
						_S_C_GP8* p = (_S_C_GP8*)tne.data;
						std::string str = p->player.nick_name;
						std::map<std::string, POINT>::iterator it = all_player.find(str);
						if (it != all_player.end())
						{
							it->second.x = p->player.x;
							it->second.y = p->player.y;
						}

						break;
					}
				case _PLAYER_QUIT:
					{
						_S_C_GP9* p = (_S_C_GP9*)tne.data;
						std::string str = p->nick_name;
						std::map<std::string, POINT>::iterator it = all_player.find(str);
						if (it != all_player.end())
							all_player.erase(it);
						std::string quit_msg = str + "退出游戏！";
						lb.AddString(quit_msg.c_str());

						break;
					}
				}
				break;
			}
		}

		tc.ReleaseTSNetEvent(&tne);
	}

	InvalidateRect(0);

	CDialog::OnTimer(nIDEvent);
}

void CTestDlg::OnBnClickedButton1()
{
	//得到ip地址和昵称
	in_addr ip;
	ip_a_c.GetAddress(ip.S_un.S_addr);
	ip.S_un.S_addr = htonl(ip.S_un.S_addr);
	m_IP = inet_ntoa(ip);
	CString s;
	GetDlgItemTextA(IDC_EDIT1, s);
	m_Nick_Name = s.GetString();

	if (m_IP.length() == 0 || m_Nick_Name.length() == 0)
	{
		MessageBox("必须填写ip地址和昵称!");
		return;
	}

	//连接服务器
	tc.ConnectByIP(
		m_IP.c_str(),
		12345,
		10,
		10,
		5);

	CWnd* p1[]
	= 
	{
		GetDlgItem(IDC_BUTTON1),
		GetDlgItem(IDC_IPADDRESS1),
		GetDlgItem(IDC_EDIT1),
		GetDlgItem(IDC_STATIC1),
	};
	for (int i = 0; i < 4; ++i)
		p1[i]->EnableWindow(FALSE);
}

void CTestDlg::OnBnClickedButton3()
{
	CString s;
	GetDlgItemTextA(IDC_EDIT3, s);
	if (s.GetLength() > 0)
	{
		_C_S_GP5 csgp5;
		strcpy_s(csgp5.talk, 256, s.GetString());
		tc.SendData((const char*)&csgp5, sizeof(csgp5));
	}
	else
		MessageBox("必须填写要发送的内容！");
}

void CTestDlg::OnBnClickedButton4()
{
	tc.Disconnect();
}

BOOL CTestDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN && all_player.size() > 0)
	{
		std::map<std::string, POINT>::iterator it;
		it = all_player.find(m_Nick_Name.c_str());
		bool ok = true;
		int cx = it->second.x;
		int cy = it->second.y;
		switch (pMsg->wParam)
		{
		case VK_UP:
			{
				if (cy > 0)
					cy -= 1;
				break;
			}
		case VK_DOWN:
			{
				if (cy < _GAME_MAP_H - 1)
					cy += 1;
				break;
			}
		case VK_LEFT:
			{
				if (cx > 0)
					cx -= 1;
				break;
			}
		case VK_RIGHT:
			{
				if (cx < _GAME_MAP_W - 1)
					cx += 1;
				break;
			}
		default:
			ok = false;
		}

		if (ok)
		{
			_C_S_GP7 csgp7;
			csgp7.x = cx;
			csgp7.y = cy;
			tc.SendData((const char*)&csgp7, sizeof(csgp7));
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
