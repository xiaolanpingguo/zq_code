#ifndef _BLACK_JACK_PROTOCOL_H_
#define _BLACK_JACK_PROTOCOL_H_

#include "Protocol.h"
/*
//--------------游戏协议--------------
//--------0-100为登陆注册用的协议---------
//--------101-200为大厅所用协议-------
//--------201-300为游戏21点所用协议-------
*/

//21点相关
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
#define GAME_SC_NEW_GAME             201//开始新游戏(S-C)
#define GAME_SC_UPDATE_PLAYER_DATA   202//更新玩家战绩(S-C)
#define GAME_SC_MAKE_CHOICE          203//指定玩家做出选择(S-C)
#define GAME_SC_TALK_IN_GAME         204//玩家进行聊天(S-C)
#define GAME_SC_GAME_END             205//本局游戏结束(S-C)

#define GAME_SC_GET_NEW              206//玩家成功获取到新的牌(S-C)
#define GAME_SC_WIN_21               207//玩家获得21点胜利(S-C)
#define GAME_SC_LOSE_OUT_RANGE       208//玩家因爆点失败(S-C)
#define GAME_SC_LOSE_GIVEUP          209//玩家因放弃本局失败(S-C)
#define GAME_SC_LOSE_RUN_AWAY        210//玩家因逃跑本局失败(S-C)
#define GAME_SC_WIN_BIGGER           211//玩家最终比点数获胜(S-C)
#define GAME_SC_DRAW                 212//玩家最终比点数平局(S-C)

#define GAME_CS_CHOICE_CONTINUE      213//玩家选择继续拿牌(C-S)
#define GAME_CS_CHOICE_STOP          214//玩家选择停止拿牌(C-S)
#define GAME_CS_CHOICE_GIVEUP        215//玩家选择放弃本轮(C-S)
#define GAME_CS_TALK_IN_GAME         216//玩家进行聊天(C-S)
#define GAME_CS_RUN_AWAY             217//玩家逃跑(C-S)

//21点相关
//----------------------------------------------------------------------------------
//1:客户端请求服务器（C-S）
//----------------------------------------------------------------------------------
//玩家选择继续拿牌(C-S)
struct CS_CHOICE_CONTINUE : public _PROTOCOL
{
	CS_CHOICE_CONTINUE(){type = GAME_CS_CHOICE_CONTINUE;}
	char ID[32];//玩家ID
};

//玩家选择停止拿牌(C-S)
struct CS_CHOICE_STOP : public _PROTOCOL
{
	CS_CHOICE_STOP(){type = GAME_CS_CHOICE_STOP;}
	char ID[32];//玩家ID
};

//玩家选择放弃本局(C-S)
struct CS_CHOICE_GIVEUP : public _PROTOCOL
{
	CS_CHOICE_GIVEUP(){type = GAME_CS_CHOICE_GIVEUP;}
	char ID[32];//玩家ID
};

//玩家进行聊天(C-S)
struct CS_TALK_IN_GAME : public _PROTOCOL
{
	CS_TALK_IN_GAME(){type = GAME_CS_TALK_IN_GAME;}
	char ID[32];//玩家ID
	char msg[256];//说话内容
};

//玩家逃跑(C-S)
struct CS_RUN_AWAY : public _PROTOCOL
{
	CS_RUN_AWAY(){type = GAME_CS_RUN_AWAY;}
	char ID[32];//玩家ID
};

//----------------------------------------------------------------------------------
//2:服务器反馈客户端（S-C）
//----------------------------------------------------------------------------------
//新游戏
struct SC_NEW_GAME : public _PROTOCOL
{
	SC_NEW_GAME(){type = GAME_SC_NEW_GAME;}
	char ID[32];//对手ID
	int firstpokernum;//第一张牌的编号，为-1表示接收者与本局游戏无关，只是更新状态
};

//更新玩家状态
struct SC_UPDATE_PLAYER_DATA : public _PROTOCOL
{
	SC_UPDATE_PLAYER_DATA(){type = GAME_SC_UPDATE_PLAYER_DATA;}
	char ID[32];//更新的玩家ID
	int score;//积分
	int win;//胜
	int lose;//负
	int draw;//平
	int playerstate;//玩家状态
	int roomnum;//房间号
	int sitenum;//座位号
};

//指定玩家做出选择(S-C)
struct SC_MAKE_CHOICE : public _PROTOCOL
{
	SC_MAKE_CHOICE(){type = GAME_SC_MAKE_CHOICE;}
	char ID[32];//玩家ID
};

//玩家进行聊天(S-C)
struct SC_TALK_IN_GAME : public _PROTOCOL
{
	SC_TALK_IN_GAME(){type = GAME_SC_TALK_IN_GAME;}
	char ID[32];//玩家ID
	char msg[256];//说话内容
};

//本局游戏结束(S-C)
struct SC_GAME_END : public _PROTOCOL
{
	SC_GAME_END(){type = GAME_SC_GAME_END;}
	char ID[32];//玩家ID
	int state;//游戏结束之后的状态
};

//玩家成功获取到新的牌(S-C)
struct SC_GET_NEW : public _PROTOCOL
{
	SC_GET_NEW(){type = GAME_SC_GET_NEW;}
	int newpoker;//(获得的牌，如果是-1表示是对方拿牌)
};

//玩家获得21点胜利(S-C)
struct SC_WIN_21 : public _PROTOCOL
{
	SC_WIN_21(){type = GAME_SC_WIN_21;}
	char winID[32];
	int lastpoker;
	int pokernum;
	int pokers[21];
};

//玩家因爆点失败(S-C)
struct SC_LOSE_OUT_RANGE : public _PROTOCOL
{
	SC_LOSE_OUT_RANGE(){type = GAME_SC_LOSE_OUT_RANGE;}
	char loseID[32];
	int lastpoker;
	int pokernum;
	int pokers[21];
};

//玩家因放弃本局失败(S-C)
struct SC_LOSE_GIVEUP : public _PROTOCOL
{
	SC_LOSE_GIVEUP(){type = GAME_SC_LOSE_GIVEUP;}
	char loseID[32];
};

//玩家因逃跑本局失败(S-C)
struct SC_LOSE_RUN_AWAY : public _PROTOCOL
{
	SC_LOSE_RUN_AWAY(){type = GAME_SC_LOSE_RUN_AWAY;}
	char loseID[32];
};

//玩家最终比点数获胜(S-C)
struct SC_WIN_BIGGER : public _PROTOCOL
{
	SC_WIN_BIGGER(){type = GAME_SC_WIN_BIGGER;}
	char winID[32];
	int pokernum;
	int pokers[21];
};

//玩家最终比点数平局(S-C)
struct SC_DRAW : public _PROTOCOL
{
	SC_DRAW(){type = GAME_SC_DRAW;}
	int pokernum;
	int pokers[21];
};

#endif