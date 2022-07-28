// 1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1.h"
#include "1Dlg.h"
#include"Xueji.h"

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


// CMy1Dlg 对话框




CMy1Dlg::CMy1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, listcont);
}

BEGIN_MESSAGE_MAP(CMy1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, &CMy1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy1Dlg::OnBnClickedButton4)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMy1Dlg::OnNMClickList1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CMy1Dlg::OnLvnColumnclickList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMy1Dlg 消息处理程序

BOOL CMy1Dlg::OnInitDialog()
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
	listcont.InsertColumn(0,"学号");
	listcont.InsertColumn(1,"姓名");
	listcont.InsertColumn(2,"性别");
	listcont.InsertColumn(3,"年龄");
	for (int i = 0; i < 4; ++i)
	{
		listcont.SetColumnWidth(i, 130);
		isIncrease[i] = true;
	}

	cur_select_hang = -1;
	cur_select_lie = -1;
	isTranslate = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy1Dlg::OnPaint()
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
HCURSOR CMy1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy1Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	Xueji fd;
	if (IDOK == fd.DoModal())
	{
		
	}
}

void CMy1Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (0 == listcont.GetSelectedCount())
	{
		MessageBox("没有选中删除的学员，删除失败");
	}
	if (IDOK == MessageBox("是否删除学员","提示",MB_OKCANCEL))
	{
		int len = listcont.GetSelectedCount();
		int* p = new int[len];
		POSITION pos = listcont.GetFirstSelectedItemPosition();
		int index = 0;
		while (pos)
		{
			p[index++] = listcont.GetNextSelectedItem(pos);
		}
		for (int i = len - 1; i >= 0; --i)
		{
			listcont.DeleteItem(p[i]);
		}
		delete []p;
	}

}

void CMy1Dlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//pNMLV->ptAction就是当前点击的位置
	LVHITTESTINFO lh;
	lh.pt = pNMLV->ptAction;
	listcont.SubItemHitTest(&lh);

	//注意如果点中有文字的行的第0列的空白部分也会
	//导致iItem为-1，当然我们可以通过自己调用GetItemRect
	//或者GetItemPosition进行判断
	if (lh.iItem == -1)
	{
		//点中了第0列
		if (lh.iSubItem == 0)
		{
			int i;
			for (i = 0; i < listcont.GetItemCount(); ++i)
			{
				POINT p, q;
				listcont.GetItemPosition(i, &p);
				listcont.GetItemPosition(i + 1, &q);
				if (lh.pt.y >= p.y && lh.pt.y < q.y)
					break;
			}
			if (i < listcont.GetItemCount())
			{
				Xueji dlg;
				cur_select_hang = i;
				cur_select_lie = lh.iSubItem;
				isTranslate = true;
				if (IDOK == dlg.DoModal())
				{


				}
			}
			return;
		}
		return;
	}

	//注意第0列必须点中字才算，但是也可以用我们自己
	//方法来判断是否出现这种情况
	Xueji dlg;
	cur_select_hang = lh.iItem;
	cur_select_lie = lh.iSubItem;
	isTranslate = true;
	if (IDOK == dlg.DoModal())
	{
		
		
	}
}

void CMy1Dlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int pos = pNMLV->iSubItem;
	int len = listcont.GetItemCount();
	if (isIncrease[pos])
	{
		for (int i = len - 1; i > 0; --i)
		{
			for (int j = 0; j < i; ++j)
			{
				CString s[3];
				s[0] = listcont.GetItemText(j, pos);
				s[1] = listcont.GetItemText(j + 1, pos);
				if (strcmp(
					s[0].GetString(),
					s[1].GetString()) == 1)
				{
					for (int k = 0; k < 4; ++k)
					{
						s[2] = listcont.GetItemText(j, k);
						listcont.SetItemText(j, k, listcont.GetItemText(j + 1, k).GetString());
						listcont.SetItemText(j + 1, k, s[2].GetString());
					}
				}
			}
		}
		isIncrease[pos] = false;
	}
	else
	{
		for (int i = len - 1; i > 0; --i)
		{
			for (int j = 0; j < i; ++j)
			{
				CString s[3];
				s[0] = listcont.GetItemText(j, pos);
				s[1] = listcont.GetItemText(j + 1, pos);
				if (strcmp(
					s[0].GetString(),
					s[1].GetString()) == -1)
				{
					for (int k = 0; k < 4; ++k)
					{
						s[2] = listcont.GetItemText(j, k);
						listcont.SetItemText(j, k, listcont.GetItemText(j + 1, k).GetString());
						listcont.SetItemText(j + 1, k, s[2].GetString());
					}
				}
			}
		}
		isIncrease[pos] = true;
	}
}

void CMy1Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fd(false,
		"map",
		"new",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		0,
		this,
		0);
	
	if (IDOK == fd.DoModal())
	{
		CString s = fd.GetPathName();
		CString s1;
		for (int i = 0; i < s.GetLength(); ++i)
		{
			if (*(s.GetString() + i) == '\\')
				s1 += "\\\\";
			else
				s1 += *(s.GetString() + i);
		}
		FILE* pf = 0;
		fopen_s(&pf,s1.GetString(),"wb");
		int len = listcont.GetItemCount();
		fwrite(&len,1,4,pf);
		CString s2;
		for (int i = 0; i < len; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				s2 = listcont.GetItemText(i,j);
				fwrite(s2.GetString(),s2.GetLength() + 1,1,pf);
			}
		}
		fclose(pf);
		MessageBox("保存成功!");
	}
	
	
}

void CMy1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fd(true,
		0,
		0,
		OFN_HIDEREADONLY ,
		"*.map||",
		this,
		0);
	if (IDOK == fd.DoModal())
	{
		CString s = fd.GetPathName();
		CString s1;
		for (int i = 0; i < s.GetLength(); ++i)
		{
			if (*(s.GetString() + i) == '\\')
				s1 += "\\\\";
			else
				s1 += *(s.GetString() + i);
		}
		FILE* pf = 0;
		fopen_s(&pf,s1.GetString(),"rb");
		fseek(pf,0,SEEK_END);
		int fs = ftell(pf);
		rewind(pf);
		int len;
		fread(&len, 1, 4,pf);
		CString s2;
		int index = 0;
		char temp;
		//清空
		len = listcont.GetItemCount();
		if (len > 0)
		{
			for (int i = 0; i < len; ++i)
				listcont.DeleteItem(0);
		}
		for (int i = 4; i < fs; ++i)
		{
			fread(&temp,1,1,pf);
			if (temp == 0)
			{
				int x = index % 4;
				int y = index / 4;
				if (x == 0)
					listcont.InsertItem(y,s2.GetString());
				else
					listcont.SetItemText(y,x,s2.GetString());
				++index;
				s2 = "";
				continue;
			}
			s2 += temp;
		}
		fclose(pf);
		MessageBox("打开成功!");
	}
}
