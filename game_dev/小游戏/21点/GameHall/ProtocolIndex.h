#ifndef _PROTOCOL_INDEX_H_
#define _PROTOCOL_INDEX_H_
#include "DataDefine.h"

class CGameHallDlg;

class CProtocolIndex
{
protected:
	CGameHallDlg* m_pCGameHallDlg;
public:
	CProtocolIndex(CGameHallDlg* p);
	virtual void ProtocolFun(_CNET_EVENT& ne);
};

//--------------------------------------------------------------------------------------
//登陆相关
//--------------------------------------------------------------------------------------
//客户端登录成功协议
class CPI_LoginSuccess : public CProtocolIndex
{
public:
	CPI_LoginSuccess(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//客户端新玩家登录协议
class CPI_NewClientLogin : public CProtocolIndex
{
public:
	CPI_NewClientLogin(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//--------------------------------------------------------------------------------------
//大厅相关
//--------------------------------------------------------------------------------------
//客户端修改资料成功协议
class CPI_DataChangeSuccess : public CProtocolIndex
{
public:
	CPI_DataChangeSuccess(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//客户端修改资料失败协议
class CPI_DataChangeFailed : public CProtocolIndex
{
public:
	CPI_DataChangeFailed(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//客户端公共聊天协议
class CPI_PublicTalk : public CProtocolIndex
{
public:
	CPI_PublicTalk(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//客户端私人聊天协议
class CPI_PrivateTalk : public CProtocolIndex
{
public:
	CPI_PrivateTalk(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//客户端玩家离线协议
class CPI_PlayerOffLine : public CProtocolIndex
{
public:
	CPI_PlayerOffLine(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//客户端进入房间成功
class CPI_EnterRoomSuccess : public CProtocolIndex
{
public:
	CPI_EnterRoomSuccess(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//客户端进入房间失败
class CPI_EnterRoomFail : public CProtocolIndex
{
public:
	CPI_EnterRoomFail(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//客户端准备成功
class CPI_ReadSuccess : public CProtocolIndex
{
public:
	CPI_ReadSuccess(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//客户端退出房间成功
class CPI_ExitRoomSuccess : public CProtocolIndex
{
public:
	CPI_ExitRoomSuccess(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//客户端取消准备成功
class CPI_ReadyCancelSuccess : public CProtocolIndex
{
public:
	CPI_ReadyCancelSuccess(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//--------------------------------------------------------------------------------------
//游戏相关
//--------------------------------------------------------------------------------------
//开始新游戏
class CPI_NewGame : public CProtocolIndex
{
public:
	CPI_NewGame(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//更新玩家数据
class CPI_UpdatePlayerData : public CProtocolIndex
{
public:
	CPI_UpdatePlayerData(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//指定玩家做出选择
class CPI_MakeChoice : public CProtocolIndex
{
public:
	CPI_MakeChoice(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//指定玩家进行聊天
class CPI_TalkInGame : public CProtocolIndex
{
public:
	CPI_TalkInGame(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//玩家获取到新的牌
class CPI_GetNew : public CProtocolIndex
{
public:
	CPI_GetNew(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//玩家获得21点胜利
class CPI_Win_21 : public CProtocolIndex
{
public:
	CPI_Win_21(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//玩家因爆点失败
class CPI_LoseOutRange : public CProtocolIndex
{
public:
	CPI_LoseOutRange(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};
//玩家因放弃本局失败
class CPI_LoseGiveUp : public CProtocolIndex
{
public:
	CPI_LoseGiveUp(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};
//玩家因逃跑本局失败
class CPI_LoseRunAway : public CProtocolIndex
{
public:
	CPI_LoseRunAway(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};
//玩家最终比点数获胜
class CPI_WinBigger : public CProtocolIndex
{
public:
	CPI_WinBigger(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};
//玩家最终比点数平局
class CPI_Draw : public CProtocolIndex
{
public:
	CPI_Draw(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//游戏结束消息
class CPI_GameEnd : public CProtocolIndex
{
public:
	CPI_GameEnd(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};
#endif