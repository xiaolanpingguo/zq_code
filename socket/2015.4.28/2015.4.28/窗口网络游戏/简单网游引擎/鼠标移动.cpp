#include <iostream>
#include "GameEngine.h"
#include "Begin.h"
#include "Game.h"

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	CGameEngine::GetGE()->Init(640, 480, 33);

	CGameEngine::GetGE()->LoadScene("开始场景", new CBegin);
	CGameEngine::GetGE()->LoadScene("游戏场景", new CGame);
	CGameEngine::GetGE()->SetFirstScene("开始场景");
	CGameEngine::GetGE()->Run();

	return 1;
}