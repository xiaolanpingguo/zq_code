#include "HelloWorldScene.h"
#include "AppDelegate.h"

HelloWorld::HelloWorld()
{}

HelloWorld::~HelloWorld()
{}

CCScene* HelloWorld::getScene()
{
	CCScene* scene = CCScene::create();
	scene->addChild(this);
	return scene;
}

void HelloWorld::onEnter()
{
	//调用父类的onEnter
	CCLayer::onEnter();

	//设置本层开启触屏
	setTouchEnabled(true);

	//设置本层为触屏消息的分发目标
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
		this, //设置为分发目标的层
		1, //分发优先级，优先级越到越先得到触屏消息
		true); //如果设置为真，那么不再往后面的层发送触屏消息，反之继续发送

	//开启本层的更新
	scheduleUpdate();
}

void HelloWorld::onExit()
{
	//调用父类的onEnter
	CCLayer::onExit();
}

bool HelloWorld::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	return true;
}

void HelloWorld::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	
}

void HelloWorld::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	
}

void HelloWorld::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{

}

void HelloWorld::draw()
{
	//下面的cocos2d基本绘制函数（底层调用的是OpenGL中的绘
	//制函数）只能在draw里面被调用，其它地方调用没有效果，
	//这些基本的绘制函数中，有一个当前颜色的概念，我们可以
	//通过相关的函数设置当前颜色，被设置的颜色将体现在那些
	//绘图函数的结果中，当前颜色默认是白色的

	ccColor4B c1 = {0x7f, 0x7f, 0x7f, 0xff};
	AppDelegate::DrawRect2(
		ccp(0, 0),
		ccp(AppDelegate::m_DebugSize.width, AppDelegate::m_DebugSize.height),
		c1);

	ccColor4B c2 = {0xff, 0x00, 0x00, 0xff};
	AppDelegate::DrawLine(
		ccp(0, 0),
		ccp(AppDelegate::m_DebugSize.width, AppDelegate::m_DebugSize.height),
		c2);

	ccColor4B c3 = {0xff, 0x00, 0xff, 0xff};
	AppDelegate::DrawRect1(
		ccp(100, 100),
		ccp(AppDelegate::m_DebugSize.width - 100, AppDelegate::m_DebugSize.height - 100),
		c3);
}

void HelloWorld::update(float dt)
{
	
}