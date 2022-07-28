#include <windows.h>
#include "GameEngine.h"	
#include "2.h"
#include "1.h"


int __stdcall WinMain(HINSTANCE hInstance,//应用程序实例句柄
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	CGameEngine::GetGE()->Init(640,480);
	CGameEngine::GetGE()->LoadScene("开始场景",new C1);
	CGameEngine::GetGE()->LoadScene("游戏场景",new C2);
	CGameEngine::GetGE()->SetInitScene("开始场景");
	CGameEngine::GetGE()->Run();
	return 1;
}