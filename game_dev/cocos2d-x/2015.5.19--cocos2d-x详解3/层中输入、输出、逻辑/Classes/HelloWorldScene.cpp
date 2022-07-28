#include "HelloWorldScene.h"
#include "Test.h"

HelloWorld::HelloWorld()
{
	int x = add(1, 2);
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

	//初始化游戏数据
	hero_pos = CCPointZero;
	move_right = true;
}

void HelloWorld::onExit()
{
	//调用父类的onEnter
	CCLayer::onExit();
}

bool HelloWorld::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	//pTouch->getLocation(); //得到的是GL坐标系下的触屏坐标
	//pTouch->getLocationInView(); //得到的是UI坐标系下的触屏坐标
	
	return true;
}

void HelloWorld::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	
}

void HelloWorld::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	hero_pos = pTouch->getLocation();
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

	ccColor4F cf0 = {0.3f, 0.3f, 0.3f, 0.1f};
	ccDrawSolidRect(ccp(0, 0), ccp(800, 600), cf0);

	//设置当前颜色为红色
	ccDrawColor4B(0xff, 0, 0, 0xff);

	//线段绘制
	ccDrawLine(ccp(0, 0), ccp(300, 150));

	ccDrawColor4B(0xff, 0xff, 0xff, 0xff);
	ccDrawLine(ccp(0, 150), ccp(300, 0));

	//在光照模型计算中，往往用0~1之间的浮点数
	//来表示一个颜色的分量，0~1就相当于是用无
	//符号字符代表颜色分量时候的0~255，那么一
	//个红色就可以用（1.0f, 0.0f, 0.0f, 1.0f）
	//来表示
	ccDrawColor4F(0.0f, 1.0f, 1.0f, 1.0f);
	ccDrawLine(ccp(0, 150), ccp(300, 150));

	//空心矩形绘制
	ccDrawRect(ccp(200, 100), ccp(400, 300));

	//实心矩形绘制
	ccColor4F cf1 = {1.0f, 1.0f, 0.0f, 0.1f};
	ccDrawSolidRect(ccp(250, 150), ccp(450, 350), cf1);

	//实心矩形绘制
	ccColor4F cf2 = {1.0f, 0.0f, 0.0f, 0.3f};
	ccDrawSolidRect(ccp(300, 200), ccp(600, 400), cf2);

	//弧度 = 弧长 / 半径，是一种表示角度大小的单位，90°的角度
	//的弧度值为3.1415926f / 2.0f，180°的角度的弧度值为3.1415926f，
	//360°的角度的弧度值为3.1415926f * 2.0f

	//等边形绘制
	ccDrawCircle(
		hero_pos, //中心点
		80.0f, //半径
		0.0f, //角度
		8, //边数
		true); //是否绘制线到中心点
}

void HelloWorld::update(float dt)
{
	if (move_right)
	{
		hero_pos.x += 10;
		if (hero_pos.x > 800)
			move_right = false;
	}
	else
	{
		hero_pos.x -= 10;
		if (hero_pos.x < 0)
			move_right = true;
	}
}