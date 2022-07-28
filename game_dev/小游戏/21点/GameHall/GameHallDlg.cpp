// GameHallDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GameHall.h"
#include "GameHallDlg.h"
#include "Login.h"
#include "DataChange.h"
#include "PTalkDlg.h"
#include "ProtocolMessageDispatcher.h"
#include "GameSel.h"

#define _ROOM_W 134
#define _ROOM_H 92
#define _FACE_L_W 64
#define _FACE_L_H 64
#define _FACE_S_W 32
#define _FACE_S_H 32
#define _LBORDER 30
#define _TBORDER 20
#define _POKER_W 75
#define _POKER_H 111


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//class CPTalkDlg;

SOCKET g_Socket;//套接字
_PLAYER g_Player;//当前客户端的用户
CTcpClient g_TcpClient;//Tcp控制器
std::map<std::string,_PLAYER> g_OnlinePlayers;//在线玩家表
std::map<std::string,CPTalkDlg*> g_PTalkDlgs;//私聊对话框
bool g_bInit;//是否初始化完成

CDC g_Table;//游戏桌纹理
CDC g_Title;//游戏标题纹理
CDC g_Room;//游戏房间纹理
CDC g_Pokers;//扑克纹理
CDC g_Faces[_FACE_NUM];//玩家头像纹理
RECT g_Site[_SITE_NUM];//座位矩形
_ROOM g_Rooms[_ROOM_NUM];//房间数据
CPMDispatcher g_PMDispatcher;//协议消息派发器

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


// CGameHallDlg 对话框




CGameHallDlg::CGameHallDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGameHallDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	g_bInit = false;
}

void CGameHallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lbOnlinePlayers);
	DDX_Control(pDX, IDC_LIST2, m_lbMessage);
	DDX_Control(pDX, IDC_EDIT1, m_edSendMessage);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_sbRoomV);
	DDX_Control(pDX, IDC_NAME, m_stName);
	DDX_Control(pDX, IDC_SCORE, m_stScore);
	DDX_Control(pDX, IDC_HISTORY, m_stHistory);
	DDX_Control(pDX, IDC_BUTTON2, m_btRead);
}

BEGIN_MESSAGE_MAP(CGameHallDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_VSCROLL()
	//	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON3, &CGameHallDlg::OnBnClickedButton3)
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CGameHallDlg::OnBnClickedButton1)
	ON_LBN_DBLCLK(IDC_LIST1, &CGameHallDlg::OnLbnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGameHallDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CGameHallDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CGameHallDlg 消息处理程序

BOOL CGameHallDlg::OnInitDialog()
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
	
	InitPMDispatcher();
	gh_GameHallInit();

	m_GameDlg.Create(MAKEINTRESOURCE(IDD_DIALOG5),this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGameHallDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGameHallDlg::OnPaint()
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
		dc.SetStretchBltMode(STRETCH_HALFTONE);
		dc.SetBkMode(TRANSPARENT);
		int pos = m_sbRoomV.GetScrollPos();

		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				int cx = _LBORDER + j * _ROOM_W;
				int cy = _TBORDER + _ROOM_H * i;
				dc.BitBlt(cx, cy, _ROOM_W, _ROOM_H, &g_Room,0,0,SRCCOPY);
				for(int k = 0; k < 2; ++k)
				{
					if(g_Rooms[j + (i + pos) * _R_VIEW_W].player[k])
					{
						dc.StretchBlt(cx + 5 + k * 90,cy + 30,_FACE_S_W,_FACE_S_H,&g_Faces[g_Rooms[j + (i + pos) * _R_VIEW_W].player[k]->m_Face],0,0,48,48,SRCCOPY);
						CString s = "";
						switch(g_Rooms[j + (i + pos) * _R_VIEW_W].player[k]->m_PlayState)
						{
						case _PS_WAIT:s = "等待中";break;
						case _PS_READY:s = "准备中";break;
						case _PS_PLAYING:s = "游戏中";break;
						}
						dc.TextOutA(cx + k * 90,cy + 15,s.GetString(),s.GetLength());
					}
				}
			}
		}

		if(g_bInit)
		{
			dc.StretchBlt(640,30,_FACE_L_W,_FACE_L_H,&g_Faces[g_Player.m_Face],0,0,48,48,SRCCOPY);
		}

		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CGameHallDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGameHallDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CGameHallDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	gh_GameHallEnd();
	CDialog::OnCancel();
}

void CGameHallDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int pos = pScrollBar->GetScrollPos();
	switch(nSBCode)
	{
	case SB_LINEUP:
		{
			pos -= 1;
			break;
		}
	case SB_LINEDOWN:
		{
			pos += 1;
			break;
		}
	case SB_PAGEUP:
		{
			pos -= 2;
			break;
		}
	case SB_PAGEDOWN:
		{
			pos += 2;
			break;
		}
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		{
			pos = nPos;
			break;
		}
	}
	pScrollBar->SetScrollPos(pos);
	this->InvalidateRect(0);

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CGameHallDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s;
	m_edSendMessage.GetWindowTextA(s);
	if(s.GetLength() > 255)
		MessageBox("消息发送过长，必须小于256个字节");
	else if(!s.IsEmpty())
	{
		CS_PUB_TALK cs_pt;
		strcpy_s(cs_pt.ID,32,g_Player.m_ID.c_str());
		strcpy_s(cs_pt.Message,256,s.GetString());
		g_TcpClient.SendData(&cs_pt,sizeof(cs_pt));
		m_edSendMessage.SetWindowTextA("");
	}

}

void CGameHallDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(g_Player.m_PlayState == _PS_NONE || g_Player.m_PlayState == _PS_WAIT)
	{
		int pos = m_sbRoomV.GetScrollPos();

		for(int i = 0; i < _SITE_NUM; ++i)
		{
			int sitenum = i  + pos * _R_VIEW_W * 2;
			if(PtInRect(&g_Site[i],point))
			{
				int roomnum = sitenum / 2;
				if(g_Rooms[roomnum].m_RoomState == _RS_WAIT)
				{
					if(g_Rooms[roomnum].player[sitenum % 2] == 0)
					{
						CS_ENTER_ROOM cs_er;
						strcpy_s(cs_er.ID,32,g_Player.m_ID.c_str());
						cs_er.RoomNumNew = roomnum;
						cs_er.SiteNumNew = sitenum % 2;

						g_TcpClient.SendData(&cs_er,sizeof(cs_er));
					}
					else
						MessageBox("当前座位已有玩家。");
				}
				else
					MessageBox("当房间正在游戏中，无法进入。");
				this->InvalidateRect(0);
			}
		}
	}
	else
		MessageBox("处于游戏中或准备状态不能变更座位。");

	CDialog::OnLButtonUp(nFlags, point);
}

void CGameHallDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	gh_GameHallRun();
	CDialog::OnTimer(nIDEvent);
}

void CGameHallDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_Player.m_PlayState != _PS_PLAYING)
	{
		CDataChange dcdlg;
		if(dcdlg.DoModal() == IDOK)
		{
			CS_CHANGE_DATA cs_cd;
			strcpy_s(cs_cd.ID,32,g_Player.m_ID.c_str());
			cs_cd.facenum = dcdlg.m_FaceNum;
			strcpy_s(cs_cd.Name,32,dcdlg.m_Name.GetString());
			g_TcpClient.SendData(&cs_cd,sizeof(cs_cd));
		}
	}
	else
		MessageBox("处于游戏中或准备状态不能修改资料。");
}

void CGameHallDlg::OnLbnDblclkList1()
{
	// TODO: 在此添加控件通知处理程序代码
	int pos = m_lbOnlinePlayers.GetCurSel();
	CString s;
	m_lbOnlinePlayers.GetText(pos,s);

	std::map<std::string,_PLAYER>::iterator n;
	
	for(n = g_OnlinePlayers.begin(); n != g_OnlinePlayers.end(); ++n)
	{
		if(strcmp(n->second.m_Name.c_str(),s.GetString()) == 0)
		{
			std::map<std::string,CPTalkDlg*>::iterator it = g_PTalkDlgs.find(n->second.m_ID);

			if(it == g_PTalkDlgs.end())
			{
				CPTalkDlg* p = new CPTalkDlg;
				p->Create(MAKEINTRESOURCE(IDD_DIALOG3),this);
				g_PTalkDlgs.insert(std::pair<std::string,CPTalkDlg*>(n->second.m_ID,p));
				p->player = &n->second;
				p->ShowWindow(SW_SHOW);
				CString s;
				s.Format("与%s聊天中",p->player->m_Name.c_str());
				p->SetWindowTextA(s.GetString());
			}
			else
			{
				it->second->ShowWindow(SW_SHOW);
			}
			break;
		}
	}
}
//初始化派发器协议
void CGameHallDlg::InitPMDispatcher()
{
	//登陆相关---------------------------------------------------------
	//登录成功:DL_SC_DL_OK
	CPI_LoginSuccess* ls = new CPI_LoginSuccess(this);
	g_PMDispatcher.AddProtocol(DL_SC_DL_OK,ls);

	//新玩家登录:DL_SC_NEW_CLIENT
	CPI_NewClientLogin* ncl = new CPI_NewClientLogin(this);
	g_PMDispatcher.AddProtocol(DL_SC_NEW_CLIENT,ncl);

	//大厅相关---------------------------------------------------------
	//修改资料成功:HALL_SC_CHANGE_DATA
	CPI_DataChangeSuccess* dcs = new CPI_DataChangeSuccess(this);
	g_PMDispatcher.AddProtocol(HALL_SC_CHANGE_DATA,dcs);

	//修改资料失败:HALL_SC_CHANGE_DATA_FAIL
	CPI_DataChangeFailed*  dcf = new CPI_DataChangeFailed(this);
	g_PMDispatcher.AddProtocol(HALL_SC_CHANGE_DATA_FAIL,dcf);

	//大厅公共聊天:HALL_SC_PUB_TALK
	CPI_PublicTalk*  pubt = new CPI_PublicTalk(this);
	g_PMDispatcher.AddProtocol(HALL_SC_PUB_TALK,pubt);

	//私聊:HALL_SC_PRI_TALK
	CPI_PrivateTalk*  prit = new CPI_PrivateTalk(this);
	g_PMDispatcher.AddProtocol(HALL_SC_PRI_TALK,prit);

	//玩家离线:HALL_SC_PLAYER_OFFLINE
	CPI_PlayerOffLine*  pof= new CPI_PlayerOffLine(this);
	g_PMDispatcher.AddProtocol(HALL_SC_PLAYER_OFFLINE,pof);

	//玩家进入房间成功:HALL_SC_ENTER_ROOM_SUCCESS
	CPI_EnterRoomSuccess*  ers = new CPI_EnterRoomSuccess(this);
	g_PMDispatcher.AddProtocol(HALL_SC_ENTER_ROOM_SUCCESS,ers);

	//玩家进入房间失败:HALL_SC_ENTER_ROOM_FAIL
	CPI_EnterRoomFail*  erf = new CPI_EnterRoomFail(this);
	g_PMDispatcher.AddProtocol(HALL_SC_ENTER_ROOM_FAIL,erf);

	//玩家准备成功:HALL_SC_READ_SUCCESS
	CPI_ReadSuccess*  rs = new CPI_ReadSuccess(this);
	g_PMDispatcher.AddProtocol(HALL_SC_READ_SUCCESS,rs);

	//玩家退出房间成功:HALL_SC_EXIT_ROOM_SUCCESS
	CPI_ExitRoomSuccess*  pers = new CPI_ExitRoomSuccess(this);
	g_PMDispatcher.AddProtocol(HALL_SC_EXIT_ROOM_SUCCESS,pers);

	//玩家取消准备成功:HALL_SC_READY_CANCEL_SUCCESS
	CPI_ReadyCancelSuccess*  rcs = new CPI_ReadyCancelSuccess(this);
	g_PMDispatcher.AddProtocol(HALL_SC_READY_CANCEL_SUCCESS,rcs);

	//游戏相关---------------------------------------------------------
	//开始新游戏:GAME_SC_NEW_GAME
	CPI_NewGame*  ng = new CPI_NewGame(this);
	g_PMDispatcher.AddProtocol(GAME_SC_NEW_GAME,ng);

	//更新玩家数据:GAME_SC_UPDATE_PLAYER_DATA
	CPI_UpdatePlayerData* upd = new CPI_UpdatePlayerData(this);
	g_PMDispatcher.AddProtocol(GAME_SC_UPDATE_PLAYER_DATA,upd);

	//指定玩家做出选择:GAME_SC_MAKE_CHOICE
	CPI_MakeChoice* mc = new CPI_MakeChoice(this);
	g_PMDispatcher.AddProtocol(GAME_SC_MAKE_CHOICE,mc);

	//玩家进行聊天:GAME_SC_TALK_IN_GAME
	CPI_TalkInGame* tig = new CPI_TalkInGame(this);
	g_PMDispatcher.AddProtocol(GAME_SC_TALK_IN_GAME,tig);
	
	//玩家获取到新的牌:GAME_SC_GET_NEW
	CPI_GetNew* gn = new CPI_GetNew(this);
	g_PMDispatcher.AddProtocol(GAME_SC_GET_NEW,gn);

	//玩家获得21点胜利:GAME_SC_WIN_21
	CPI_Win_21* w21 = new CPI_Win_21(this);
	g_PMDispatcher.AddProtocol(GAME_SC_WIN_21,w21);

    //玩家因爆点失败:GAME_SC_LOSE_OUT_RANGE
	CPI_LoseOutRange* lor = new CPI_LoseOutRange(this);
	g_PMDispatcher.AddProtocol(GAME_SC_LOSE_OUT_RANGE,lor);

	//玩家因放弃本局失败:GAME_SC_LOSE_GIVEUP
	CPI_LoseGiveUp* lgu = new CPI_LoseGiveUp(this);
	g_PMDispatcher.AddProtocol(GAME_SC_LOSE_GIVEUP,lgu);

	//玩家因逃跑本局失败:GAME_SC_LOSE_RUN_AWAY 
	CPI_LoseRunAway* lra = new CPI_LoseRunAway(this);
	g_PMDispatcher.AddProtocol(GAME_SC_LOSE_RUN_AWAY,lra);

	//玩家最终比点数获胜:GAME_SC_WIN_BIGGER
	CPI_WinBigger* wb = new CPI_WinBigger(this);
	g_PMDispatcher.AddProtocol(GAME_SC_WIN_BIGGER,wb);

	//玩家最终比点数平局:GAME_SC_DRAW
	CPI_Draw* d = new CPI_Draw(this);
	g_PMDispatcher.AddProtocol(GAME_SC_DRAW,d);

	//游戏结束消息:GAME_SC_GAME_END
	CPI_GameEnd* ge = new CPI_GameEnd(this);
	g_PMDispatcher.AddProtocol(GAME_SC_GAME_END,ge);
}

//初始化游戏大厅
void CGameHallDlg::gh_GameHallInit()
{
	CLogin dlglg;

	if(dlglg.DoModal() == IDOK)
	{
		this->SetTimer(0,20,0);

		CClientDC dc(this);
		HBITMAP hbmp = (HBITMAP)LoadImage(0,"pic\\界面\\牌桌.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		g_Table.CreateCompatibleDC(&dc);
		DeleteObject(g_Table.SelectObject(hbmp));
		DeleteObject(hbmp);

		hbmp = (HBITMAP)LoadImage(0,"pic\\界面\\标题.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		g_Title.CreateCompatibleDC(&dc);
		DeleteObject(g_Title.SelectObject(hbmp));
		DeleteObject(hbmp);

		hbmp = (HBITMAP)LoadImage(0,"pic\\界面\\房间.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		g_Room.CreateCompatibleDC(&dc);
		DeleteObject(g_Room.SelectObject(hbmp));
		DeleteObject(hbmp);

		hbmp = (HBITMAP)LoadImage(0,"pic\\界面\\扑克牌.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		g_Pokers.CreateCompatibleDC(&dc);
		DeleteObject(g_Pokers.SelectObject(hbmp));
		DeleteObject(hbmp);

		for(int i = 0; i < _FACE_NUM; i++)
		{
			CString path;
			path.Format("pic\\头像\\头像 (%d).bmp",i);
			hbmp = (HBITMAP)LoadImage(0,path.GetString(),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			g_Faces[i].CreateCompatibleDC(&dc);
			DeleteObject(g_Faces[i].SelectObject(hbmp));
			DeleteObject(hbmp);
		}

		for(int i = 0; i < _ROOM_NUM; i++)
		{
			g_Rooms[i].player[0] = g_Rooms[i].player[1] = 0;
			g_Rooms[i].m_RoomState = _RS_WAIT;
		}

		m_sbRoomV.SetScrollRange(0,_ROOM_NUM / _R_VIEW_W - _R_VIEW_H);
		m_sbRoomV.SetScrollPos(0);
		m_sbRoomV.MoveWindow(_ROOM_W * 4 + _LBORDER,_TBORDER,15,_ROOM_H * 2,FALSE);

		for(int i = 0; i < _SITE_NUM / 2; ++i)
		{
			int rx = i % _R_VIEW_W;
			int ry = i / _R_VIEW_W;
			int cx = _LBORDER + rx * _ROOM_W;
			int cy = _TBORDER + _ROOM_H * ry;
			g_Site[i * 2].left = cx + 5;
			g_Site[i * 2].top = cy + 30;
			g_Site[i * 2].right = g_Site[i * 2].left + _FACE_S_W;
			g_Site[i * 2].bottom = g_Site[i * 2].top + _FACE_S_H;

			g_Site[i * 2 + 1].left = cx + 96;
			g_Site[i * 2 + 1].top = cy + 30;
			g_Site[i * 2 + 1].right = g_Site[i * 2 + 1].left + _FACE_S_W;
			g_Site[i * 2 + 1].bottom = g_Site[i * 2 + 1].top + _FACE_S_H;
		}

		std::map<std::string,_PLAYER>::iterator it;
		for(it = g_OnlinePlayers.begin(); it != g_OnlinePlayers.end(); ++it)
		{
			if(it->second.m_RoomNum != -1)
				g_Rooms[it->second.m_RoomNum].player[it->second.m_SiteNum] = &it->second;
		}

		for(int i = 0; i < _POKERS_MAX; i++)
		{
			m_Pokers[i].num = i % 13 + 1;
			if(m_Pokers[i].num > 10)
				m_Pokers[i].num = 10;
			m_Pokers[i].tex.x = i % 13 * _POKER_W;
			m_Pokers[i].tex.y = i / 13 * _POKER_H;
		}
	}
	else
	{
		g_TcpClient.Disconnect();
		this->OnCancel();
	}
}
//大厅运行
void CGameHallDlg::gh_GameHallRun()
{
	g_TcpClient.Run();

	_CNET_EVENT ne;
	while (g_TcpClient.GetNetEvent(&ne))
	{
		switch (ne.type)
		{
		case _CNE_DATA:
			{
				g_PMDispatcher.ProtocolRun(ne);
				break;
			}
		default: //三种断开事件
			{
				Beep(500, 500);
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
}

//大厅结束
void CGameHallDlg::gh_GameHallEnd()
{
	g_Table.DeleteDC();
	g_Title.DeleteDC();
	g_Room.DeleteDC();
	g_Pokers.DeleteDC();
	for(int i = 0; i < _FACE_NUM; ++i)
		g_Faces[i].DeleteDC();

	for(std::map<std::string,CPTalkDlg*>::iterator it = g_PTalkDlgs.begin(); it != g_PTalkDlgs.end(); ++it)
	{
		delete (it->second);
	}
	if(m_GameDlg.showsel)
		m_GameDlg.gs.EndDlg();

	m_GameDlg.ShowWindow(SW_HIDE);
}

//登陆成功
void CGameHallDlg::gh_LoginSuccess(_CNET_EVENT& ne)
{
	LoginSuccess(ne,g_OnlinePlayers);
	std::map<std::string,_PLAYER>::iterator it;
	for(it = g_OnlinePlayers.begin(); it != g_OnlinePlayers.end(); ++it)
	{
		int count = m_lbOnlinePlayers.GetCount();
		m_lbOnlinePlayers.InsertString(count,it->second.m_Name.c_str());
	}
	InvalidateRect(0);
	MessageBox("登陆成功!");
	this->OnOK();
}

//新玩家登入
void CGameHallDlg::gh_NewClientLogin(_CNET_EVENT& ne)
{
	_PLAYER newplayer;

	bool isclient = NewClientLogin(ne,newplayer,g_Player.m_ID);

	if(isclient)
	{
		g_Player = newplayer;
		CString s;
		s.Format("昵称：%s",g_Player.m_Name.c_str());
		m_stName.SetWindowTextA(s.GetString());
		s.Format("积分：%d",g_Player.m_Score);
		m_stScore.SetWindowTextA(s.GetString());
		s.Format("战绩：胜%d 平%d 负%d",g_Player.m_Win,g_Player.m_Draw,g_Player.m_Lose);
		m_stHistory.SetWindowTextA(s.GetString());

		g_bInit = true;
		InvalidateRect(0);
	}
	else
	{
		g_OnlinePlayers.insert(std::pair<std::string,_PLAYER>(newplayer.m_ID,newplayer));
		int count = m_lbOnlinePlayers.GetCount();
		m_lbOnlinePlayers.InsertString(count,newplayer.m_Name.c_str());
		InvalidateRect(0);
	}
}

//修改玩家资料成功
void CGameHallDlg::gh_ChangeDataSuccess(_CNET_EVENT& ne)
{
	std::string newname;
	int newface;
	std::string id;

	ChangeDataSuccess(ne,newname,newface,id);

	if(id == g_Player.m_ID)
	{
		g_Player.m_Name = newname;
		g_Player.m_Face = newface;
		CString s;
		s.Format("昵称：%s",g_Player.m_Name.c_str());
		m_stName.SetWindowTextA(s.GetString());
		MessageBox("资料修改成功！");
		this->InvalidateRect(0);
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id.c_str());
		if(it != g_OnlinePlayers.end())
		{
			int cur = m_lbOnlinePlayers.FindString(0,it->second.m_Name.c_str());
			if(cur != LB_ERR)
			{
				m_lbOnlinePlayers.DeleteString(cur);
				m_lbOnlinePlayers.InsertString(cur,newname.c_str());
			}

			it->second.m_Name = newname;
			it->second.m_Face = newface;
			this->InvalidateRect(0);
		}
	}
}

//修改玩家资料失败
void CGameHallDlg::gh_ChangeDataFailed(_CNET_EVENT& ne)
{
	MessageBox("修改失败，名字不能重复!");
}

//公共聊天
void CGameHallDlg::gh_PublicTalk(_CNET_EVENT& ne)
{
	std::string id,message;

	PublicTalk(ne,id,message);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		CString ms;
		ms.Format("%s说：%s",g_Player.m_Name.c_str(),message.c_str());
		int count  = m_lbMessage.GetCount();
		m_lbMessage.InsertString(count,ms.GetString());
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id.c_str());
		if(it != g_OnlinePlayers.end())
		{
			CString ms;
			ms.Format("%s说：%s",it->second.m_Name.c_str(),message.c_str());
			int count  = m_lbMessage.GetCount();
			m_lbMessage.InsertString(count,ms.GetString());
		}
	}
}

//私人聊天
void CGameHallDlg::gh_PrivateTalk(_CNET_EVENT& ne)
{
	std::string id,desid,message;

	PrivateTalk(ne,id,desid,message);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		std::map<std::string,CPTalkDlg*>::iterator it = g_PTalkDlgs.find(desid.c_str());
		if(it != g_PTalkDlgs.end())
		{
			CString ms;
			ms.Format("%s说：%s",g_Player.m_Name.c_str(),message.c_str());
			it->second->m_lbMessage.AddString(ms.GetString());
		}
	}
	else
	{
		std::map<std::string,CPTalkDlg*>::iterator it = g_PTalkDlgs.find(id.c_str());

		if(it != g_PTalkDlgs.end())
		{
			CString ms;
			ms.Format("%s说：%s",it->second->player->m_Name.c_str(),message.c_str());
			it->second->m_lbMessage.AddString(ms.GetString());
			it->second->ShowWindow(TRUE);
		}
		else
		{
			std::map<std::string,_PLAYER>::iterator n = g_OnlinePlayers.find(id.c_str());
			if(n != g_OnlinePlayers.end())
			{
				CPTalkDlg* p = new CPTalkDlg;
				p->Create(MAKEINTRESOURCE(IDD_DIALOG3),this);
				g_PTalkDlgs.insert(std::pair<std::string,CPTalkDlg*>(n->second.m_ID,p));
				p->player = &n->second;
				p->ShowWindow(SW_SHOW);
				p->SetWindowTextA(p->player->m_Name.c_str());
				CString ms;
				ms.Format("%s说：%s",n->second.m_Name.c_str(),message.c_str());
				p->m_lbMessage.AddString(ms.GetString());
			}
		}
	}
}

//玩家离线
void CGameHallDlg::gh_PlayerOffLine(_CNET_EVENT& ne)
{
	std::string id;
	PlayerOffLine(ne,id);

	std::map<std::string,CPTalkDlg*>::iterator it = g_PTalkDlgs.find(id.c_str());

	if(it != g_PTalkDlgs.end())
	{
		it->second->ShowWindow(FALSE);
		delete it->second;
		g_PTalkDlgs.erase(it);
	}

	std::map<std::string,_PLAYER>::iterator n = g_OnlinePlayers.find(id.c_str());
	if(n != g_OnlinePlayers.end())
	{
		if(&n->second == m_Adversary && n->second.m_PlayState == _PS_PLAYING)
		{
			g_Player.m_PlayState = _PS_WAIT;

			if(m_GameDlg.showsel)
				m_GameDlg.gs.EndDlg();

			m_GameDlg.ShowWindow(SW_HIDE);

			MessageBox("对手逃跑了~恭喜你获得胜利！");
			m_btRead.SetWindowTextA("准备");
		}
		if(n->second.m_RoomNum != -1)
			g_Rooms[n->second.m_RoomNum].player[n->second.m_SiteNum] = 0;
		int cur = m_lbOnlinePlayers.FindString(-1,n->second.m_Name.c_str());
		if(cur != -1)
			m_lbOnlinePlayers.DeleteString(cur);
	}

	this->InvalidateRect(0);
}

//进入房间成功
void CGameHallDlg::gh_EnterRoomSuccess(_CNET_EVENT& ne)
{
	std::string id;
	int roomnew,sitenew;
	EnterRoomSuccess(ne,id,roomnew,sitenew);


	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		if(g_Player.m_RoomNum != -1)
		{
			g_Rooms[g_Player.m_RoomNum].player[g_Player.m_SiteNum] = 0;
		}
		g_Rooms[roomnew].player[sitenew] = &g_Player;
		g_Player.m_RoomNum = roomnew;
		g_Player.m_SiteNum = sitenew;
		g_Player.m_PlayState = _PS_WAIT;
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			if(it->second.m_RoomNum != -1)
			{
				g_Rooms[it->second.m_RoomNum].player[it->second.m_SiteNum] = 0;
			}
			g_Rooms[roomnew].player[sitenew] = &it->second;
			it->second.m_RoomNum = roomnew;
			it->second.m_SiteNum = sitenew;
			it->second.m_PlayState = _PS_WAIT;
		}
	}
	this->InvalidateRect(0);
}
//进入房间失败
void CGameHallDlg::gh_EnterRoomFail(_CNET_EVENT& ne)
{
	MessageBox("进入房间失败。");
}

//准备成功
void CGameHallDlg::gh_ReadSuccess(_CNET_EVENT& ne)
{
	std::string id;
	ReadSuccess(ne,id);
	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		g_Player.m_PlayState = _PS_READY;
		m_btRead.SetWindowTextA("取消准备");
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			it->second.m_PlayState = _PS_READY;
		}
	}
	this->InvalidateRect(0);
}

//退出房间成功
void CGameHallDlg::gh_ExitRoomSuccess(_CNET_EVENT& ne)
{
	std::string id;
	ExitRoomSuccess(ne,id);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		g_Player.m_PlayState = _PS_NONE;
		g_Rooms[g_Player.m_RoomNum].player[g_Player.m_SiteNum] = 0;
		g_Player.m_RoomNum = -1;
		g_Player.m_SiteNum = -1;
		m_btRead.SetWindowTextA("准备");
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			it->second.m_PlayState = _PS_NONE;
			g_Rooms[it->second.m_RoomNum].player[it->second.m_SiteNum] = 0;
			it->second.m_RoomNum = -1;
			it->second.m_SiteNum = -1;
		}
	}
	this->InvalidateRect(0);
}

//取消准备成功
void CGameHallDlg::gh_ReadyCancelSuccess(_CNET_EVENT& ne)
{
	std::string id;
	ReadyCancelSuccess(ne,id);
	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		g_Player.m_PlayState = _PS_WAIT;
		m_btRead.SetWindowTextA("准备");
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			it->second.m_PlayState = _PS_WAIT;
		}
	}
	this->InvalidateRect(0);
}

//开始新游戏
void CGameHallDlg::gh_NewGame(_CNET_EVENT& ne)
{
	std::string id;
	int num = -1;
	NewGame(ne,id,num);
	std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);

	if(it != g_OnlinePlayers.end())
	{
		//如果num为-1表示本局游戏与我无关，只是为了更新其他玩家状态
		if(num != -1)
		{
			it->second.m_PlayState = _PS_PLAYING;
			g_Player.m_PlayState = _PS_PLAYING;

			m_MyPokers[0] = num;
			m_iPlayerCurPoint = m_Pokers[num].num;
			m_MyPokersNum = 1;

			m_Adversary = &it->second;
			m_AdversaryPokers[0] = -1;
			m_AdversaryPokersNum = 1;

			m_GameDlg.m_lbMessage.ResetContent();
			m_GameDlg.m_edSendMessage.SetWindowTextA("");

			m_GameDlg.m_lbMessage.AddString("[系统]游戏正式开始！");

			m_GameDlg.ShowWindow(SW_SHOW);

			m_GameDlg.InvalidateRect(0);
		}
		else
		{
			it->second.m_PlayState = _PS_PLAYING;
		}
	}
}
//更新玩家战绩
void CGameHallDlg::gh_UpdatePlayerData(_CNET_EVENT& ne)
{
	std::string id;
	int score,win,lose,draw,playerstate,roomnum,sitenum;
	UpdatePlayerData(ne,id,score,win,lose,draw,playerstate,roomnum,sitenum);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		g_Player.m_Score = score;
		g_Player.m_Win = win;
		g_Player.m_Lose = lose;
		g_Player.m_Draw = draw;

		CString s;
		s.Format("积分：%d",g_Player.m_Score);
		m_stScore.SetWindowTextA(s.GetString());
		s.Format("战绩：胜%d 平%d 负%d",g_Player.m_Win,g_Player.m_Draw,g_Player.m_Lose);
		m_stHistory.SetWindowTextA(s.GetString());

		if(playerstate == _PS_NONE)
		{
			if(g_Player.m_RoomNum != -1)
			{
				g_Rooms[g_Player.m_RoomNum].player[g_Player.m_SiteNum] = 0;
				g_Player.m_RoomNum = roomnum;
				g_Player.m_SiteNum = sitenum;
			}
			m_btRead.SetWindowTextA("准备");
		}
		else if(playerstate == _PS_WAIT)
		{
			m_btRead.SetWindowTextA("准备");
		}
		else if(playerstate == _PS_READY)
		{
			m_btRead.SetWindowTextA("取消准备");
		}
		else if(playerstate == _PS_PLAYING)
		{

		}

		g_Player.m_PlayState = playerstate;
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			it->second.m_Score = score;
			it->second.m_Win = win;
			it->second.m_Lose = lose;
			it->second.m_Draw = draw;

			if(playerstate == _PS_NONE)
			{
				if(it->second.m_RoomNum != -1)
				{
					g_Rooms[it->second.m_RoomNum].player[it->second.m_SiteNum] = 0;
					it->second.m_RoomNum = roomnum;
					it->second.m_SiteNum = sitenum;
				}
			}
			else if(playerstate == _PS_WAIT)
			{
				
			}
			else if(playerstate == _PS_READY)
			{
				
			}
			else if(playerstate == _PS_PLAYING)
			{

			}

			it->second.m_PlayState = playerstate;
		}
	}
	this->InvalidateRect(0);
}

//指定玩家做出选择
void CGameHallDlg::gh_MakeChoice(_CNET_EVENT& ne)
{
	std::string id;
	MakeChoice(ne,id);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		m_GameDlg.m_lbMessage.AddString("[系统]请做出选择！");
		int sel = m_GameDlg.game_MakeChoice();
		if(sel == _GS_CONTINUE)
		{
			CS_CHOICE_CONTINUE cs_cc;
			strcpy_s(cs_cc.ID,32,g_Player.m_ID.c_str());
			g_TcpClient.SendData(&cs_cc,sizeof(cs_cc));
		}
		else if(sel == _GS_STOP)
		{
			CS_CHOICE_STOP cs_cs;
			strcpy_s(cs_cs.ID,32,g_Player.m_ID.c_str());
			g_TcpClient.SendData(&cs_cs,sizeof(cs_cs));
		}
		else if(sel == _GS_GIVEUP)
		{
			CS_CHOICE_GIVEUP cs_cg;
			strcpy_s(cs_cg.ID,32,g_Player.m_ID.c_str());
			g_TcpClient.SendData(&cs_cg,sizeof(cs_cg));
		}
	}
	else
	{
		CString s;
		s.Format("[系统]等待玩家%s做出选择！",m_Adversary->m_Name.c_str());
		m_GameDlg.m_lbMessage.AddString(s.GetString());
	}
}

//玩家进行聊天
void CGameHallDlg::gh_TalkInGame(_CNET_EVENT& ne)
{
	std::string id;
	std::string msg;
	TalkInGame(ne,id,msg);

	CString s;

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		s.Format("[玩家]%s说：%s",g_Player.m_Name.c_str(),msg.c_str());
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			s.Format("[玩家]%s说：%s",it->second.m_Name.c_str(),msg.c_str());
		}
	}

	m_GameDlg.m_lbMessage.AddString(s.GetString());
}

//玩家获取到新的牌
void CGameHallDlg::gh_GetNew(_CNET_EVENT& ne)
{
	int newpoker = -1;
	GetNew(ne,newpoker);

	if(newpoker == -1)
	{
		m_AdversaryPokers[m_AdversaryPokersNum] = -1;
		m_AdversaryPokersNum += 1;
		CString s;
		s.Format("[系统]%s获得了一张新牌。",m_Adversary->m_Name.c_str());
		m_GameDlg.m_lbMessage.AddString(s.GetString());
	}
	else
	{
		m_MyPokers[m_MyPokersNum] = newpoker;
		m_iPlayerCurPoint += m_Pokers[newpoker].num;
		m_MyPokersNum += 1;
		m_GameDlg.m_lbMessage.AddString("[系统]你获得了一张新牌。");
	}
	m_GameDlg.InvalidateRect(0);
}
//玩家获得21点胜利
void CGameHallDlg::gh_Win_21(_CNET_EVENT& ne)
{
	std::string id;
	int lastpoker;
	int pokernum;
	int pokers[21];
	CString winner;
	Win_21(ne,id,lastpoker,pokernum,pokers);

	m_AdversaryPokersNum = pokernum;
	for(int i = 0; i < pokernum; ++i)
		m_AdversaryPokers[i] = pokers[i];
	m_GameDlg.InvalidateRect(0);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		m_MyPokers[m_MyPokersNum] = lastpoker;
		m_iPlayerCurPoint += m_Pokers[lastpoker].num;
		m_MyPokersNum += 1;
		winner.Format("[系统]%s获得了游戏胜利！",g_Player.m_Name.c_str());
		m_GameDlg.MessageBox("恭喜你获得了21点，游戏胜利！");
	}
	else
	{
		winner.Format("[系统]%s获得了游戏胜利！",m_Adversary->m_Name.c_str());
		m_GameDlg.MessageBox("对方获得了21点，游戏失败！");
	}

	m_GameDlg.m_lbMessage.AddString(winner.GetString());
}
//玩家因爆点失败
void CGameHallDlg::gh_LoseOutRange(_CNET_EVENT& ne)
{
	std::string id;
	int lastpoker;
	int pokernum;
	int pokers[21];
	CString winner;

	LoseOutRange(ne,id,lastpoker,pokernum,pokers);

	m_AdversaryPokersNum = pokernum;
	for(int i = 0; i < pokernum; ++i)
		m_AdversaryPokers[i] = pokers[i];
	m_GameDlg.InvalidateRect(0);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		m_MyPokers[m_MyPokersNum] = lastpoker;
		m_iPlayerCurPoint += m_Pokers[lastpoker].num;
		m_MyPokersNum += 1;
		m_GameDlg.InvalidateRect(0);
		winner.Format("[系统]%s获得了游戏胜利！",m_Adversary->m_Name.c_str());
		m_GameDlg.MessageBox("牌面爆点，游戏失败！");
	}
	else
	{
		winner.Format("[系统]%s获得了游戏胜利！",g_Player.m_Name.c_str());
		m_GameDlg.MessageBox("对方牌面爆点，游戏胜利！");
	}

	m_GameDlg.m_lbMessage.AddString(winner.GetString());
}
//玩家因放弃本局失败
void CGameHallDlg::gh_LoseGiveUp(_CNET_EVENT& ne)
{
	std::string id;
	LoseGiveUp(ne,id);
	CString lose;

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		lose.Format("[系统]%s获得了游戏胜利！",m_Adversary->m_Name.c_str());
		m_GameDlg.MessageBox("放弃本局，游戏失败！");
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			lose.Format("[系统]%s获得了游戏胜利！",g_Player.m_Name.c_str());
			m_GameDlg.MessageBox("对方放弃本局，游戏胜利！");
		}
	}

	m_GameDlg.m_lbMessage.AddString(lose.GetString());
}

//玩家因逃跑本局失败
void CGameHallDlg::gh_LoseRunAway(_CNET_EVENT& ne)
{
	std::string id;
	LoseRunAway(ne,id);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		if(m_GameDlg.showsel)
			m_GameDlg.gs.EndDlg();
		m_GameDlg.ShowWindow(SW_HIDE);

		MessageBox("怎么能逃跑呢！快去找回场子去！");
	}
	else
	{
		std::map<std::string,_PLAYER>::iterator it = g_OnlinePlayers.find(id);
		if(it != g_OnlinePlayers.end())
		{
			if(m_GameDlg.showsel)
				m_GameDlg.gs.EndDlg();
			m_GameDlg.ShowWindow(SW_HIDE);

			MessageBox("对手逃跑了~恭喜你获得胜利！");
		}
	}
}

//玩家最终比点数获胜
void CGameHallDlg::gh_WinBigger(_CNET_EVENT& ne)
{
	std::string id;
	int pokernum;
	int pokers[21];
	CString winner;

	WinBigger(ne,id,pokernum,pokers);

	m_AdversaryPokersNum = pokernum;
	for(int i = 0; i < pokernum; ++i)
		m_AdversaryPokers[i] = pokers[i];
	m_GameDlg.InvalidateRect(0);

	if(strcmp(id.c_str(),g_Player.m_ID.c_str()) == 0)
	{
		winner.Format("[系统]%s获得了游戏胜利！",g_Player.m_Name.c_str());
		m_GameDlg.MessageBox("我方点数大于对方，游戏胜利！");
	}
	else
	{
		winner.Format("[系统]%s获得了游戏胜利！",m_Adversary->m_Name.c_str());
		m_GameDlg.MessageBox("我方点数小于对方，游戏失败！");
	}
	m_GameDlg.m_lbMessage.AddString(winner.GetString());
}
//玩家最终比点数平局
void CGameHallDlg::gh_Draw(_CNET_EVENT& ne)
{
	int pokernum;
	int pokers[21];

	Draw(ne,pokernum,pokers);

	m_AdversaryPokersNum = pokernum;
	for(int i = 0; i < pokernum; ++i)
		m_AdversaryPokers[i] = pokers[i];

	m_GameDlg.m_lbMessage.AddString("[系统]游戏平局!");
	m_GameDlg.InvalidateRect(0);

	m_GameDlg.MessageBox("游戏平局！");
}

//收到游戏结束消息
void CGameHallDlg::gh_GameEnd(_CNET_EVENT& ne)
{
}

void CGameHallDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_Player.m_PlayState == _PS_WAIT)
	{
		CS_READ cs_r;
		strcpy_s(cs_r.ID,32,g_Player.m_ID.c_str());
		g_TcpClient.SendData(&cs_r,sizeof(cs_r));
		m_GameDlg.ShowWindow(SW_HIDE);
	}
	else if(g_Player.m_PlayState == _PS_READY)
	{
		CS_READY_CANCEL cs_rc;
		strcpy_s(cs_rc.ID,32,g_Player.m_ID.c_str());
		g_TcpClient.SendData(&cs_rc,sizeof(cs_rc));
	}
}

void CGameHallDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_Player.m_PlayState == _PS_READY || g_Player.m_PlayState == _PS_PLAYING)
	{
		MessageBox("当前状态不能退出房间。");
	}
	else if(g_Player.m_RoomNum != -1)
	{
		CS_EXIT_ROOM cs_er;
		strcpy_s(cs_er.ID,32,g_Player.m_ID.c_str());
		g_TcpClient.SendData(&cs_er,sizeof(cs_er));
	}
}



