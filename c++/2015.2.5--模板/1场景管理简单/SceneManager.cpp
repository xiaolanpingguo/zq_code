#include "SceneManager.h"
#include "Scene.h"

CSceneManager::CSceneManager()
:
m_pScene(new CScene*[8]),
m_iSceneNum(0),
m_iSceneCur(-1),
m_bPlay(true)
{}
CSceneManager::~CSceneManager()
{
	if(m_pScene)
		delete []m_pScene;
}
//添加场景-添加场景父类的指针
bool CSceneManager::AddScene(CScene* pScene)
{
	if(m_iSceneNum == 8)
		return false;
	m_pScene[m_iSceneNum++] = pScene;
	return true;
}
//设置当前场景
bool CSceneManager::SetCurScene(int CurScene)
{
	if(CurScene < 0||CurScene >= m_iSceneNum)
		return false;
	m_iSceneCur = CurScene;
	return true;
}
//得到当前场景
CScene* CSceneManager::GetCurScene(int Scene)
{
	if(Scene < 0||Scene >= m_iSceneNum)
		return 0;
	return m_pScene[Scene];
}
//游戏循环的标志
bool CSceneManager::Play()
{
	return m_bPlay;
}
//退出游戏
void CSceneManager::Exit()
{
	m_bPlay = false;
}
//游戏运行
void CSceneManager::GameRun()
{
	while(m_bPlay)
	{
		m_pScene[m_iSceneCur]->Run();
	}
}
