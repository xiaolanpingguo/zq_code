#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

class CScene;

//场景管理类
class CSceneManager
{
	CScene** m_pScene;//存储场景指针
	int m_iSceneNum;//场景数量
	int m_iSceneCur;//当前场景
	bool m_bPlay;//游戏循环标志
public:
	CSceneManager();
	~CSceneManager();
	//添加场景
	bool AddScene(CScene* pScene);
	//设置当前场景
	bool SetCurScene(int CurScene);
	//得到当前场景
	CScene* GetCurScene(int Scene);
	//游戏循环的标志
	bool Play();
	//退出游戏
	void Exit();
	//游戏运行
	void GameRun();
};

#endif