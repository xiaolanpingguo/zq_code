#include "HelloWorldScene.h"
#include "AppDelegate.h"

//精灵的控制
//锚点是精灵中图形变换时候很重要的参考，在缩放
//和旋转的时候，锚点相当于是缩放、旋转的坐标原
//点，我们首先考虑没有变换的时候，绘制到屏幕上
//面的情况，然后在屏幕上面找到锚点（忽略锚点并
//不代表没有锚点），以锚点作为坐标原点进行图形
//变换，图形变换的顺序是先缩放setScale、setRotation
//旋转、平移setPosition
//在程序中如果要表现多个使用同一图像的画面，那
//么必须要使用多个精灵，每个精灵中都有图像（纹
//理）资源的一个指针，cocos2d-x专门使用图像缓冲
//类来管理所有用到的图像，情况如下：
//图像缓冲类：图像1、图像2、...、图像n
//精灵1：包含图像1
//精灵2：包含图像1
//精灵3：包含图像2
//......
//精灵n：包含图像2

HelloWorld::HelloWorld()
{
	s1 = CCSprite::create("01.PNG");
	//s1->ignoreAnchorPointForPosition(true);
	s1->setAnchorPoint(ccp(1.0, 0.0));
	this->addChild(s1);

	CCTexture2D* t2 = CCTextureCache::sharedTextureCache()->addImage("02.PNG");
	s1->setTexture(t2);

	//s1->setVisible(false);

	a = 0.0f;
	sf = 1.0f;
	fd = true;
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
	
}

void HelloWorld::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{

}

//层自己也进行绘制
void HelloWorld::draw()
{
	ccColor4B c = {0xff, 0xff, 0x00, 0xff};
	AppDelegate::DrawRect2(
		ccp(0, 0),
		ccp(500, 500),
		c);
}

void HelloWorld::update(float dt)
{
	a -= 1.0f;

	////缩放
	//if (fd)
	//{
	//	sf += 0.01f;
	//	if (sf > 3.0f)
	//		fd = false;
	//}
	//else
	//{
	//	sf -= 0.01f;
	//	if (sf < 0.333f)
	//		fd = true;
	//}
	//s1->setScale(sf);

	

	////旋转
	s1->setRotation(a);

	s1->setScaleX(1.0f);
	s1->setScaleY(2.0f);

	s1->setPosition(ccp(300, 300));
}