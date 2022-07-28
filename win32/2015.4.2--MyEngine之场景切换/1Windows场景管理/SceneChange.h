#ifndef _SCENECHANGE_H_
#define _SCENECHANGE_H_

class CSceneChange
{
	friend class CGameEngine;
	int m_iAllFrame;//总帧数
	int m_iCurFrame;//当前帧数
public:
	CSceneChange(int AllFrame);
	void SetBegin();
	virtual void Render(int CurFrame);
};

#endif