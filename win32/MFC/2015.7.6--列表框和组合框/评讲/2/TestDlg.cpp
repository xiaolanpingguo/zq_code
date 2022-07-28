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
	map = 0;
	LoadBmp(&bmpdc[0], "bmp\\0.bmp");
	LoadBmp(&bmpdc[1], "bmp\\1.bmp");
	x = 0;
	y = 0;

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
		if (map)
		{
			CPaintDC dc(this);

			//根据英雄位置得到视口左上角相对于大地图的坐标
			int vx, vy;
			if (x < _VIEW_W / 2)
				vx = 0;
			else if (x >= w - _VIEW_W / 2)
				vx = w - _VIEW_W;
			else
				vx = x - _VIEW_W / 2;
			if (y < _VIEW_H / 2)
				vy = 0;
			else if (y >= h - _VIEW_H / 2)
				vy = h - _VIEW_H;
			else
				vy = y - _VIEW_H / 2;

			//绘制视口中的地图
			for (int i = 0; i < _VIEW_W * _VIEW_H; ++i)
			{
				int cx = i % _VIEW_W;
				int cy = i / _VIEW_W;
				int dx = cx * _GRID_W;
				int dy = cy * _GRID_H;
				dc.BitBlt(
					dx, dy, _GRID_W, _GRID_H,
					&bmpdc[0],
					map[(cx + vx) + (cy + vy) * w] * _GRID_W,
					0,
					SRCCOPY);
			}

			//绘制英雄
			dc.BitBlt(
				(x - vx) * _GRID_W,
				(y - vy) * _GRID_H,
				_GRID_W,
				_GRID_H,
				&bmpdc[1],
				0,0,
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


void CTestDlg::OnBnClickedButton1()
{
	CFileDialog fd(TRUE);
	if (IDOK == fd.DoModal())
	{
		CString s = fd.GetPathName();
		FILE* pf = 0;
		fopen_s(&pf, s.GetString(), "rb");
		if (!pf)
		{
			MessageBox("无法打开指定文件！");
			return;
		}
		fread(&w, 1, 4, pf);
		fread(&h, 1, 4, pf);
		map = new char[w * h];
		fread(map, 1, w * h, pf);
		fclose(pf);

		//初始化窗口大小
		int sw = ::GetSystemMetrics(SM_CXSCREEN);
		int sh = ::GetSystemMetrics(SM_CYSCREEN);
		RECT r
			=
		{
			(sw - _CLIENT_W) / 2,
			(sh - _CLIENT_H) / 2,
			r.left + _CLIENT_W,
			r.top + _CLIENT_H
		};
		CalcWindowRect(&r);
		MoveWindow(&r);

		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);

		InvalidateRect(0);
	}
}

void CTestDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CTestDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	if (map)
		delete [] map;

	bmpdc[0].DeleteDC();
	bmpdc[1].DeleteDC();

	CDialog::OnCancel();
}

BOOL CTestDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_UP:
			{
				if (y > 0 && map[x + (y - 1) * w] == 0)
					y -= 1;
				break;
			}
		case VK_DOWN:
			{
				if (y < h - 1 && map[x + (y + 1) * w] == 0)
					y += 1;
				break;
			}
		case VK_LEFT:
			{
				if (x > 0 && map[(x - 1) + y * w] == 0)
					x -= 1;
				break;
			}
		case VK_RIGHT:
			{
				if (x < w - 1 && map[(x + 1) + y * w] == 0)
					x += 1;
				break;
			}
		}
		InvalidateRect(0);
	}

	return CDialog::PreTranslateMessage(pMsg);
}
