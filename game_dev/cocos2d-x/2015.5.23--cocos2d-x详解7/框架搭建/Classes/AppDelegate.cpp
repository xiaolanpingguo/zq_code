#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "Start.h"
#include "Game.h"

using namespace CocosDenshion;
using namespace cocos2d;

CCSize AppDelegate::m_DebugSize;
CCSize AppDelegate::m_ReleaseSize;
float AppDelegate::m_Scale;
float AppDelegate::m_OffsetX;
CCLayer* AppDelegate::m_Layer[32];
int AppDelegate::m_LayerNum;

AppDelegate::AppDelegate()
{}

AppDelegate::~AppDelegate()
{
	//释放所有的层
	for (int i = 0; i < m_LayerNum; ++i)
		delete m_Layer[i];

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

	//创建所有层并设置初始的层
	AddLayer(new CStart);
	AddLayer(new CGame);
	SetInitLayer(0);

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

bool AppDelegate::AddLayer(CCLayer* layer)
{
	if (m_LayerNum == _MAX_LAYER)
		return false;
	m_Layer[m_LayerNum++] = layer;
	return true;
}

bool AppDelegate::SetInitLayer(int index)
{
	if (index < 0 || index >= m_LayerNum)
		return false;
	CCScene* scene = CCScene::create();
	scene->addChild(m_Layer[index]);
	CCDirector::sharedDirector()->runWithScene(CCTransitionFade::create(1.0f, scene));
}

bool AppDelegate::SetCurLayer(int index)
{
	if (index < 0 || index >= m_LayerNum)
		return false;
	CCScene* scene = CCScene::create();
	scene->addChild(m_Layer[index]);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, scene));
}