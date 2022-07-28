// Game.cpp : 实现文件
//

#include "stdafx.h"
#include "GameHall.h"
#include "Game.h"
#include "GameHallDlg.h"
#include "GameSel.h"
// CGame 对话框

#define _POKER_W 75
#define _POKER_H 111

IMPLEMENT_DYNAMIC(CGame, CDialog)

CGame::CGame(CWnd* pParent /*=NULL*/)
	:
CDialog(CGame::IDD, pParent),
showsel(false)
{

}

CGame::~CGame()
{
}

void CGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lbMessage);
	DDX_Control(pDX, IDC_EDIT1, m_edSendMessage);
}


BEGIN_MESSAGE_MAP(CGame, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CGame::OnBnClickedButton1)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CGame 消息处理程序

void CGame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if(g_Player.m_PlayState == _PS_PLAYING)
	{
		CGameHallDlg* parent = (CGameHallDlg*)this->GetParent();
		dc.SetStretchBltMode(HALFTONE);
		dc.StretchBlt(0,0,500,420,&g_Table,0,0,400,300,SRCCOPY);
		dc.StretchBlt(520,10,48,48,&g_Faces[parent->m_Adversary->m_Face],0,0,48,48,SRCCOPY);
		
		dc.SetBkMode(TRANSPARENT);
		CString s = "对手信息：";
		dc.TextOutA(520,65,s.GetString(),s.GetLength());
		s.Format("昵称：%s",parent->m_Adversary->m_Name.c_str());
		dc.TextOutA(520,85,s.GetString(),s.GetLength());
		s.Format("积分：%d",parent->m_Adversary->m_Score);
		dc.TextOutA(520,105,s.GetString(),s.GetLength());
		s.Format("战绩：胜%d 平%d 负%d",parent->m_Adversary->m_Win,parent->m_Adversary->m_Draw,parent->m_Adversary->m_Lose);
		dc.TextOutA(520,125,s.GetString(),s.GetLength());
		

		s.Format("玩家当前点数：%d",parent->m_iPlayerCurPoint);
		dc.TextOutA(25,380,s.GetString(),s.GetLength());

		int dw1 = parent->m_AdversaryPokersNum > 5 ? _POKER_W / 2 : _POKER_W;

		for(int i = 0; i < parent->m_AdversaryPokersNum; i++)
		{
			if(parent->m_AdversaryPokers[i] == -1)
				dc.Rectangle(50 + dw1 * i,50,50 + dw1 * i + _POKER_W,50 + _POKER_H);
			else
				dc.TransparentBlt(50 + dw1 * i,50,_POKER_W,_POKER_H,&g_Pokers,
				parent->m_Pokers[parent->m_AdversaryPokers[i]].tex.x,
				parent->m_Pokers[parent->m_AdversaryPokers[i]].tex.y,
				_POKER_W,_POKER_H,RGB(0,255,0));
		}

		int dw2 = parent->m_MyPokersNum > 5 ? _POKER_W / 2 : _POKER_W;

		for(int i = 0; i < parent->m_MyPokersNum; i++)
		{
			dc.TransparentBlt(50 + dw2 * i,380 - _POKER_H - 25,_POKER_W,_POKER_H,&g_Pokers,
				parent->m_Pokers[parent->m_MyPokers[i]].tex.x,
				parent->m_Pokers[parent->m_MyPokers[i]].tex.y,
				_POKER_W,_POKER_H,RGB(0,255,0));
		}

	}
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}

void CGame::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CGame::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(g_Player.m_PlayState == _PS_PLAYING)
	{
		if(MessageBox("正在处于游戏中，退出将被判定为逃跑，是否确定要退出？","提示",MB_YESNO) == IDYES)
		{
			CS_RUN_AWAY cs_ra;
			strcpy_s(cs_ra.ID,32,g_Player.m_ID.c_str());
			g_TcpClient.SendData(&cs_ra,sizeof(cs_ra));
		}
	}
	else
		CDialog::OnCancel();
}

int CGame::game_MakeChoice()
{
	showsel = true;
	if(gs.DoModal() == IDOK)
	{
		showsel = false;
		return gs.m_iSel;
	}
	else
		return 0;
}

BOOL CGame::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CGame::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_Player.m_PlayState != _PS_PLAYING)
	{
		MessageBox("本局对决已结束！");
	}
	else
	{
		CString msg;
		m_edSendMessage.GetWindowTextA(msg);

		if(msg.GetLength() >= 64)
		{
			MessageBox("发送消息过长，只能发送64字节以内的文字！");
		}
		else
		{
			CS_TALK_IN_GAME cs_tig;
			strcpy_s(cs_tig.ID,32,g_Player.m_ID.c_str());
			strcpy_s(cs_tig.msg,256,msg.GetString());
			g_TcpClient.SendData(&cs_tig,sizeof(cs_tig));
			m_edSendMessage.SetWindowTextA("");
		}
	}
}

void CGame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	RECT r;
	this->GetWindowRect(&r);
	int w = r.right - r.left;
	int h = r.bottom - r.top;

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	r.left =  (sw - w) / 2;
	r.top = (sh - h) / 2;

	this->MoveWindow(r.left,r.top,w,h);
}
