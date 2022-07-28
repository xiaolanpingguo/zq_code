#include "Resource.h"
#include "GameHallDlg.h"
#include "ProtocolIndex.h"

CProtocolIndex::CProtocolIndex(CGameHallDlg* p)
:
m_pCGameHallDlg(p)
{}

void CProtocolIndex::ProtocolFun(_CNET_EVENT& ne)
{}

//--------------------------------------------------------------------------------------
//登陆相关
//--------------------------------------------------------------------------------------

//客户端登录成功协议
CPI_LoginSuccess::CPI_LoginSuccess(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_LoginSuccess::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_LoginSuccess(ne);
}

//客户端新玩家登录协议

CPI_NewClientLogin::CPI_NewClientLogin(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_NewClientLogin::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_NewClientLogin(ne);
}

//--------------------------------------------------------------------------------------
//大厅相关
//--------------------------------------------------------------------------------------

//客户端修改资料成功协议
CPI_DataChangeSuccess::CPI_DataChangeSuccess(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_DataChangeSuccess::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_ChangeDataSuccess(ne);
}

//客户端修改资料失败协议
CPI_DataChangeFailed::CPI_DataChangeFailed(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_DataChangeFailed::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_ChangeDataFailed(ne);
}

//客户端公共聊天协议
CPI_PublicTalk::CPI_PublicTalk(CGameHallDlg* p)
:
CProtocolIndex(p)
{}
void CPI_PublicTalk::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_PublicTalk(ne);
}

//客户端私人聊天协议
CPI_PrivateTalk::CPI_PrivateTalk(CGameHallDlg* p)
:
CProtocolIndex(p)
{}
void CPI_PrivateTalk::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_PrivateTalk(ne);
}

//客户端玩家离线协议
CPI_PlayerOffLine::CPI_PlayerOffLine(CGameHallDlg* p)
:
CProtocolIndex(p)
{}
void CPI_PlayerOffLine::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_PlayerOffLine(ne);
}

//客户端进入房间成功
CPI_EnterRoomSuccess::CPI_EnterRoomSuccess(CGameHallDlg* p)
:
CProtocolIndex(p)
{}
void CPI_EnterRoomSuccess::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_EnterRoomSuccess(ne);
}

//客户端玩家离线协议
CPI_EnterRoomFail::CPI_EnterRoomFail(CGameHallDlg* p)
:
CProtocolIndex(p)
{}
void CPI_EnterRoomFail::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_EnterRoomFail(ne);
}

//客户端准备成功
CPI_ReadSuccess::CPI_ReadSuccess(CGameHallDlg* p)
:
CProtocolIndex(p)
{}
void CPI_ReadSuccess::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_ReadSuccess(ne);
}

//客户端退出房间成功
CPI_ExitRoomSuccess::CPI_ExitRoomSuccess(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_ExitRoomSuccess::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_ExitRoomSuccess(ne);
}

//客户端取消准备成功
CPI_ReadyCancelSuccess::CPI_ReadyCancelSuccess(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_ReadyCancelSuccess::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_ReadyCancelSuccess(ne);
}

//--------------------------------------------------------------------------------------
//游戏相关
//--------------------------------------------------------------------------------------
//开始新游戏
CPI_NewGame::CPI_NewGame(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_NewGame::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_NewGame(ne);
}

//更新玩家战绩
CPI_UpdatePlayerData::CPI_UpdatePlayerData(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_UpdatePlayerData::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_UpdatePlayerData(ne);
}

//指定玩家做出选择
CPI_MakeChoice::CPI_MakeChoice(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_MakeChoice::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_MakeChoice(ne);
}

//指定玩家进行聊天
CPI_TalkInGame::CPI_TalkInGame(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_TalkInGame::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_TalkInGame(ne);
}

//玩家获取到新的牌
CPI_GetNew::CPI_GetNew(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_GetNew::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_GetNew(ne);
}

//玩家获得21点胜利
CPI_Win_21::CPI_Win_21(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_Win_21::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_Win_21(ne);
}

//玩家因爆点失败
CPI_LoseOutRange::CPI_LoseOutRange(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_LoseOutRange::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_LoseOutRange(ne);
}

//玩家因放弃本局失败
CPI_LoseGiveUp::CPI_LoseGiveUp(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_LoseGiveUp::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_LoseGiveUp(ne);
}

//玩家因逃跑本局失败
CPI_LoseRunAway::CPI_LoseRunAway(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_LoseRunAway::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_LoseRunAway(ne);
}

//玩家最终比点数获胜
CPI_WinBigger::CPI_WinBigger(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_WinBigger::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_WinBigger(ne);
}

//玩家最终比点数平局
CPI_Draw::CPI_Draw(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_Draw::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_Draw(ne);
}

//游戏结束消息
CPI_GameEnd::CPI_GameEnd(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_GameEnd::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_GameEnd(ne);
}
