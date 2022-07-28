#include "BlackJack.h"

CBlackJack::CBlackJack(_ROOM* r)
:
m_Room(r),
m_iRestPokersNum(_POKERS_MAX),
m_iPlayer1CurPokersNum(0),
m_iPlayer1CurPoint(0),
m_bPlayer1Stop(false),
m_iPlayer2CurPokersNum(0),
m_iPlayer2CurPoint(0),
m_bPlayer2Stop(false),
m_bIsPlayer1Speak(true)
{
	for(int i = 0; i < 52; i++)
		m_GamePokers[i] = i;
}

int CBlackJack::GetNewPoker()
{
	int cur = rand() % m_iRestPokersNum;

	int p = m_GamePokers[cur];

	m_GamePokers[cur] = m_GamePokers[--m_iRestPokersNum];

	return p;
}