#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class CGame : public cocos2d::CCLayer
{
public:

	//初始化
	CGame();

	//收尾
	~CGame();

	//当程序从其它场景转换到本层所属的场景时被调用
	virtual void onEnter();

	//当程序从本层所属的场景转换到其它场景时被调用
    virtual void onExit();

	//当前切换动画执行完毕的时候会调用本函数，在本
	//函数没有被调用之前，不能再用导演去切换场景
	virtual void onEnterTransitionDidFinish()
	{}
    
	//多点触碰
	CCPoint touch[32];
	int touch_num;
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

	virtual void draw();

	virtual void update(float dt);

	//纹理
	MyTexture* t;

	//文字绘制
	void DrawString(
		int x, int y, //文字绘制区域的左上角x、y坐标
		int w, int h, //每个文字的宽、高
		int xn, int yn,  //文字绘制区域的x、y方向的文字数量
		const char* str)
	{
		//初次加载稍慢
		MyTexture* ascii = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("ASCII.PNG");

		//循环绘制文字
		for (int i = 0; str[i] && i < xn * yn; ++i)
		{
			//得到源文字矩形
			int sx = (str[i] % 32) * 25;
			int sy = (str[i] / 32) * 48;

			//得到目标文字矩形
			int dx = (i % xn) * w;
			int dy = (i / xn) * h;

			ascii->Draw(
				sx, sy, 25, 48,
				dx + x, dy + y, w, h);
		}
	}
};

#endif