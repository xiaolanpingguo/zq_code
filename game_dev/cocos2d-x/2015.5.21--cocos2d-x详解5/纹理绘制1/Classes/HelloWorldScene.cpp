#include "HelloWorldScene.h"
#include "AppDelegate.h"
//......
//精灵n：包含图像2

HelloWorld::HelloWorld()
{
	t1 = CCTextureCache::sharedTextureCache()->addImage("01.PNG");
	t2 = CCTextureCache::sharedTextureCache()->addImage("02.PNG");
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
	ccColor4B c = {0xff, 0xff, 0xff, 0xff};
	AppDelegate::DrawRect2(
		ccp(0, 0),
		ccp(500, 500),
		c);

	//如果要在绘制纹理的时候进行旋转处理，那么就必须
	//在绘制的时候将纹理和一个精灵结合到一起并设置精
	//灵的旋转角度，依次进行绘制，如果不进行旋转那么
	//直接进行纹理绘制即可

	//直接在指定位置绘制纹理
	t1->drawAtPoint(ccp(200, 200));

	//CCRect是cocos2d中用于代表一个屏幕上的矩形的类
	CCRect r;

	//origin表示矩形的左下角点
	r.origin.x = 100;
	r.origin.y = 100;

	//size表示矩形的宽高
	r.size.width = 300;
	r.size.height = 150;

	//直接在目标举行绘制纹理（拉伸）
	t2->drawInRect(r);
}

void HelloWorld::update(float dt)
{
	
}