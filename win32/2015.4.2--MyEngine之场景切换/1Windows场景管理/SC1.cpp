#include "SC1.h"
#include "GameEngine.h"	


CSC1::CSC1()
:
CSceneChange(32)
{
	
}
void CSC1::Render(int CurFrame)
{
	int w = CGameEngine::GetGE()->GetW();
	int h = CGameEngine::GetGE()->GetH();

	CGameEngine::GetGE()->GetGO()->DrawRectangle2(0,0,
		w - (w / 32) * CurFrame,
		h,RGB(0,0,0),RGB(0,0,0));
}