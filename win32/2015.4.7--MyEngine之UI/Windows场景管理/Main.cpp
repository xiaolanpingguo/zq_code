#include <windows.h>
#include "GameEngine.h"
#include "1.h"
#include "2.h"
#include "Enter1.h"
#include "Quit1.h"
#include "Enter2.h"
#include "Quit2.h"
#include "Enter3.h"
#include "Quit3.h"
#include "Enter4.h"
#include "Quit4.h"

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	CGameEngine::GetGE()->Init(640, 480);

	CGameEngine::GetGE()->LoadSceneChange("入1", new CEnter1);
	CGameEngine::GetGE()->LoadSceneChange("出1", new CQuit1);
	CGameEngine::GetGE()->LoadSceneChange("入2", new CEnter2);
	CGameEngine::GetGE()->LoadSceneChange("出2", new CQuit2);
	CGameEngine::GetGE()->LoadSceneChange("入3", new CEnter3);
	CGameEngine::GetGE()->LoadSceneChange("出3", new CQuit3);
	CGameEngine::GetGE()->LoadSceneChange("入4", new CEnter4);
	CGameEngine::GetGE()->LoadSceneChange("出4", new CQuit4);

	CGameEngine::GetGE()->LoadScene("开始场景", new C1);
	CGameEngine::GetGE()->LoadScene("游戏场景", new C2);
	CGameEngine::GetGE()->SetInitScene("开始场景");

	CGameEngine::GetGE()->Run();

	return 1;
}