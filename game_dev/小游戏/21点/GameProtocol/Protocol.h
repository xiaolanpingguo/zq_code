#ifndef _PROTOCOL_H
#define _PROTOCOL_H


/*
//--------------游戏协议--------------
//--------0-100为登陆注册用的协议---------
//--------101-200为大厅所用协议-------
//--------201-300为游戏21点所用协议-------
*/

#define P_LOGIN_MIN 0
#define P_LOGIN_MAX 100

#define P_HALL_MIN  101
#define P_HALL_MAX  200

#define P_GAME_BLACK_JACK_MIN 201
#define P_GAME_BLACK_JACK_MAX 300

//协议原型
struct _PROTOCOL
{
	int type;
};

#endif