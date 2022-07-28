#ifndef _PROTOCOL_FILTER_H_
#define _PROTOCOL_FILTER_H_

//服务器端的协议筛选器
#include "..\\GameProtocol\\Protocol.h"
#include "..\\GameProtocol\\LoginProtocol.h"
#include "..\\GameProtocol\\HallProtocol.h"
#include "..\\GameProtocol\\BlackJackProtocol.h"
#include "TcpServer.h"
#include "DataType.h"
#include <map>
#include "BlackJack.h"
/*
//--------------游戏协议--------------
//--------1-100为登陆注册用的协议---------
//--------101-200为大厅所用协议-------
//--------201-300为游戏21点所用协议-------
*/

//协议处理派发
void ProtocolDispatcher(_SNET_EVENT& ne);

//登录模块协议解析
void LoginProtoclTranslate(int type, _SNET_EVENT& ne);
//登陆
void Login(_SNET_EVENT& ne);
//注册
void Register(_SNET_EVENT& ne);


//大厅模块协议解析
void HallProtoclTranslate(int type, _SNET_EVENT& ne);
//更新玩家数据
void ChangePlayerData(_SNET_EVENT& ne);
//大厅聊天
void PublicTalk(_SNET_EVENT& ne);
//私聊
void PrivateTalk(_SNET_EVENT& ne);
//进入房间
void EnterRoom(_SNET_EVENT& ne);
//准备
void Read(_SNET_EVENT& ne);
//退出房间
void ExitRoom(_SNET_EVENT& ne);
//取消准备
void ReadyCancel(_SNET_EVENT& ne);

//21点游戏模块协议解析
void BlackJackProtocolTranslate(int type, _SNET_EVENT& ne);
//新游戏
void NewGame(int roomnum);
//继续拿牌
void ChoiceContinue(_SNET_EVENT& ne);
//停止拿牌
void ChoiceStop(_SNET_EVENT& ne);
//放弃本局游戏
void ChoiceGiveUp(_SNET_EVENT& ne);
//游戏中聊天
void TalkInGame(_SNET_EVENT& ne);
//逃跑
void RunAway(_SNET_EVENT& ne);
//游戏结束
void GameEnd(_PLAYER* p1, _PLAYER* p2,std::map<int,CBlackJack>::iterator& game);
#endif