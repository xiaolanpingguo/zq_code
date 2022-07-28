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
	DDX_Control(pDX, IDC_LIST1, lc);
	DDX_Control(pDX, IDC_COMBO1, cb);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &CTestDlg::OnCbnDropdownCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CTestDlg::OnLvnColumnclickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CTestDlg::OnNMClickList1)
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
	lc.InsertColumn(0, "账户");
	lc.InsertColumn(1, "密码");
	lc.InsertColumn(2, "昵称");
	for (int i = 0; i < 3; ++i)
		lc.SetColumnWidth(i, 100);

	//设置带表格线的扩展风格
	lc.SetExtendedStyle(LVS_EX_GRIDLINES);

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
	CString s[3];
	for (int i = IDC_EDIT1; i <= IDC_EDIT3; ++i)
	{
		GetDlgItemTextA(i, s[i - IDC_EDIT1]);
		if (s[i - IDC_EDIT1].GetLength() == 0)
		{
			MessageBox("添加内容有空！");
			return;
		}
	}

	//得到当前的总行数
	int ic = lc.GetItemCount();

	//插入第0列到最后位置
	lc.InsertItem(ic, s[0].GetString());

	//插入第1、2列
	lc.SetItemText(ic, 1, s[1].GetString());
	lc.SetItemText(ic, 2, s[2].GetString());
}

void CTestDlg::OnCbnDropdownCombo1()
{
	cb.ResetContent();
	for (int i = 0; i < lc.GetItemCount(); ++i)
	{
		CString s;
		s.Format("%d", i);
		cb.AddString(s.GetString());
	}
}

void CTestDlg::OnBnClickedButton2()
{
	if (-1 != cb.GetCurSel())
		lc.DeleteItem(cb.GetCurSel());
	else
		MessageBox("必须选择要删除的行！");
}

void CTestDlg::OnBnClickedButton3()
{
	lc.DeleteAllItems();
}

void CTestDlg::OnBnClickedButton4()
{
	if (0 == lc.GetSelectedCount())
	{
		MessageBox("当前没有选择！");
		return;
	}

	CString str1, str2;
	str1.Format("总共选择了%d行，分别如下\n", lc.GetSelectedCount());

	//得到初始位置
	POSITION pos = lc.GetFirstSelectedItemPosition();
	while (pos)
	{
		//得到下一个位置并返回当前选择的行的下标
		int i = lc.GetNextSelectedItem(pos);

		CString s1 = lc.GetItemText(i, 0);
		CString s2 = lc.GetItemText(i, 1);
		CString s3 = lc.GetItemText(i, 2);

		str2 += s1 + " - " + s2 + " - " + s3 + "\n";
	}

	MessageBox(str2.GetString(), str1.GetString());
}

void CTestDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//C++和C语言中的转换有所不同，C语言的转换一般来说就是
	//(类型)表达式，这种书写方式在代码中很难被发现，也就是
	//在代码中难以发现此处有类型转换，所以在C++中将类型转换
	//改成了4个关键字来处理，因为是关键字，而往往在各种C++
	//编译器中对关键字的显示都用了特殊的颜色，在程序中很容易
	//辨别出来是有类型转换，C++中的类型转换语法如下：
	//XXX_cast<类型>(表达式)。
	//static_cast：静态转换，完全等同于C语言的转换
	//dynamic_cast：动态转换，主要用于在继承体系下进行转换
	//const_cast：去常量属性转换
	//reinterpret_cast：整数和地址之间的转换

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	const char* str[] = {"账号", "密码", "昵称"};
	CString s;
	s.Format("点中了[%s]列", str[pNMLV->iSubItem]);
	SetWindowTextA(s.GetString());
}

void CTestDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//增加转换
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//pNMLV->ptAction就是当前点击的位置
	LVHITTESTINFO lh;
	lh.pt = pNMLV->ptAction;
	lc.SubItemHitTest(&lh);

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
				CString s;
				s.Format("点中了第%d行第%d列", i, 0);
				SetWindowTextA(s.GetString());
			}
			else
				MessageBox("该行为空");
			return;
		}

		MessageBox("该行为空");
		return;
	}

	//注意第0列必须点中字才算，但是也可以用我们自己
	//方法来判断是否出现这种情况

	CString s;
	s.Format("点中了第%d行第%d列", lh.iItem, lh.iSubItem);
	SetWindowTextA(s.GetString());
}
