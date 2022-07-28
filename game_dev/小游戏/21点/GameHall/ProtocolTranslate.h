#ifndef _PROTOCOL_TRANSLATE_H_
#define _PROTOCOL_TRANSLATE_H_

#include "DataType.h"
#include <map>
#include "TcpClient.h"
//----------------------------------------------------------------------------------------------
//登陆相关
//----------------------------------------------------------------------------------------------
//----------------------------------
//服务器向客户端发送消息(C-S消息)
//----------------------------------
//1.注册账号
//参数：注册用账号，密码，Tcp客户端类
void Register(const char* id, const char* pw, CTcpClient& tc);

//2.登陆账号
//参数：登陆用账号，密码，Tcp客户端类
void Login(const char* id, const char* pw, CTcpClient& tc);

//----------------------------------
//客户端接受服务器消息反馈(S-C消息)
//----------------------------------
//1.登陆成功
//参数：客户端事件消息，需要填充的当前在线玩家表
void LoginSuccess(_CNET_EVENT& ne,std::map<std::string,_PLAYER>& players);

//2.新玩家登陆成功
//参数：客户端事件消息，填充的玩家信息，当前客户端玩家的ID号
//返回true表示是玩家自己的信息
//返回false表示是其他玩家登入的信息
bool NewClientLogin(_CNET_EVENT& ne,_PLAYER& player,std::string clientid);


//----------------------------------------------------------------------------------------------
//大厅相关
//----------------------------------------------------------------------------------------------
//1.玩家修改成功
//参数：客户端事件消息，填充的名字，头像，填充的ID号
//返回true表示是玩家自己的信息
//返回false表示是其他玩家登入的信息
void ChangeDataSuccess(_CNET_EVENT& ne,std::string& name, int& face, std::string& clientid);

//2.公共聊天
//参数：客户端事件消息，填充的发送者id，填充的发送内容
void PublicTalk(_CNET_EVENT& ne,std::string& id, std::string& message);

//3.私人聊天
//参数：客户端事件消息，填充的发送者id，填充的发送内容
void PrivateTalk(_CNET_EVENT& ne,std::string& id, std::string& desid, std::string& message);

//4.玩家离线
//参数：客户端事件消息，填充的离线者id
void PlayerOffLine(_CNET_EVENT& ne,std::string& id);

//5.玩家进入房间成功
//参数：客户端事件消息，填充的进入房间者id, 新房间号，新座位号
void EnterRoomSuccess(_CNET_EVENT& ne,std::string& id, int& roomnew, int& sitenew);

//6.玩家准备成功
//参数：客户端事件消息，填充准备者id
void ReadSuccess(_CNET_EVENT& ne,std::string& id);

//7.玩家退出房间成功
//参数：客户端事件消息，填充的退出房间者id
void ExitRoomSuccess(_CNET_EVENT& ne,std::string& id);

//8.玩家取消准备成功
//参数：客户端事件消息，填充准备者id
void ReadyCancelSuccess(_CNET_EVENT& ne,std::string& id);

//----------------------------------------------------------------------------------------------
//游戏相关
//----------------------------------------------------------------------------------------------
//1.开始新游戏
//参数：客户端事件消息，填充对手id，获得的初始牌
void NewGame(_CNET_EVENT& ne,std::string& id,int &num);

//2.更新玩家数据
//参数：客户端事件消息，填充准备者id,积分，胜，负，平
void UpdatePlayerData(_CNET_EVENT& ne,std::string& id,
					  int& score, int& win, int& lose, int& draw);

//3.玩家做出选择
//参数：客户端事件消息，填充对手id
void MakeChoice(_CNET_EVENT& ne,std::string& id);

//4.玩家获得新牌
//参数：客户端事件消息，填充牌编号
void GetNew(_CNET_EVENT& ne,int &num);

//5玩家获得21点胜利
//参数：客户端事件消息，填充胜利者id, 胜利者的最后一张牌，另一方的牌的数量，另一方的牌面
void Win_21(_CNET_EVENT& ne,std::string& id,
			int& lastpoker,int& pokernum,int* pokers);

//6玩家爆点失败
//参数：客户端事件消息，填充失败者id,失败者的最后一张牌，另一方的牌的数量，另一方的牌面
void LoseOutRange(_CNET_EVENT& ne,std::string& id,
			int& lastpoker,int& pokernum,int* pokers);

//7玩家比点数获胜
//参数：客户端事件消息，填充胜利者id,另一方的牌的数量，另一方的牌面
void WinBigger(_CNET_EVENT& ne,std::string& id,
			int& pokernum,int* pokers);

//8玩家比点数平局
//参数：客户端事件消息，另一方的牌的数量，另一方的牌面
void Draw(_CNET_EVENT& ne,int& pokernum,int* pokers);

//9游戏结束消息
//参数：客户端事件消息，填充准备者id,积分，胜，负，平,玩家状态，房间号，座位号
void UpdatePlayerData(_CNET_EVENT& ne,std::string& id,
					  int& score, int& win, int& lose, int& draw, 
					  int& playerstate, int&roomnum, int& sitenum);

//10玩家放弃本局失败
//参数：客户端事件消息，填充失败者id
void LoseGiveUp(_CNET_EVENT& ne,std::string& id);

//11玩家逃跑失败
//参数：客户端事件消息，填充逃跑者id
void LoseRunAway(_CNET_EVENT& ne,std::string& id);

//12玩家游戏中聊天
//参数：客户端事件消息，填充的发送者id，填充的发送内容
void TalkInGame(_CNET_EVENT& ne,std::string& id, std::string& message);

#endif