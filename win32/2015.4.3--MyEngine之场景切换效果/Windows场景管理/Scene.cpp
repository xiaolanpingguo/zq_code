#include "GameEngine.h"
#include "Scene.h"

CScene::CScene(){m_EnterChange[0] = 0; m_QuitChange[0] = 0;}
CScene::~CScene(){}
void CScene::Init(){}
void CScene::Enter(){}
void CScene::OutputRun(){}
void CScene::LogicInputRun(){}
void CScene::Quit(){}
void CScene::End(){}

void CScene::SetEnterChange(const char* id)
{
	if (id)
		m_EnterChange = id;
	else
		m_EnterChange = "";
}

void CScene::SetQuitChange(const char* id)
{
	if (id)
		m_QuitChange = id;
	else
		m_QuitChange = "";
}