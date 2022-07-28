// 2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "2.h"
#include "2Dlg.h"
#include <time.h>
#include <list>
using namespace std;

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


// CMy2Dlg 对话框




CMy2Dlg::CMy2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMy2Dlg 消息处理程序

BOOL CMy2Dlg::OnInitDialog()
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

	//固定客户区大小的对话框窗口
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

	srand((unsigned int)time(0));
	SetTimer(0,33,0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy2Dlg::OnPaint()
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
		for(list<OBJ>::iterator i = l_obj.begin(); i != l_obj.end();)
		{
			CBrush* b0;
			if (i->flag == 0)
			{
				CBrush b;
				b.CreateSolidBrush(i->color);
				b0 = dc.SelectObject(&b);
				dc.Rectangle(i->p.x - 20,i->p.y - 20,i->p.x + 20,i->p.y + 20);
			}
			else
			{
				CBrush b;
				b.CreateSolidBrush(i->color);
				b0 = dc.SelectObject(&b);
				dc.Ellipse(i->p.x - 20,i->p.y - 20,i->p.x + 20,i->p.y + 20);
			}
			if (i->p.y <=0 || i->p.y >= _CLIENT_H
				|| i->p.x <=0 || i->p.x >= _CLIENT_W)
				i = l_obj.erase(i);
			else
				++i;
			
				b0->DeleteObject();
		}
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	OBJ obj;
	obj.p = point;
	obj.dir = rand() % 4;
	obj.flag = rand() % 2;
	obj.color = RGB(rand() % 255,rand() % 255,rand() % 255);
	l_obj.push_back(obj);
	CDialog::OnLButtonDown(nFlags, point);
}

void CMy2Dlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CMy2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	CPaintDC dc(this);
	for(list<OBJ>::iterator i = l_obj.begin(); i != l_obj.end();++i)
	{
		switch (i->dir)
		{
		case 0:i->p.y -= 5;break;
		case 1:i->p.y += 5;break;
		case 2:i->p.x -= 5;break;
		case 3:i->p.x += 5;break;
		}
	}
	InvalidateRect(0);

	CDialog::OnTimer(nIDEvent);
}

BOOL CMy2Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//return true;
	return CDialog::OnEraseBkgnd(pDC);
}
