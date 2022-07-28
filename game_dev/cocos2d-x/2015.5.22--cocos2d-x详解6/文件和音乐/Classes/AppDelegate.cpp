#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;

CCSize AppDelegate::m_DebugSize;
CCSize AppDelegate::m_ReleaseSize;
float AppDelegate::m_Scale;
float AppDelegate::m_OffsetX;

AppDelegate::AppDelegate()
{}

AppDelegate::~AppDelegate()
{
	//释放所有场景
	//即delete layer[i];

    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(false);
    pDirector->setAnimationInterval(1.0 / 30.0);

	//得到尺寸
	m_DebugSize.setSize(_DEBUG_W, _DEBUG_H);
	m_ReleaseSize = CCEGLView::sharedOpenGLView()->getFrameSize();

	//得到缩放比例
	m_Scale = m_ReleaseSize.height / m_DebugSize.height;

	//得到X方向偏移量
	m_OffsetX = (m_ReleaseSize.width - m_DebugSize.width * m_Scale) / 2.0f;

	//创建层
	HelloWorld* pHelloWorld = new HelloWorld();

	//导演运行包含本层的场景
	pDirector->runWithScene(pHelloWorld->getScene());

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::DrawLine(const CCPoint& p1, const CCPoint& p2, ccColor4B c)
{
	float p1y = m_DebugSize.height - p1.y;
	float p2y = m_DebugSize.height - p2.y;

	CCPoint p3 = ccp(p1.x * m_Scale + m_OffsetX, p1y * m_Scale);
	CCPoint p4 = ccp(p2.x * m_Scale + m_OffsetX, p2y * m_Scale);
	ccDrawColor4B(c.r, c.g, c.b, c.a);
	ccDrawLine(p3, p4);
	ccDrawColor4B(0xff, 0xff, 0xff, 0xff);
}

void AppDelegate::DrawRect1(const CCPoint& p1, const CCPoint& p2, ccColor4B c)
{
	float p1y = m_DebugSize.height - p1.y;
	float p2y = m_DebugSize.height - p2.y;

	CCPoint p3 = ccp(p1.x * m_Scale + m_OffsetX, p1y * m_Scale);
	CCPoint p4 = ccp(p2.x * m_Scale + m_OffsetX, p2y * m_Scale);
	ccDrawColor4B(c.r, c.g, c.b, c.a);
	ccDrawRect(p3, p4);
	ccDrawColor4B(0xff, 0xff, 0xff, 0xff);
}

void AppDelegate::DrawRect2(const CCPoint& p1, const CCPoint& p2, ccColor4B c)
{
	float p1y = m_DebugSize.height - p1.y;
	float p2y = m_DebugSize.height - p2.y;
	CCPoint p3 = ccp(p1.x * m_Scale + m_OffsetX, p1y * m_Scale);
	CCPoint p4 = ccp(p2.x * m_Scale + m_OffsetX, p2y * m_Scale);
	ccColor4F cf = {c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, c.a / 255.0f};
	ccDrawSolidRect(p3, p4, cf);
}