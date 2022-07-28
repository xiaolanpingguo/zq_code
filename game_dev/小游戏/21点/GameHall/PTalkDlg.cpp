// PTalkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GameHall.h"
#include "PTalkDlg.h"
#include "GameHallDlg.h"


// CPTalkDlg 对话框

IMPLEMENT_DYNAMIC(CPTalkDlg, CDialog)

CPTalkDlg::CPTalkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPTalkDlg::IDD, pParent)
{

}

CPTalkDlg::~CPTalkDlg()
{
}

void CPTalkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lbMessage);
	DDX_Control(pDX, IDC_EDIT1, m_lbSendMessage);
}


BEGIN_MESSAGE_MAP(CPTalkDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON2, &CPTalkDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CPTalkDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPTalkDlg 消息处理程序

void CPTalkDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CGameHallDlg* p = (CGameHallDlg*)(this->GetParent());

	CString state = player->m_Name.c_str();

	CString n = state;

	if(player->m_PlayState == _PS_NONE)
	{
		n += "正在闲逛中。。。";
	}
	else if(player->m_PlayState == _PS_WAIT || player->m_PlayState == _PS_READY)
	{
		n.Format("%s正在%d号房间等待挑战。",state.GetString(),player->m_RoomNum);
	}
	else if(player->m_PlayState == _PS_PLAYING)
	{
		n.Format("%s正在%d号房间激战正酣。",state.GetString(),player->m_RoomNum);
	}

	dc.SetBkMode(TRANSPARENT);
	dc.StretchBlt(30,15,48,48,&g_Faces[player->m_Face],0,0,48,48,SRCCOPY);
	dc.TextOutA(100,30,n.GetString(),(int)n.GetLength());
	// 不为绘图消息调用 CDialog::OnPaint()
}

BOOL CPTalkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	parent = (CGameHallDlg*)this->GetParent();
	this->SetTimer(0,20,0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPTalkDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	this->OnCancel();
}

void CPTalkDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s;
	m_lbSendMessage.GetWindowTextA(s);
	if(s.GetLength() > 255)
		MessageBox("消息发送过长，必须小于256个字节");
	else if(!s.IsEmpty())
	{
		CS_PRI_TALK cs_pt;
		strcpy_s(cs_pt.ID,32,g_Player.m_ID.c_str());
		strcpy_s(cs_pt.DESID,32,player->m_ID.c_str());
		strcpy_s(cs_pt.Message,256,s.GetString());
		g_TcpClient.SendData(&cs_pt,sizeof(cs_pt));
		m_lbSendMessage.SetWindowTextA("");
	}
}

void CPTalkDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(::GetAsyncKeyState(VK_RETURN) & 0x1 && this->GetActiveWindow() == this)
	{
		OnBnClickedButton1();
	}
	CDialog::OnTimer(nIDEvent);
}

void CPTalkDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CPTalkDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnCancel();
}
