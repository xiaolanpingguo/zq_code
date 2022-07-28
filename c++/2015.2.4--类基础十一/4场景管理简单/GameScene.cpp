#include "GameScene.h"

CGameScene::CGameScene()
:
m_ix(0),
m_iy(0),
m_bBeep(true)
{

}
void CGameScene::Run()
{
	//
}

bool CGameScene::ReturnBeep()
{
	return m_bBeep;
}