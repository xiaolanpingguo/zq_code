#ifndef _GAME_PROTOCOL_H_
#define _GAME_PROTOCOL_H_

#define _TRY_NICK_NAME 1 //(客户端->服务器)检查昵称
#define _NICK_NAME_LAWLESS 2 //(服务器->客户端)昵称非法
#define _NICK_NAME_LEGALITY 3 //(服务器->客户端)昵称合法
#define _NEW_PLAYER_ENTER 4 //(服务器（群）->客户端)新玩家进入
#define _SEND_TALK 5 //(客户端->服务器)聊天
#define _PLAYER_TALK 6 //(服务器（群）->客户端)聊天
#define _SEND_WALK 7 //(客户端->服务器)移动
#define _PLAYER_WALK 8 //(服务器（群）->客户端)移动
#define _PLAYER_QUIT 9 //(服务器（群）->客户端)退出

struct _GAME_PROTOCOL
{
	int id; //协议的id
};

struct _C_S_GP1 : public _GAME_PROTOCOL
{
	_C_S_GP1(){id = _TRY_NICK_NAME;}
	char nick_name[32];
};

struct _S_C_GP2 : public _GAME_PROTOCOL
{
	_S_C_GP2(){id = _NICK_NAME_LAWLESS;}
};

#define _GAME_MAP_W 32 //地图宽
#define _GAME_MAP_H 32 //地图高
#define _GAME_MAP_S (_GAME_MAP_W * _GAME_MAP_H) //地图总大小
#define _ZA 0 //障碍
#define _TL 1 //通路
#define _MAX_PLAYER 32 //最大玩家数量

struct _PLAYER //玩家结构体
{
	char nick_name[32];
	int x, y;
};

struct _S_C_GP3 : public _GAME_PROTOCOL
{
	_S_C_GP3(){id = _NICK_NAME_LEGALITY;}
	char map[_GAME_MAP_S]; //地图
	int player_num; //玩家数量
	_PLAYER player[_MAX_PLAYER]; //玩家
};

struct _S_C_GP4 : public _GAME_PROTOCOL
{
	_S_C_GP4(){id = _NEW_PLAYER_ENTER;}
	_PLAYER new_player; //玩家
};

struct _C_S_GP5 : public _GAME_PROTOCOL
{
	_C_S_GP5(){id = _SEND_TALK;}
	char talk[256];
};

struct _S_C_GP6 : public _GAME_PROTOCOL
{
	_S_C_GP6(){id = _PLAYER_TALK;}
	char talk[256]; //talk之前先加上昵称
};

struct _C_S_GP7 : public _GAME_PROTOCOL
{
	_C_S_GP7(){id = _SEND_WALK;}
	int x, y;
};

struct _S_C_GP8 : public _GAME_PROTOCOL
{
	_S_C_GP8(){id = _PLAYER_WALK;}
	_PLAYER player; //玩家信息
};

struct _S_C_GP9 : public _GAME_PROTOCOL
{
	_S_C_GP9(){id = _PLAYER_QUIT;}
	char nick_name[32];
};

#endif