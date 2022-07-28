// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "GameHall.h"
#include "Login.h"
#include "Register.h"
#include "GameHallDlg.h"
#include "ProtocolMessageDispatcher.h"
#include "DataDefine.h"

// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialog)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CLogin::IDD, pParent)
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IpAddr);
	DDX_Control(pDX, IDC_EDIT1, m_ID);
	DDX_Control(pDX, IDC_EDIT2, m_Password);
	DDX_Control(pDX, IDC_BUTTON1, m_Login);
	DDX_Control(pDX, IDC_BUTTON4, m_RG);
	DDX_Control(pDX, IDC_BUTTON2, m_CL);
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CLogin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CLogin::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CLogin::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CLogin 消息处理程序

void CLogin::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnCancel();
}

void CLogin::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CLogin::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	this->OnCancel();
}

void CLogin::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CRegister rgdlg;
	rgdlg.DoModal();

}

void CLogin::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString id;
	m_ID.GetWindowTextA(id);

	CString pw;
	m_Password.GetWindowTextA(pw);

	if(id.GetLength() < 8 || id.GetLength() > 16)
	{
		MessageBox("账号长度必须大于8并且小于16");
		m_ID.SetWindowTextA("");
		m_Password.SetWindowTextA("");
		return;
	}


	for(int i = 0; i < id.GetLength(); i++)
	{
		if(id[i] < 32 || id[i] > 128)
		{
			MessageBox("账号含有非法字符");
			m_ID.SetWindowTextA("");
			m_Password.SetWindowTextA("");
			return;
		}
	}

	if(pw.GetLength() < 8 || pw.GetLength() > 16)
	{
		MessageBox("密码长度必须大于8并且小于16");
		m_ID.SetWindowTextA("");
		m_Password.SetWindowTextA("");
		return;
	}


	for(int i = 0; i < pw.GetLength(); i++)
	{
		if(pw[i] < 32 || pw[i] > 128)
		{
			MessageBox("密码含有非法字符");
			m_ID.SetWindowTextA("");
			m_Password.SetWindowTextA("");
			return;
		}
	}

	CString ip;
	m_IpAddr.GetWindowTextA(ip);

	

	this->SetTimer(0,20,0);
	if(!g_TcpClient.ConnectIP(ip.GetString(), 12345, 5, 10, 5))
		MessageBox("IP地址格式有误。");
	else
	{
		m_ID.EnableWindow(FALSE);
		m_Password.EnableWindow(FALSE);
		m_IpAddr.EnableWindow(FALSE);
		m_Login.EnableWindow(FALSE);
		m_RG.EnableWindow(FALSE);
		m_CL.EnableWindow(FALSE);
	}
}

void CLogin::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	g_TcpClient.Run();

	_CNET_EVENT ne;
	while (g_TcpClient.GetNetEvent(&ne))
	{
		switch (ne.type)
		{
			case _CNE_CONNECT_OK:
			{
				
				CString id;
				m_ID.GetWindowTextA(id);

				CString pw;
				m_Password.GetWindowTextA(pw);

				g_Player.m_ID = id;

				Login(id.GetString(),pw.GetString(),g_TcpClient);
				break;
			}
		case _CNE_CONNECT_FAIL:
			{
				MessageBox("连接失败！");
				m_ID.EnableWindow(TRUE);
				m_Password.EnableWindow(TRUE);
				m_IpAddr.EnableWindow(TRUE);
				m_Login.EnableWindow(TRUE);
				m_RG.EnableWindow(TRUE);
				m_CL.EnableWindow(TRUE);
				break;
			}
		case _CNE_DATA:
			{
				_PROTOCOL* xy = (_PROTOCOL*)ne.data;
				switch (xy->type)
				{
				case DL_SC_NO_ID:
					{
						MessageBox("没有指定的账号！");
						m_ID.EnableWindow(TRUE);
						m_Password.EnableWindow(TRUE);
						m_IpAddr.EnableWindow(TRUE);
						m_Login.EnableWindow(TRUE);
						m_RG.EnableWindow(TRUE);
						m_CL.EnableWindow(TRUE);
						break;
					}
				case DL_SC_PW_ERROR:
					{
						MessageBox("密码不正确！");
						m_ID.EnableWindow(TRUE);
						m_Password.EnableWindow(TRUE);
						m_IpAddr.EnableWindow(TRUE);
						m_Login.EnableWindow(TRUE);
						m_RG.EnableWindow(TRUE);
						m_CL.EnableWindow(TRUE);
						break;
					}
					//登陆成功
				case DL_SC_DL_OK:
					//新玩家加入
				case DL_SC_NEW_CLIENT:
					{
						g_PMDispatcher.ProtocolRun(ne);
						this->OnOK();
						break;
					}
				case DL_SC_DL_AGAIN:
					{
						MessageBox("该账号已登录！");
						m_ID.EnableWindow(TRUE);
						m_Password.EnableWindow(TRUE);
						m_IpAddr.EnableWindow(TRUE);
						m_Login.EnableWindow(TRUE);
						m_RG.EnableWindow(TRUE);
						m_CL.EnableWindow(TRUE);
						break;
					}
				}
				break;
			}
		case _CNE_DISCONNECTED_C:
		case _CNE_DISCONNECTED_S:
				{
					Beep(500, 500);
					break;
				}
		case _CNE_DISCONNECTED_E:
			{
				KillTimer(0);
				if(MessageBox("服务器失去连接,程序即将关闭。","连接失败",MB_OK) == IDOK)
				{
					this->OnCancel();
				}
				break;
			}
		}

		g_TcpClient.ReleaseNetEvent(&ne);
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CLogin::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_IpAddr.SetWindowTextA("127.0.0.1");
	m_ID.SetWindowTextA("aabbccdd");
	m_Password.SetWindowTextA("aabbccdd");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLogin::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
