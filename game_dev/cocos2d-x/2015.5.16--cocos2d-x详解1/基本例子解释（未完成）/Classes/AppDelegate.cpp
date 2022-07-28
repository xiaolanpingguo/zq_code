#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;

AppDelegate::AppDelegate()
{}

AppDelegate::~AppDelegate()
{
	//结束简单音频引擎的所有工作
	SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	//得到当前导演类对象
	CCDirector* pDirector = CCDirector::sharedDirector();

	//设置OpenGL类对象用于绘图
	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	//设置显示帧率
	pDirector->setDisplayStats(true);

	//设置游戏帧率
	pDirector->setAnimationInterval(1.0 / 30);

	//HelloWorld创建了一个场景对象，并且将自己
	//装入这个场景对象并返回，注意HelloWorld本
	//身并不是场景，而是层，层里面可以有输入、
	//输出、逻辑，类似我们自己的引擎中的场景，
	//但是cocos2d-x的导演不能直接运行一个层，它
	//只能直接运行一个场景，所以我们要运行一个
	//层就必须将一个层装入到一个场景中再用导演
	//来运行这个场景，间接地运行这个层了
	CCScene* pScene = HelloWorld::scene();
	
	//设置初始运行的场景
	pDirector->runWithScene(pScene);

	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	//停止整个游戏的绘制
	CCDirector::sharedDirector()->stopAnimation();

	//停止整个游戏的背景音乐播放
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
	//开始整个游戏的绘制
	CCDirector::sharedDirector()->startAnimation();

	//恢复整个游戏的背景音乐播放
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}