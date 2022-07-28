#ifndef _BLACK_JACK_H_
#define _BLACK_JACK_H_

#include "DataType.h"

#define _POKERS_MAX        52
#define _PLAYER_MAX_POKERS  21

class CBlackJack
{
public:
	//本局游戏所在房间号
	_ROOM* m_Room;
	//52张牌
	int m_GamePokers[_POKERS_MAX];
	//剩下牌数量
	int m_iRestPokersNum;

	//玩家1的牌，最多21张
	int Player1Pokers[_PLAYER_MAX_POKERS];
	//当前玩家1有的牌数量
	int m_iPlayer1CurPokersNum;
	//当前牌总点数
	int m_iPlayer1CurPoint;
	//是否停止要牌
	bool m_bPlayer1Stop;

	//玩家2的牌，最多21张
	int Player2Pokers[_PLAYER_MAX_POKERS];
	//当前玩家2有的牌数量
	int m_iPlayer2CurPokersNum;
	//当前牌总点数
	int m_iPlayer2CurPoint;
	//是否停止要牌
	bool m_bPlayer2Stop;

	//当前进行操作的玩家
	bool m_bIsPlayer1Speak;

	//构造
	CBlackJack(_ROOM* r);
	//获取新牌
	int GetNewPoker();
};

#endif