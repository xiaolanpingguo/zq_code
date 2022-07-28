#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

class CScene;

class CSceneManager
{
	static CScene* m_Scene[8];//场景父类指针数组
	static int m_SceneNum;//当前已经有的场景数量
	static int m_CurScene;//当前场景编号
	static bool m_Play;//是否开始游戏
public:
	//加载场景
	static bool LoadScene(CScene* pScene);

	//设置当前场景
	static bool SetCurScene(int index);

	//退出游戏
	static void Exit();

	//运行
	void Run();
};

#endif