#ifndef _SCENE_H_
#define _SCENE_H_
//CStartScene:开始场景
//CEndScene:结束场景
//CGameScene:游戏场景
//CSetScene:游戏设置场景

//CSceneManager:场景管理
//场景类

class CSceneManager;
class CScene
{
	CSceneManager* pCSceneManager;
public:
	virtual void Run();
	virtual void SetSceneManager(CSceneManager* pSceneManager);
	virtual CSceneManager* GetManager();

};

#endif