#include "SC2.h"
#include "GameEngine.h"	


CSC2::CSC2()
:
CSceneChange(32)
{
	
}
void CSC2::Render(int CurFrame)
{
	int w = CGameEngine::GetGE()->GetW();
	int h = CGameEngine::GetGE()->GetH();

	CGameEngine::GetGE()->GetGO()->DrawRectangle2(0,0,
		(w / 32) * CurFrame,
		h,RGB(0,0,0),RGB(0,0,0));
}