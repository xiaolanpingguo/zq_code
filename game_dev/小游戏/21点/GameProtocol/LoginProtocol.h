#ifndef LOGIN_PROTOCOL_H_
#define LOGIN_PROTOCOL_H_

#include "Protocol.h"
/*
//--------------游戏协议--------------
//--------0-100为登陆注册用的协议---------
//--------101-200为大厅所用协议-------
//--------201-300为游戏21点所用协议-------
*/

//登陆相关
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

#define DL_CS_DL			0//登陆（C-S)
#define DL_CS_ZC			1//注册（C-S)

#define DL_SC_NO_ID			2//没有账户（S-C)
#define DL_SC_PW_ERROR		3//密码错误（S-C)
#define DL_SC_DL_OK			4//登陆成功（S-C)
#define DL_SC_NEW_CLIENT	5//新玩家上线（S-C)
#define DL_SC_ZC_FAIL		6//注册失败（S-C)
#define DL_SC_ZC_OK			7//注册成功（S-C)
#define DL_SC_DL_AGAIN		8//重复登陆（S-C)


//登陆相关
//----------------------------------------------------------------------------------
//1:客户端请求服务器（C-S）
//----------------------------------------------------------------------------------
//登陆
struct CS_DL : public _PROTOCOL
{
	CS_DL(){type = DL_CS_DL;}
	char id[32];
	char pw[32];
};

//注册
struct CS_ZC : public _PROTOCOL
{
	CS_ZC(){type = DL_CS_ZC;}
	char id[32];
	char pw[32];
};

//----------------------------------------------------------------------------------
//2:服务器反馈客户端（S-C）
//----------------------------------------------------------------------------------
//账号不存在
struct SC_NO_ID : public _PROTOCOL
{
	SC_NO_ID(){type = DL_SC_NO_ID;}
};

//密码错误
struct SC_PW_ERROR : public _PROTOCOL
{
	SC_PW_ERROR(){type = DL_SC_PW_ERROR;}
};

//登陆
struct SC_DL_OK : public _PROTOCOL
{
	SC_DL_OK(){type = DL_SC_DL_OK;}
	int num;
	//后面要添加所有其它玩家的信息
};

//新用户
struct SC_NEW_CLIENT : public _PROTOCOL
{
	SC_NEW_CLIENT(){type = DL_SC_NEW_CLIENT;}
};

//注册失败
struct SC_ZC_FAIL : public _PROTOCOL
{
	SC_ZC_FAIL(){type = DL_SC_ZC_FAIL;}
};

//注册成功
struct SC_ZC_OK : public _PROTOCOL
{
	SC_ZC_OK(){type = DL_SC_ZC_OK;}
};

//玩家重复登录
struct SC_DL_AGAIN : public _PROTOCOL
{
	SC_DL_AGAIN(){ type = DL_SC_DL_AGAIN; }
};

#endif