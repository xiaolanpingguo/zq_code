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
	//设置为当前层的子节点
	s1 = CCSprite::create("01.PNG");
	addChild(s1);

	//加载纹理
	t1 = CCTextureCache::sharedTextureCache()->addImage("02.PNG");

	//s1->setTexture(t1);
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

	CCSize s(1.0f, 1.0f);
	DrawTexture(
		t1,
		45.0f,
		s,
		ccp(200, 200));

	CCSize s2(2.0f, 2.0f);
	DrawTexture(
		t1,
		90.0f,
		s2,
		ccp(400, 400));
}

void HelloWorld::update(float dt)
{
	
}

void HelloWorld::DrawTexture(CCTexture2D* t,
							 float angle,
							 CCSize scale,
							 CCPoint position)
{
	//为已经准备好的精灵设置纹理
	s1->setTexture(t);

	//设置角度
	s1->setRotation(angle);

	//设置缩放量
	s1->setScaleX(scale.width * AppDelegate::m_Scale);
	s1->setScaleY(scale.height * AppDelegate::m_Scale);

	//设置位置
	position.x *= AppDelegate::m_Scale;
	position.x += AppDelegate::m_OffsetX;
	position.y *= AppDelegate::m_Scale;
	position.y = AppDelegate::m_ReleaseSize.height - position.y;
	s1->setPosition(position);
}