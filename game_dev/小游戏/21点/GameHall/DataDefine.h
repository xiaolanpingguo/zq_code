#ifndef _DATA_DEFINE_H_
#define _DATA_DEFINE_H_

#include <map>
#include <string>
#include "DataType.h"
#include "TcpClient.h"

#define _FACE_NUM 58
#define _R_VIEW_W 4
#define _R_VIEW_H 2
#define _SITE_NUM (_R_VIEW_W * _R_VIEW_H * 2)
#define _ROOM_NUM 64

class CPTalkDlg;
class CDC;
class CPMDispatcher;

extern SOCKET g_Socket;//套接字
extern _PLAYER g_Player;//当前客户端的用户
extern CTcpClient g_TcpClient;//Tcp控制器
extern std::map<std::string,_PLAYER> g_OnlinePlayers;//在线玩家表
extern std::map<std::string,CPTalkDlg*> g_PTalkDlgs;//私聊对话框
extern bool g_bInit;//是否初始化完成

extern CDC g_Table;//游戏桌纹理
extern CDC g_Title;//游戏标题纹理
extern CDC g_Room;//游戏房间纹理
extern CDC g_Pokers;//扑克纹理
extern CDC g_Faces[_FACE_NUM];//玩家头像纹理
extern RECT g_Site[_SITE_NUM];//座位矩形
extern _ROOM g_Rooms[_ROOM_NUM];//房间数据
extern CPMDispatcher g_PMDispatcher;//协议派发器

#endif