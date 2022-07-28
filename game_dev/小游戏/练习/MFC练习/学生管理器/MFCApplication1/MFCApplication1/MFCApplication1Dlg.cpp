
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "dlg1.h"

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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, lc);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMFCApplication1Dlg::OnNMClickList1)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
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

	ShowWindow(SW_MINIMIZE);

	// TODO:  在此添加额外的初始化代码
	erase_hang = -1;

	lc.InsertColumn(0, L"学号");
	lc.InsertColumn(1, L"姓名");
	lc.InsertColumn(2, L"性别");
	lc.InsertColumn(3, L"年龄");
	for (int i = 0; i < 4; ++i)
		lc.SetColumnWidth(i, 130);

	//设置带表格线的扩展风格
	lc.SetExtendedStyle(LVS_EX_GRIDLINES);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedButton1()
{
	CFileDialog fd(
		TRUE,
		0,
		0,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"所有文件 | *.*",
		this,
		0);

	int ic;

	if (IDOK == fd.DoModal())
	{
		CString s1 = fd.GetPathName();
		FILE* pf = NULL;
		_wfopen_s(&pf, s1.GetString(), L"rb");
		fseek(pf, 0, SEEK_END);
		int fs = ftell(pf);
		rewind(pf);
		char* buf = new char[fs + 1];
		char* p = buf;
		fread(buf, 1, fs, pf);
		rewind(pf);
		fread(&ic, 1, sizeof(int), pf);
		int k = 0;
		for (int i = 0; i < ic; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				char a[32] = {};
				for (;  a[k] = p[k]; ++k)
					;
				CString s;
				fread(a, 1, strlen(a) + 1, pf);
				s.Format(L"%s", a);
				//lc.SetItemText(i,j,L"1");
				//插入第0列到最后位置
				if (j == 0)
					lc.InsertItem(i, s.GetString());
				else
					lc.SetItemText(i, j, s.GetString());
			}
		}
		fclose(pf);
		delete[] buf;
	}
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	CFileDialog fd(
		FALSE,
		0,
		0,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"所有文件 | *.*",
		this,
		0);

	int ic = lc.GetItemCount();

	if (IDOK == fd.DoModal())
	{
		CString s1 = fd.GetPathName();
		FILE* pf = NULL;
		_wfopen_s(&pf, s1.GetString(), L"wb");
		fwrite(&ic, 1, sizeof(int), pf);
		for (int i = 0; i < ic; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				CString s;
				s = lc.GetItemText(i, j);
				fwrite(s.GetString(), 1, s.GetLength() + 1, pf);
			}
		}
		fclose(pf);
	}
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	dlg1 d;
	d.add = true;
	if (IDOK == d.DoModal())
	{
		/*
		STUDENT stu;
		stu.age = d.stu.age;
		stu.id = d.stu.id;
		stu.name = d.stu.name;
		stu.sex = stu.sex;
		v_stu.push_back(stu);*/
	}
}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	if (erase_hang == -1)
	{
		MessageBox(L"当前没有选择要删除的数据！");
		return;
	}
	if (IDYES == MessageBox(L"是否删除？", L"提示", MB_YESNO))
		lc.DeleteItem(erase_hang);
	erase_hang = -1;
}


void CMFCApplication1Dlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	//pNMLV->ptAction就是当前点击的位置
	LVHITTESTINFO lh;
	lh.pt = pNMItemActivate->ptAction;
	lc.SubItemHitTest(&lh);

	int ic = lc.GetItemCount();
	dlg1 d;
	d.hang = lh.iItem;
	d.lie = lh.iSubItem;
	//注意如果点中有文字的行的第0列的空白部分也会
	//导致iItem为-1，当然我们可以通过自己调用GetItemRect
	//或者GetItemPosition进行判断
	if (lh.iItem == -1)
	{
		//点中了第0列
		if (lh.iSubItem == 0)
		{
			int i;
			for (i = 0; i < lc.GetItemCount(); ++i)
			{
				POINT p, q;
				lc.GetItemPosition(i, &p);
				lc.GetItemPosition(i + 1, &q);
				if (lh.pt.y >= p.y && lh.pt.y < q.y)
					break;
			}
			if (i < lc.GetItemCount())
			{
				d.add = false;
				d.hang = i;
				d.lie = 0;
				if (IDOK == d.DoModal())
				{
				
				}
			}
			return;
		}
		return;
	}
	erase_hang = lh.iItem;
	d.add = false;
	if (IDOK == d.DoModal())
	{
		
	}
}
