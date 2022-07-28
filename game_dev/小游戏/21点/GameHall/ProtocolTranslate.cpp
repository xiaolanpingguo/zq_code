#include "ProtocolTranslate.h"
#include "..\\GameProtocol\\Protocol.h"
#include "..\\GameProtocol\\LoginProtocol.h"
#include "..\\GameProtocol\\HallProtocol.h"
#include "..\\GameProtocol\\BlackJackProtocol.h"

//----------------------------------------------------------------------------------------------
//登陆相关
//----------------------------------------------------------------------------------------------
//----------------------------------
//服务器向客户端发送消息(C-S消息)
//----------------------------------
//1.注册账号
//参数：注册用账号，密码，Tcp客户端类
void Register(const char* id, const char* pw, CTcpClient& tc)
{
	CS_ZC cs_zc;
	strcpy_s(cs_zc.id, 32,id);
	strcpy_s(cs_zc.pw, 32,pw);
	tc.SendData(&cs_zc, sizeof(cs_zc));
}

//2.登陆账号
//参数：登陆用账号，密码，Tcp客户端类
void Login(const char* id, const char* pw, CTcpClient& tc)
{
	CS_DL cs_dl;
	strcpy_s(cs_dl.id, 32,id);
	strcpy_s(cs_dl.pw, 32,pw);
	tc.SendData(&cs_dl, sizeof(cs_dl));
}

//----------------------------------
//客户端接受服务器消息反馈(S-C消息)
//----------------------------------
//1.登陆成功
//参数：客户端事件消息，需要填充的当前在线玩家表
void LoginSuccess(_CNET_EVENT& ne,std::map<std::string,_PLAYER>& players)
{
	SC_DL_OK* dl_ok = (SC_DL_OK*)ne.data;
	char* p = (char*)(dl_ok + 1);
	for(int i = 0; i < dl_ok->num; ++i)
	{
		std::string id = p;
		p += strlen(p) + 1;

		std::string name = p;
		p += strlen(p) + 1;

		int face = *((int*)p);
		p += sizeof(int);

		int score = *((int*)p);
		p += sizeof(int);

		int win = *((int*)p);
		p += sizeof(int);

		int lose = *((int*)p);
		p += sizeof(int);

		int draw = *((int*)p);
		p += sizeof(int);

		int roomnum = *((int*)p);
		p += sizeof(int);

		int sitenum = *((int*)p);
		p += sizeof(int);

		int playerstate = *((int*)p);
		p += sizeof(int);

		_PLAYER player = {id,name,face,score,win,lose,draw,roomnum,sitenum,playerstate};
		players.insert(std::pair<std::string,_PLAYER>(id,player));
	}
}

//2.新玩家登陆成功
//参数：客户端事件消息，填充的玩家信息，当前客户端玩家的ID号
//返回true表示是玩家自己的信息
//返回false表示是其他玩家登入的信息
bool NewClientLogin(_CNET_EVENT& ne,_PLAYER& player,std::string clientid)
{
	SC_NEW_CLIENT* new_client = (SC_NEW_CLIENT*)ne.data;
	char* p = (char*)(new_client + 1);

	player.m_ID = p;
	p += strlen(p) + 1;

	player.m_Name = p;
	p += strlen(p) + 1;

	player.m_Face = *((int*)p);
	p += sizeof(int);

	player.m_Score = *((int*)p);
	p += sizeof(int);

	player.m_Win = *((int*)p);
	p += sizeof(int);

	player.m_Lose = *((int*)p);
	p += sizeof(int);

	player.m_Draw = *((int*)p);
	p += sizeof(int);

	player.m_RoomNum = *((int*)p);
	p += sizeof(int);

	player.m_SiteNum = *((int*)p);
	p += sizeof(int);

	player.m_PlayState = *((int*)p);
	p += sizeof(int);

	return strcmp(clientid.c_str(),player.m_ID.c_str()) == 0;
}

//----------------------------------------------------------------------------------------------
//大厅相关
//----------------------------------------------------------------------------------------------
//1.玩家修改成功
//参数：客户端事件消息，填充的名字，头像，当前客户端玩家的ID号
//返回true表示是玩家自己的信息
//返回false表示是其他玩家登入的信息
void ChangeDataSuccess(_CNET_EVENT& ne,std::string& name, int& face, std::string& clientid)
{
	SC_CHANGE_DATA* sc_cd = (SC_CHANGE_DATA*)ne.data;
	name = sc_cd->Name;
	face = sc_cd->facenum;
	clientid = sc_cd->ID;
}

//2.公共聊天
//参数：客户端事件消息，填充的发送者id，填充的发送内容
void PublicTalk(_CNET_EVENT& ne,std::string& id, std::string& message)
{
	SC_PUB_TALK* sc_pt = (SC_PUB_TALK*)ne.data;
	id = sc_pt->ID;
	message = sc_pt->Message;
}

//3.私人聊天
//参数：客户端事件消息，填充的发送者id，填充的发送内容
void PrivateTalk(_CNET_EVENT& ne,std::string& id, std::string& desid, std::string& message)
{
	SC_PRI_TALK* sc_pt = (SC_PRI_TALK*)ne.data;
	id = sc_pt->ID;
	desid = sc_pt->DESID;
	message = sc_pt->Message;

}

//4.玩家离线
//参数：客户端事件消息，填充的离线者id
void PlayerOffLine(_CNET_EVENT& ne,std::string& id)
{
	SC_PLAYER_OFFLINE* sc_po = (SC_PLAYER_OFFLINE*)ne.data;
	id = sc_po->ID;
}

//5.玩家进入房间成功
//参数：客户端事件消息，填充的进入房间者id, 旧房间号，旧座位号，新房间号，新座位号
void EnterRoomSuccess(_CNET_EVENT& ne,std::string& id,int& roomnew, int& sitenew)
{
	SC_ENTER_ROOM_SUCCESS* sc_ers = (SC_ENTER_ROOM_SUCCESS*)ne.data;
	id = sc_ers->ID;
	roomnew = sc_ers->RoomNumNew;
	sitenew = sc_ers->SiteNumNew;
}

//6.玩家准备成功
//参数：客户端事件消息，填充准备者id
void ReadSuccess(_CNET_EVENT& ne,std::string& id)
{
	SC_READ_SUCCESS* sc_rs = (SC_READ_SUCCESS*)ne.data;
	id = sc_rs->ID;
}

//7.玩家退出房间成功
//参数：客户端事件消息，填充的退出房间者id
void ExitRoomSuccess(_CNET_EVENT& ne,std::string& id)
{
	SC_EXIT_ROOM_SUCCESS* sc_ers = (SC_EXIT_ROOM_SUCCESS*)ne.data;
	id = sc_ers->ID;
}

//8.玩家取消准备成功
//参数：客户端事件消息，填充准备者id
void ReadyCancelSuccess(_CNET_EVENT& ne,std::string& id)
{
	SC_READY_CANCEL_SUCCESS* sc_rcs = (SC_READY_CANCEL_SUCCESS*)ne.data;
	id = sc_rcs->ID;
}

//----------------------------------------------------------------------------------------------
//游戏相关
//----------------------------------------------------------------------------------------------
//1.开始新游戏
//参数：客户端事件消息，填充准备者id
void NewGame(_CNET_EVENT& ne,std::string& id,int &num)
{
	SC_NEW_GAME* sc_ng = (SC_NEW_GAME*)ne.data;
	id = sc_ng->ID;
	num = sc_ng->firstpokernum;
}

//2.更新玩家数据
//参数：客户端事件消息，填充准备者id,积分，胜，负，平,玩家状态，房间号，座位号
void UpdatePlayerData(_CNET_EVENT& ne,std::string& id,
					  int& score, int& win, int& lose, int& draw, 
					  int& playerstate, int&roomnum, int& sitenum)
{
	SC_UPDATE_PLAYER_DATA* sc_upd = (SC_UPDATE_PLAYER_DATA*)ne.data;
	id = sc_upd->ID;
	score = sc_upd->score;
	win = sc_upd->win;
	lose = sc_upd->lose;
	draw = sc_upd->draw;
	playerstate = sc_upd->playerstate;
	roomnum = sc_upd->roomnum;
	sitenum = sc_upd->sitenum;
}

//3.玩家做出选择
//参数：客户端事件消息，填充对手id
void MakeChoice(_CNET_EVENT& ne,std::string& id)
{
	SC_MAKE_CHOICE* sc_mc = (SC_MAKE_CHOICE*)ne.data;
	id = sc_mc->ID;
}

//4.玩家获得新牌
//参数：客户端事件消息，填充牌编号
void GetNew(_CNET_EVENT& ne,int &num)
{
	SC_GET_NEW* sc_gn = (SC_GET_NEW*)ne.data;
	num = sc_gn->newpoker;
}

//5玩家获得21点胜利
//参数：客户端事件消息，填充胜利者id, 胜利者的最后一张牌，另一方的牌的数量，另一方的牌面
void Win_21(_CNET_EVENT& ne,std::string& id,
			int& lastpoker,int& pokernum,int* pokers)
{
	SC_WIN_21* sc_w21 = (SC_WIN_21*)ne.data;
	id = sc_w21->winID;
	lastpoker = sc_w21->lastpoker;
	pokernum = sc_w21->pokernum;
	for(int i = 0; i< pokernum; ++i)
		pokers[i] = sc_w21->pokers[i];
}

//6玩家爆点失败
//参数：客户端事件消息，填充失败者id,失败者的最后一张牌，另一方的牌的数量，另一方的牌面
void LoseOutRange(_CNET_EVENT& ne,std::string& id,
			int& lastpoker,int& pokernum,int* pokers)
{
	SC_LOSE_OUT_RANGE* sc_lor = (SC_LOSE_OUT_RANGE*)ne.data;
	id = sc_lor->loseID;
	lastpoker = sc_lor->lastpoker;
	pokernum = sc_lor->pokernum;
	for(int i = 0; i< pokernum; ++i)
		pokers[i] = sc_lor->pokers[i];
}

//7玩家比点数获胜
//参数：客户端事件消息，填充胜利者id,另一方的牌的数量，另一方的牌面
void WinBigger(_CNET_EVENT& ne,std::string& id,
			int& pokernum,int* pokers)
{
	SC_WIN_BIGGER* sc_wb = (SC_WIN_BIGGER*)ne.data;
	id = sc_wb->winID;
	pokernum = sc_wb->pokernum;
	for(int i = 0; i< pokernum; ++i)
		pokers[i] = sc_wb->pokers[i];
}

//8玩家比点数平局
//参数：客户端事件消息，另一方的牌的数量，另一方的牌面
void Draw(_CNET_EVENT& ne,int& pokernum,int* pokers)
{
	SC_DRAW* sc_d = (SC_DRAW*)ne.data;
	pokernum = sc_d->pokernum;
	for(int i = 0; i< pokernum; ++i)
		pokers[i] = sc_d->pokers[i];
}

//9游戏结束消息
//参数：客户端事件消息，填充修改状态者id
void GameEnd(_CNET_EVENT& ne,std::string& id, int& state)
{
	SC_GAME_END* sc_ge = (SC_GAME_END*)ne.data;
	id = sc_ge->ID;
	state = sc_ge->state;
}

//10玩家放弃本局失败
//参数：客户端事件消息，填充失败者id
void LoseGiveUp(_CNET_EVENT& ne,std::string& id)
{
	SC_LOSE_GIVEUP* sc_lg = (SC_LOSE_GIVEUP*)ne.data;
	id = sc_lg->loseID;
}

//11玩家逃跑失败
//参数：客户端事件消息，填充逃跑者id
void LoseRunAway(_CNET_EVENT& ne,std::string& id)
{
	SC_LOSE_RUN_AWAY* sc_lr = (SC_LOSE_RUN_AWAY*)ne.data;
	id = sc_lr->loseID;
}

//12玩家游戏中聊天
//参数：客户端事件消息，填充的发送者id，填充的发送内容
void TalkInGame(_CNET_EVENT& ne,std::string& id, std::string& message)
{
	SC_TALK_IN_GAME* sc_tig = (SC_TALK_IN_GAME*)ne.data;
	id = sc_tig->ID;
	message = sc_tig->msg;
}