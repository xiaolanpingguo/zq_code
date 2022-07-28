#include "HelloWorldScene.h"
#include "AppDelegate.h"
//......
//精灵n：包含图像2

HelloWorld::HelloWorld()
{
	t1 = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("01.PNG");
	t2 = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("02.png");
	pos = CCPointZero;
}

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
	pos = pTouch->getLocationInView();
}

void HelloWorld::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{

}

//层自己也进行绘制
void HelloWorld::draw()
{
	ccColor4B c = {0xff, 0xff, 0xff, 0xff};
	AppDelegate::DrawRect2(
		ccp(0, 0),
		ccp(500, 500),
		c);

	t1->Draw(
		0, 0, 100, 100,
		0, 0, AppDelegate::m_DebugSize.width, AppDelegate::m_DebugSize.height);

	t2->Draw(
		25, 25, 50, 50,
		pos.x, pos.y, 200, 200);

	DrawString(
		100, 100,
		30, 50,
		3, 3,
		"abcdefghijklmn");
}

void HelloWorld::update(float dt)
{
	
}