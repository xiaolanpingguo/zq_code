#include "SceneManager.h"
#include "Scene.h"
#include <windows.h>

CScene* CSceneManager::m_Scene[8];//场景父类指针数组
int CSceneManager::m_SceneNum = 0;//场景数量
int CSceneManager::m_CurScene = -1;//当前场景编号
bool CSceneManager::m_Play = true;//是否开始游戏
//加载场景
bool CSceneManager::LoadScene(CScene* pScene)
{
	if(m_SceneNum == 8)
		return false;
	m_Scene[m_SceneNum ++] = pScene;
	return true;
}
//设置当前场景
bool CSceneManager::SetCurScene(int index)
{
	if(index < 0 || index >= m_SceneNum)
		return false;
	m_CurScene = index;
	return true;
}

//退出游戏
void CSceneManager::Exit()
{
	m_Play = false;
}

//运行
void CSceneManager::Run()
{
	while(m_Play)
	{
		m_Scene[m_CurScene]->Run();
		Sleep(33);
	}
}