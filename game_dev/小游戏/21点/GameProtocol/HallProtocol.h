#ifndef _HALL_PROTOCOL_H_
#define _HALL_PROTOCOL_H_


/*
//--------------游戏协议--------------
//--------0-100为登陆注册用的协议---------
//--------101-200为大厅所用协议-------
//--------201-300为游戏21点所用协议-------
*/


//大厅相关
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

#define HALL_CS_PUB_TALK			101//大厅公共聊天（C-S)
#define HALL_CS_PRI_TALK			102//私聊（C-S)
#define HALL_CS_CHANGE_DATA			103//修改资料（C-S)
#define HALL_CS_ENTER_ROOM         109//进入房间(C-S)
#define HALL_CS_READ               111//准备游戏(C-S)
#define HALL_CS_EXIT_ROOM          112//退出房间(C-S)
#define HALL_CS_READY_CANCEL        115//取消准备(C-S)

#define HALL_SC_PLAYER_OFFLINE		104//玩家离线（S-C)
#define HALL_SC_PUB_TALK			105//大厅公共聊天（S-C)
#define HALL_SC_PRI_TALK			106//私聊（S-C)
#define HALL_SC_CHANGE_DATA			107//修改资料成功（S-C)		
#define HALL_SC_CHANGE_DATA_FAIL	108//修改资料失败（S-C)
#define HALL_SC_ENTER_ROOM_SUCCESS  109//进入房间成功(S-C)
#define HALL_SC_ENTER_ROOM_FAIL     110//进入房间失败(S-C)
#define HALL_SC_READ_SUCCESS       113//准备游戏成功(S-C)
#define HALL_SC_EXIT_ROOM_SUCCESS   114//退出房间成功(S-C)
#define HALL_SC_READY_CANCEL_SUCCESS 116//取消准备成功(S-C)


//大厅相关
//----------------------------------------------------------------------------------
//1:客户端请求服务器(C-S)
//----------------------------------------------------------------------------------
//公共聊天
struct CS_PUB_TALK : public _PROTOCOL
{
	CS_PUB_TALK(){ type = HALL_CS_PUB_TALK; }
	char ID[32];
	char Message[256];
};

//私人聊天
struct CS_PRI_TALK : public _PROTOCOL
{
	CS_PRI_TALK(){ type = HALL_CS_PRI_TALK; }
	char ID[32];
	char DESID[32];
	char Message[256];
};

//修改资料
struct CS_CHANGE_DATA : public _PROTOCOL
{
	CS_CHANGE_DATA(){ type = HALL_CS_CHANGE_DATA; }
	char ID[32];
	int facenum;
	char Name[32];
};

//进入房间
struct CS_ENTER_ROOM : public _PROTOCOL
{
	CS_ENTER_ROOM(){ type = HALL_CS_ENTER_ROOM; }
	char ID[32];
	int RoomNumNew;
	int SiteNumNew;
};

//准备游戏
struct CS_READ : public _PROTOCOL
{
	CS_READ(){ type = HALL_CS_READ; }
	char ID[32];
};

//退出房间
struct CS_EXIT_ROOM : public _PROTOCOL
{
	CS_EXIT_ROOM(){ type = HALL_CS_EXIT_ROOM; }
	char ID[32];
};

//取消准备
struct CS_READY_CANCEL : public _PROTOCOL
{
	CS_READY_CANCEL(){ type = HALL_CS_READY_CANCEL; }
	char ID[32];
};

//-----------------------------------------------------------------------------
//2:服务器反馈客户端（S-C）
//----------------------------------------------------------------------------------

//玩家离线
struct SC_PLAYER_OFFLINE : public _PROTOCOL
{
	SC_PLAYER_OFFLINE(){ type = HALL_SC_PLAYER_OFFLINE; }
	char ID[32];
};

//公共聊天
struct SC_PUB_TALK : public _PROTOCOL
{
	SC_PUB_TALK(){ type = HALL_SC_PUB_TALK; }
	char ID[32];
	char Message[256];
};

//私人聊天
struct SC_PRI_TALK : public _PROTOCOL
{
	SC_PRI_TALK(){ type = HALL_SC_PRI_TALK; }
	char ID[32];
	char DESID[32];
	char Message[256];
};

//修改资料成功
struct SC_CHANGE_DATA : public _PROTOCOL
{
	SC_CHANGE_DATA(){ type = HALL_SC_CHANGE_DATA; }
	char ID[32];
	int facenum;
	char Name[32];
};

//修改资料失败
struct SC_CHANGE_DATA_FAIL : public _PROTOCOL
{
	SC_CHANGE_DATA_FAIL(){ type = HALL_SC_CHANGE_DATA_FAIL; }
};

//进入房间成功
struct SC_ENTER_ROOM_SUCCESS : public _PROTOCOL
{
	SC_ENTER_ROOM_SUCCESS(){ type = HALL_SC_ENTER_ROOM_SUCCESS; }
	char ID[32];
	int RoomNumNew;
	int SiteNumNew;
};

//进入房间失败
struct SC_ENTER_ROOM_FAIL : public _PROTOCOL
{
	SC_ENTER_ROOM_FAIL(){ type = HALL_SC_ENTER_ROOM_FAIL; }
};

//准备游戏成功
struct SC_READ_SUCCESS : public _PROTOCOL
{
	SC_READ_SUCCESS(){ type = HALL_SC_READ_SUCCESS; }
	char ID[32];
};

//退出房间成功
struct SC_EXIT_ROOM_SUCCESS : public _PROTOCOL
{
	SC_EXIT_ROOM_SUCCESS(){ type = HALL_SC_EXIT_ROOM_SUCCESS; }
	char ID[32];
};

//取消准备成功
struct SC_READY_CANCEL_SUCCESS : public _PROTOCOL
{
	SC_READY_CANCEL_SUCCESS(){ type = HALL_SC_READY_CANCEL_SUCCESS; }
	char ID[32];
};

#endif