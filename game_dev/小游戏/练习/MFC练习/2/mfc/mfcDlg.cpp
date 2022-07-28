
// mfcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc.h"
#include "mfcDlg.h"
#include "afxdialogex.h"

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
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
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

	//滚动条
	//修改窗口风格
	ModifyStyle(0, WS_HSCROLL | WS_VSCROLL);

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

	//加载位图
	CClientDC dc(this);
	HBITMAP hbmp;
	hbmp = (HBITMAP)LoadImageA(0, "0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc.CreateCompatibleDC(&dc);
	::DeleteObject(bmpdc.SelectObject(hbmp));
	::DeleteObject(hbmp);

	//读取地图
	FILE* pf = NULL;
	fopen_s(&pf, "Map2.txt", "rb");
	fseek(pf, 0, SEEK_END);
	int filesize = ftell(pf);
	rewind(pf);
	map = (char*)malloc(filesize + 1);
	map[filesize] = 0;
	fread(map, 1, filesize, pf);
	fclose(pf);

	hang = 1, lie = 0;
	for (int i = 0; map[i] != '\r'; ++i)
		++lie;
	for (int i = 0; i < strlen(map); ++i)
	{
		if (map[i] == '\n')
			++hang;
	}
	char* p = (char*)malloc(filesize + 1);
	char* q = p;
	int len = 0;
	for (int i = 0; i < filesize; ++i)
	{
		if (map[i] != '\r' && map[i] != '\n')
			p[len++] = map[i];
	}
	p[len] = 0;
	free(map);
	map = q;

	vx = 0;
	vy = 0;
	//水平
	SetScrollRange(SB_HORZ, 0, lie - 10);
	SetScrollPos(SB_HORZ, vx);

	//垂直
	SetScrollRange(SB_VERT, 0, hang - 10);
	SetScrollPos(SB_VERT, vx);
	SetTimer(0, 33, 0);
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
		//主绘图设备
		CPaintDC dc(this);
	//	dc.TransparentBlt(0, 0, _CLIENT_W, _CLIENT_H, &bmpdc, 64, 0,64,48, RGB(0,255,0));

		for (int i = 0; i < hang; ++i)
		{
			for (int j = 0; j < lie; ++j)
			{
				if (map[(j + vx) + (i + vy) * lie] == '0')
					dc.TransparentBlt(j * 64, i * 48, 64, 48, &bmpdc, 0 * 64, 0, 64, 48, RGB(0, 255, 0));
				if (map[(j + vx) + (i + vy) * lie] == '1')
					dc.TransparentBlt(j * 64, i * 48, 64, 48, &bmpdc, 1 * 64, 0, 64, 48, RGB(0, 255, 0));
				if (map[(j + vx) + (i + vy) * lie] == '2')
					dc.TransparentBlt(j * 64, i * 48, 64, 48, &bmpdc, 2 * 64, 0, 64, 48, RGB(0, 255, 0));
				if (map[(j + vx) + (i + vy) * lie] == '3')
					dc.TransparentBlt(j * 64, i * 48, 64, 48, &bmpdc, 3 * 64, 0, 64, 48, RGB(0, 255, 0));
			}
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

void CmfcDlg::UpdateScroll()
{

}



void CmfcDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	InvalidateRect(0);
	CDialogEx::OnTimer(nIDEvent);
}


void CmfcDlg::OnCancel()
{
	KillTimer(0);
	bmpdc.DeleteDC();
	free(map);

	CDialogEx::OnCancel();
}


BOOL CmfcDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//return true;
	return CDialogEx::OnEraseBkgnd(pDC);
}


void CmfcDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
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

	SetScrollPos(SB_HORZ, pos);
	vx = pos;

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CmfcDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	//得到垂直滚动条的范围和位置
	int min, max, pos;
	GetScrollRange(SB_VERT, &min, &max);
	pos = GetScrollPos(SB_VERT);

	//对垂直滚动条的事件进行分类处理
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

	SetScrollPos(SB_VERT, pos);
	vy = pos;

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
