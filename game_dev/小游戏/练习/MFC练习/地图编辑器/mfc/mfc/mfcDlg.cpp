
// mfcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc.h"
#include "mfcDlg.h"
#include "afxdialogex.h"
#include "msdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmfcDlg 对话框



CmfcDlg::CmfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CmfcDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CmfcDlg::OnBnClickedButton3)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CmfcDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CmfcDlg 消息处理程序

BOOL CmfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	d.Create(
		MAKEINTRESOURCE(IDD_DIALOG3), //对话框资源ID
		this); //父窗口)

	//初始化地图
	_MAP_H = 15;
	_MAP_W = 15;
	map = new char[_MAP_W * _MAP_H];
	for (int i = 0; i < _MAP_W * _MAP_H; ++i)
		map[i] = d.c;

	//设置滚动条
	((CScrollBar*)GetDlgItem(IDC_SCROLLBAR1))->MoveWindow(0, _GRID_H * _VIEW_H, _GRID_W * _VIEW_W, ::GetSystemMetrics(SM_CYHSCROLL));
	((CScrollBar*)GetDlgItem(IDC_SCROLLBAR2))->MoveWindow(_GRID_W * _VIEW_W, 0, ::GetSystemMetrics(SM_CXVSCROLL), _GRID_H * _VIEW_H);
	((CScrollBar*)GetDlgItem(IDC_SCROLLBAR1))->SetScrollRange(0, _MAP_W - _VIEW_W);
	((CScrollBar*)GetDlgItem(IDC_SCROLLBAR1))->SetScrollPos(0);
	((CScrollBar*)GetDlgItem(IDC_SCROLLBAR2))->SetScrollRange(0, _MAP_H - _VIEW_H);
	((CScrollBar*)GetDlgItem(IDC_SCROLLBAR2))->SetScrollPos(0);

	//加载位图
	CClientDC dc(this);
	HBITMAP hbmp;
	hbmp = (HBITMAP)LoadImageA(0, "0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc.CreateCompatibleDC(&dc);
	::DeleteObject(bmpdc.SelectObject(hbmp));
	::DeleteObject(hbmp);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmfcDlg::OnPaint()
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
		int vx = ((CScrollBar*)GetDlgItem(IDC_SCROLLBAR1))->GetScrollPos();
		int vy = ((CScrollBar*)GetDlgItem(IDC_SCROLLBAR2))->GetScrollPos();

		for (int i = 0; i < _VIEW_W * _VIEW_H; ++i)
		{
			int x = i % _VIEW_W;
			int y = i / _VIEW_W;
			int dx = x * _GRID_W;
			int dy = y * _GRID_H;
			char c = map[(x + vx) + (y + vy) * _MAP_W];
			if (c == 0)
				dc.BitBlt(dx, dy, _GRID_W, _GRID_H, &bmpdc, 0, 0, SRCCOPY);
			else if (c == 1)
				dc.BitBlt(dx, dy, _GRID_W, _GRID_H, &bmpdc, 60, 0, SRCCOPY);
			else if (c == 2)
				dc.BitBlt(dx, dy, _GRID_W, _GRID_H, &bmpdc, 120, 0, SRCCOPY);
		}
	
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfcDlg::OnBnClickedButton2()
{
	msdlg d;
	if (IDOK == d.DoModal())
	{
	}
}


void CmfcDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	d.c = 0;
	d.ShowWindow(SW_SHOW);
}


void CmfcDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = pScrollBar->GetScrollPos();
	switch (nSBCode)
	{
	case SB_LINELEFT:
	case SB_PAGELEFT:
	{
			pos -= 1;
			break;
	}
	case SB_LINERIGHT:
	case SB_PAGERIGHT:
	{
			 pos += 1;
			 break;
	}
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
	{
			 pos = nPos;
			 break;
	}
	}

	pScrollBar->SetScrollPos(pos);
	InvalidateRect(0);


	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CmfcDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = pScrollBar->GetScrollPos();
	switch (nSBCode)
	{
	case SB_LINEUP:
	case SB_PAGEUP:
	{
			pos -= 1;
			break;
	}
	case SB_LINEDOWN:
	case SB_PAGEDOWN:
	{
			pos += 1;
			break;
	}
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
	{
			pos = nPos;
			break;
	}
	}

	pScrollBar->SetScrollPos(pos);
	InvalidateRect(0);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CmfcDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (point.x >= 0 && point.x < _VIEW_W * _GRID_W &&
		point.y >= 0 && point.y < _VIEW_H * _GRID_H
		&& d.c != -1)
	{
		int vx = ((CScrollBar*)GetDlgItem(IDC_SCROLLBAR1))->GetScrollPos();
		int vy = ((CScrollBar*)GetDlgItem(IDC_SCROLLBAR2))->GetScrollPos();
		int cx = point.x / _GRID_W;
		int cy = point.y / _GRID_H;
		map[(cx + vx) + (cy + vy) * _MAP_W] = d.c;
		InvalidateRect(0);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CmfcDlg::OnCancel()
{
	delete[] map;
	bmpdc.DeleteDC();
	d.bmpdc.DeleteDC();
	CDialogEx::OnCancel();
}


void CmfcDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	FILE* pf = NULL;
	fopen_s(&pf, "map.txt", "wb");
	fwrite(&_MAP_W, 1, sizeof(int), pf);
	fwrite(&_MAP_H, 1, sizeof(int), pf);
	for (int i = 0; i < _MAP_W * _MAP_H; ++i)
		fwrite(&(map[i]), 1, sizeof(char), pf);
	fclose(pf);
	MessageBox(L"保存成功！",L"提示", MB_OK);
}
