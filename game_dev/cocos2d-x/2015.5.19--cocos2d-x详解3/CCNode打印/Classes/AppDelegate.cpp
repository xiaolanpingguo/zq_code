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

void PrintCCNodeTree(CCNode* p, int level)
{
	if (!p)
		return;

	//打印当前层的层数
	char buf[256] = {};
	for (int i = 0; i < level; ++i)
		strcat_s(buf, 256, "◆");
	OutputDebugStringA(buf);

	CCPoint a = CCPointZero;
	if (!p->isIgnoreAnchorPointForPosition())
		a = p->getAnchorPoint();
	
	//打印当前节点数据
	sprintf_s(
		buf,
		256,
		"尺寸(%d,%d)位置(%d,%d)锚点(%f,%f)\n",
		(int)p->getContentSize().width,
		(int)p->getContentSize().height,
		(int)p->getPosition().x,
		(int)p->getPosition().y,
		a.x,
		a.y);
	OutputDebugStringA(buf);

	//递归所有子节点
	//每个节点在存储其子节点的时候，是用的一个CCArray来存储
	//的，而CCArray存储的数据类型是CCObject，而CCObject类是
	//几乎所有cocos2d类的根类，所以CCNode也可以存储在CCArray
	//之中，只不过真正要访问CCNode的时候必须强转
	CCArray* arr = p->getChildren();
	for (int i = 0; i < (int)p->getChildrenCount(); ++i)
	{
		CCNode* q = (CCNode*)arr->objectAtIndex(i);
		PrintCCNodeTree(q, level + 1);
	}
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

	//打印
	PrintCCNodeTree(pScene, 0);
	//尺寸(480,320)位置(0,0)锚点(0,0)
	//◆尺寸(480,320)位置(0,0)锚点(0,0)
	//◆◆尺寸(480,320)位置(0,0)锚点(0,0)
	//◆◆◆尺寸(100,100)位置(100,50)锚点(0.5,0)
	//◆◆◆◆尺寸(40,80)位置(50,100)锚点(0.5,0.5)
	//◆◆◆◆尺寸(50,50)位置(100,200)锚点(0,0.5)

	//尺寸(480,320)位置(0,0)锚点(0.000000,0.000000)
	//◆尺寸(480,320)位置(0,0)锚点(0.000000,0.000000)
	//◆◆尺寸(480,320)位置(0,0)锚点(0.000000,0.000000)
	//◆◆◆尺寸(100,100)位置(100,50)锚点(0.500000,0.000000)
	//◆◆◆◆尺寸(40,80)位置(50,100)锚点(0.500000,0.500000)
	//◆◆◆◆尺寸(50,50)位置(100,200)锚点(0.000000,0.500000)
	
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