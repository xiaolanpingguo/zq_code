#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "AppDelegate.h"
#include "cocos2d.h"
#include <string>
#include <vector>

using namespace cocos2d;

class CUI;

class CGameLayer : public CCLayer
{
private:

	//进入、退出场景相关
	virtual void onEnter();
    virtual void onExit();
	bool m_Logic; //游戏逻辑执行标志
	virtual void onEnterTransitionDidFinish();

	//输入相关
	CCPoint m_Touches[32];
	int m_TouchesNum;
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent);
    virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent);
    virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* Event);
    virtual void ccTouchesCancelled(CCSet* pTouches, CCEvent* pEvent);

	//输出相关
	int m_BorderColor;
	virtual void draw();

	//逻辑相关
	virtual void update(float dt);

public:

	//构造析构
	CGameLayer();
	virtual ~CGameLayer();

	//流程
	virtual void Enter();
	virtual void InputDown(CCPoint* p);
	virtual void InputMove(CCPoint* p, int n);
	virtual void InputUp(CCPoint* p);
	virtual void Output();
	virtual void Logic(float dt);
	virtual void Exit();
	void Quit();

	//绘制相关
	void SetBorderColor(int BorderColor);
	void DrawLine(const CCPoint& p1, const CCPoint& p2, int c);
	void DrawRect1(const CCPoint& p1, const CCPoint& p2, int c);
	void DrawRect2(const CCPoint& p1, const CCPoint& p2, int c);
	void DrawImage1(
		CCTexture2D* t,
		int sx, int sy, int sw, int sh,
		int dx, int dy, int dw, int dh);
	std::vector<CCSprite*> m_Sprites;
	int m_CurSpriteIndex;
	void DrawImage2(
		CCTexture2D* t,
		float angle,
		int dx, int dy, int dw, int dh);
	void DrawString(
		int x, int y,
		int w, int h,
		int xn, int yn,
		const char* str);

	//文件相关
	struct _FILE_DATA
	{
		char* fd; //文件的数据首地址
		int fs; //文件的总大小
	};
	_FILE_DATA GetResourceFileData(const char* fn);
	char m_RWDirectory[256];
	const char* GetRWDirectory();

	//音频相关
	void PlayMusic(const char* fn);
	void StopMusic();
	float GetMusicVolume();
	void SetMusicVolume(float v);
	void PlayEffect(const char* fn);
	float GetEffectVolume();
	void SetEffectVolume(float v);

	//UI相关
	std::vector<CUI*> m_UI;
	bool LoadUI(int id, CUI* pUI);
	bool ReleaseUI(int id);
	CUI* GetUI(int id);
	virtual void OnUIMessage(int id, int msg);
};

#endif