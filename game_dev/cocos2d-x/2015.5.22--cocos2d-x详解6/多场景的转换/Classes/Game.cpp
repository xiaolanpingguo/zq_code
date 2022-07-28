#include "Game.h"

CGame::CGame()
{
	t = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("02.png");
}

CGame::~CGame()
{}

void CGame::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	scheduleUpdate();
}

void CGame::onExit()
{
	CCLayer::onExit();
}

void CGame::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
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
		
	}
}

void CGame::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
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
		
	}
}

void CGame::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
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
		if (touch[0].x >= 100 && touch[0].x < 300 && touch[0].y >= 100 && touch[0].y < 300)
			AppDelegate::SetCurScene(0);
	}
}

void CGame::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	
}

void CGame::draw()
{
	t->Draw(
		0, 0, 100, 100,
		100, 100, 200, 200);
}

void CGame::update(float dt)
{

}
