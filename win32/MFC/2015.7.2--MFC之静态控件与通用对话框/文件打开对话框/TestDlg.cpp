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
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestDlg::OnBnClickedButton6)
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
	_getcwd(work_dir, 256);

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

		//设置工作目录为之前存储的最初的工作目录
		_chdir(work_dir);

		//如果使用绝对路径则没有问题
		//C:\\Documents and Settings\\Administrator\\桌面\\2015.7.2\\文件打开对话框\\01.bmp
		//使用相对路径则要从当前工作目录中查找
		HBITMAP hbmp = (HBITMAP)LoadImageA(0, "01.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		CDC bmpdc;
		bmpdc.CreateCompatibleDC(&dc);
		DeleteObject(bmpdc.SelectObject(hbmp));
		DeleteObject(hbmp);

		dc.BitBlt(300, 100, 200, 200, &bmpdc, 0, 0, SRCCOPY);

		bmpdc.DeleteDC();

		char buf[256];
		SetWindowTextA(_getcwd(buf, 256));

		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//对话框分为两种
//1）模式对话框，这种对话框不关闭的话，它
//   的父窗口是无法响应我们的输入的，MFC
//   中的模式对话框基本上都是用DoModal函数
//   来进行显示的，适合于在非做不可的情况
//   下使用
//2）非模式对话框，这种对话框关闭与否都不影
//   响它的父窗口响应我们的输入，非模式对话
//   框一般我们都用ShowWindow来显示或隐藏它
//通用对话框中，文件打开关闭、颜色、字体等
//对话框都是模式对话框，但是文本查找替换对话
//框都是非模式对话框

void CTestDlg::OnBnClickedButton1()
{
	//构造的形式参数填写TRUE表示文件打开对话框
	//构造的形式参数填写FALSE表示文件另存对话框
	CFileDialog fd(TRUE);

	//如果是按[打开]关闭对话框的，那么DoMal函数
	//的返回值就是IDOK，如果是按[取消]关闭对话框
	//的话那么返回值是IDCANCEL
	if (IDOK == fd.DoModal())
	{
		//GetPathName可以得到我们选择的
		//文件的完整路径名
		m_SrcFileName = fd.GetPathName();

		SetWindowTextA(m_SrcFileName.GetString());

		//在得到了文件的路径名后，我们一般
		//就可以通过fopen、fclose等那套文件
		//操作函数来处理文件了
	}
}

void CTestDlg::OnBnClickedButton2()
{
	if (m_SrcFileName.GetLength() > 0)
	{
		CFileDialog fd(FALSE);
		if (IDOK == fd.DoModal())
		{
			CString DestFile = fd.GetPathName();
			
			FILE* pf = 0;
			fopen_s(&pf, m_SrcFileName.GetString(), "rb");
			fseek(pf, 0, SEEK_END);
			int fs = ftell(pf);
			rewind(pf);
			char* fd = new char[fs];
			fread(fd, 1, fs, pf);
			fclose(pf); //断开了程序中的这个指针和硬盘上面的那个文件的联系

			fopen_s(&pf, DestFile.GetString(), "wb");
			fwrite(fd, 1, fs, pf);
			fclose(pf);

			MessageBox("备份成功！");
		}
	}
	else
		MessageBox("必须先选择要备份的文件！");
}

void CTestDlg::OnBnClickedButton3()
{
	//OFN_HIDEREADONLY：隐藏只读复选框
	//OFN_OVERWRITEPROMPT：如果要覆盖则会进行提示（文件另存中使用）
	//OFN_ALLOWMULTISELECT：允许多选
	//OFN_FILEMUSTEXIST：文件必须存在
	//OFN_FORCESHOWHIDDEN：强制显示隐藏文件夹

	CFileDialog fd(
		FALSE, //TRUE为打开、FALSE关闭
		0, //默认的文件扩展名
		0, //默认的文件名
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, //风格
		0, //文件类型过滤字符串
		this, //父窗口
		0); //未使用

	if (IDOK == fd.DoModal())
	{
		CString s = fd.GetPathName();
		SetWindowTextA(s.GetString());
	}

	//Windows中很多函数会有暂时没有使用的参数，这个
	//其实是很高明的设计，以后这个函数要扩展功能，那
	//么这些参数可能就有用了，严格来说一个函数可以只
	//需要一个void指针作为形式参数即可
	//int f1(int a, int b, int c)
	//{
	//	return a + b + c;
	//}
	//struct _参数
	//{
	//	int a, b, c;
	//};
	//int f2(void* p)
	//{
	//	_参数* q = (_参数*)p;
	//	return q->a + q->b + q->c;
	//}
}

void CTestDlg::OnBnClickedButton4()
{
	CFileDialog fd(
		FALSE, //TRUE为打开、FALSE关闭
		0, //默认的文件扩展名
		0, //默认的文件名
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, //风格
		"位图文件|*.bmp|JPEG文件|*.jpg|所有文件|*.*||", //"描述1|*.XXX|描述2|*.XXX||"
		this, //父窗口
		0); //未使用

	if (IDOK == fd.DoModal())
	{
		CString s = fd.GetPathName();
		SetWindowTextA(s.GetString());
	}
}

void CTestDlg::OnBnClickedButton5()
{
	CFileDialog fd(
		TRUE, //TRUE为打开、FALSE关闭
		0, //默认的文件扩展名
		0, //默认的文件名
		OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		0,
		this, //父窗口
		0); //未使用

	//文件打开对话框中如果要使用多文件，要注意它内部
	//存储所有文件的字符数组如果大小不够的话（即不足
	//以存储我们选择的所有文件名称，它本身的字符数组
	//大小是MAX_PATH，即260），我们只能自己来对它的存
	//储空间进行扩充
	char buf[1024 * 64] = {};
	fd.GetOFN().lpstrFile = buf;
	fd.GetOFN().nMaxFile = 1024 * 64;

	if (fd.DoModal() == IDOK)
	{
		std::vector<std::string> v;

		//得到起始的位置
		POSITION p = fd.GetStartPosition();
		while (p)
		{
			//根据位置得到文件名，并设置下一个位置，当
			//下一个位置为0则表示当前没有文件了
			CString s = fd.GetNextPathName(p);
	
			//放入表中
			v.push_back(std::string(s.GetString()));
		}

		std::string s;
		for (int i = 0; i < v.size(); ++i)
		{
			s += v[i];
			s += "\r\n";
		}
		MessageBoxA(s.c_str());
	}
}

//文件打开对话框会修改当前程序的工作路径的，一般来说
//当前程序的工作路径就是其exe文件所在的目录，我们可以
//通过下面的函数进行读取、设置
//char* _getcwd(char *buffer, int maxlen);
//int _chdir(const char *dirname);


void CTestDlg::OnBnClickedButton6()
{
	//用于存储目录路径的字符数组
	char d[MAX_PATH];

	BROWSEINFO bi = {};
	bi.hwndOwner = m_hWnd;   
	bi.pszDisplayName = d;
	bi.lpszTitle = "目录打开对话框的标题！！";   
	bi.ulFlags = BIF_RETURNONLYFSDIRS;     

	//目录打开对话框
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl)   
	{   
		//得到目录路径
		SHGetPathFromIDList(pidl, d);

		MessageBox(d);
	}
}
