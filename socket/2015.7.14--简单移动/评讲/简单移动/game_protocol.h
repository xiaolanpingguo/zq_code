#ifndef _GAME_PROTOCOL_H_
#define _GAME_PROTOCOL_H_

#define _NEW_PLAYER 0
#define _OLD_PLAYER 1
#define _PLAYER_MOVE 2
#define _SOMEONE_MOVE 3
#define _PLAYER_QUIT 4

//玩家信息
struct _GAME_PLAYER
{
	int name, x, y;
};

//游戏协议
struct _GAME_PROTOCOL
{
	int id; //协议的id号
};

//0号协议：服务器通知新玩家他/她/它的名字、位置、老玩家信息
struct _SC_NEW_PLAYER : public _GAME_PROTOCOL
{
	_SC_NEW_PLAYER()
	{
		id = _NEW_PLAYER;
	}
	_GAME_PLAYER new_player; //新玩家数据
	int old_player_num; //老玩家数量
	_GAME_PLAYER old_player[25]; //老玩家信息
};

//1号协议：服务器通知老玩家新进入的玩家他/她/它的名字、位置
struct _SC_OLD_PLAYER : public _GAME_PROTOCOL
{
	_SC_OLD_PLAYER()
	{
		id = _OLD_PLAYER;
	}
	_GAME_PLAYER new_player; //新玩家数据
};

//2号协议：客户端移动之后通知服务器他自己的位置
struct _CS_PLAYER_MOVE : public _GAME_PROTOCOL
{
	_CS_PLAYER_MOVE()
	{
		id = _PLAYER_MOVE;
	}
	_GAME_PLAYER player; //玩家数据
};

//3号协议：服务器通知其它玩家有玩家移动了
struct _SC_SOMEONE_MOVE : public _GAME_PROTOCOL
{
	_SC_SOMEONE_MOVE()
	{
		id = _SOMEONE_MOVE;
	}
	_GAME_PLAYER player; //玩家数据
};

//4号协议：服务器通知其它玩家有玩家离开了
struct _SC_PLAYER_QUIT : public _GAME_PROTOCOL
{
	_SC_PLAYER_QUIT()
	{
		id = _PLAYER_QUIT;
	}
	int name; //玩家名字
};

#endif