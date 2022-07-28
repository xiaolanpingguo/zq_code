#include "SceneChange.h"	

CSceneChange::CSceneChange(int AllFrame)
:
m_iAllFrame(AllFrame)
{}
void CSceneChange::SetBegin()
{
	m_iCurFrame = 0;
}
void CSceneChange::Render(int CurFrame){}