#include <iostream>
#include "SceneManager.h"
#include "Start.h"
#include "Game.h"

void main()
{
	CSceneManager sm;
	CSceneManager::LoadScene(new CStart);
	CSceneManager::LoadScene(new CGame);
	CSceneManager::SetCurScene(0);
	sm.Run();
	system("pause");
}