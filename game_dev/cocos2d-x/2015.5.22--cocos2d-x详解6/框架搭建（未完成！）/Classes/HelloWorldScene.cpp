#include "HelloWorldScene.h"
#include "AppDelegate.h"
//......
//精灵n：包含图像2

HelloWorld::HelloWorld()
{
	t = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("01.PNG");
}

HelloWorld::~HelloWorld()
{}

void HelloWorld::onEnter()
{
	//调用父类的onEnter
	CCLayer::onEnter();

	//设置本层开启触屏
	setTouchEnabled(true);

	//开启本层的更新
	scheduleUpdate();
}

void HelloWorld::onExit()
{
	//调用父类的onEnter
	CCLayer::onExit();
}

void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent *pEvent)
{
	began.clear();
	touch_num = 0;
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCPoint point = ((CCTouch*)(*it))->getLocationInView();
		if (point.x > AppDelegate::m_OffsetX && point.x < (AppDelegate::m_ReleaseSize.width - AppDelegate::m_OffsetX))
		{
			point.x -= AppDelegate::m_OffsetX;
			point.x /= AppDelegate::m_Scale;
			point.y /= AppDelegate::m_Scale;
			touch[touch_num++] = point;
		}
	}
	if (touch_num > 0)
	{
		for (int i = 0; i < touch_num; ++i)
			began.push_back(touch[i]);
	}
}

void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	touch_num = 0;
	move.clear();
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCPoint point = ((CCTouch*)(*it))->getLocationInView();
		if (point.x > AppDelegate::m_OffsetX && point.x < (AppDelegate::m_ReleaseSize.width - AppDelegate::m_OffsetX))
		{
			point.x -= AppDelegate::m_OffsetX;
			point.x /= AppDelegate::m_Scale;
			point.y /= AppDelegate::m_Scale;
			touch[touch_num++] = point;
		}
	}
	if (touch_num > 0)
	{
		for (int i = 0; i < touch_num; ++i)
			move.push_back(touch[i]);
	}
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	touch_num = 0;
	end.clear();
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCPoint point = ((CCTouch*)(*it))->getLocationInView();
		if (point.x > AppDelegate::m_OffsetX && point.x < (AppDelegate::m_ReleaseSize.width - AppDelegate::m_OffsetX))
		{
			point.x -= AppDelegate::m_OffsetX;
			point.x /= AppDelegate::m_Scale;
			point.y /= AppDelegate::m_Scale;
			touch[touch_num++] = point;
		}
	}
	if (touch_num > 0)
	{
		for (int i = 0; i < touch_num; ++i)
			end.push_back(touch[i]);

		if (touch[0].x >= 0 && touch[0].x < 100 && touch[0].y >= 0 && touch[0].y < 100)
			AppDelegate::SetCurLayer(1);
	}
}

void HelloWorld::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{

}

//层自己也进行绘制
void HelloWorld::draw()
{
	ccColor4B c = {0xff, 0xff, 0xff, 0xff};
	//AppDelegate::DrawRect2(
	//	ccp(0, 0),
	//	ccp(AppDelegate::m_DebugSize.width, AppDelegate::m_DebugSize.height),
	//	c);

	//打印在手机屏幕上
	char buf[256];
	for (int i = 0; i < began.size(); ++i)
	{
		sprintf(buf, "(%d,%d)", (int)began[i].x, (int)began[i].y);
		DrawString(
			i * 200, 0,
			20, 40,
			10, 1,
			buf);
	}
	for (int i = 0; i < move.size(); ++i)
	{
		sprintf(buf, "(%d,%d)", (int)move[i].x, (int)move[i].y);
		DrawString(
			i * 200, 50,
			20, 40,
			10, 1,
			buf);
	}
	for (int i = 0; i < end.size(); ++i)
	{
		sprintf(buf, "(%d,%d)", (int)end[i].x, (int)end[i].y);
		DrawString(
			i * 200, 100,
			20, 40,
			10, 1,
			buf);
	}

	t->Draw(
		0, 0, 100, 100,
		0, 0, 100, 100);
}

void HelloWorld::update(float dt)
{
	
}