#include "SetScene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include <iostream>

CSetScene::CSetScene()
:
sel(0)
{
}
void CSetScene::Run()
{
	CGameScene* pGameScene = (CGameScene*)(GetManager()->GetCurScene(1));
	if(sel == 0)
	{
		std::cout<<" ∑µªÿ"<<std::endl;
		std::cout<<"->“Ù–ß";
		std::cout<<(pGameScene->ReturnBeep()?"on":"off")<<std::endl;
	}
	////


}