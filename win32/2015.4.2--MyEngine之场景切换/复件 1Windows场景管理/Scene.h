#ifndef _SCENE_H_
#define _SCENE_H_

class CScene
{
public:
	virtual ~CScene();
	virtual void Init();
	virtual void Enter();
	virtual void Run();
	virtual void Quit();
	virtual void End();
};

#endif