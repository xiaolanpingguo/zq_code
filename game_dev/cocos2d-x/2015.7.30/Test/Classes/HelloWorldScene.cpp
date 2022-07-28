#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
	//创建场景
	auto scene = Scene::create();

	//调用CREATE_FUNC宏替换出来的静态create函数
	auto layer = HelloWorld::create();

	//设置本类对象为场景的子节点
	scene->addChild(layer);

	//返回场景
	return scene;
}

bool HelloWorld::init()
{
	//调用父类的初始化
	if ( !Layer::init() )
	{
		return false;
	}

	//得到窗口的尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//得到窗口的左下角位置
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//cocos2d编程中的两个坐标系，其中绘制
	//时候使用的坐标系都是GL坐标系
	//UI坐标系：x向右，y向下
	//GL坐标系：x向右，y向上

	//创建一个图像菜单项
	closeItem = MenuItemImage::create(
		"close/CloseNormal.png", //菜单未被按下时候的图像
		"close/CloseSelected.png", //菜单被按下时候的图像
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this)); //菜单响应函数

	//设置图像菜单项的位置
	closeItem->setPosition(
		Vec2(
		//0 + 960 - 40 / 2 = 940
		origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		//0 + 40 / 2 = 20
		origin.y + closeItem->getContentSize().height / 2)
		);

	//再创建1个图像菜单项，并依然选择是menuCloseCallback为响应函数
	closeItem2 = MenuItemImage::create(
		"close/ok1.png",
		"close/ok2.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem2->setPosition(
		//100 / 2 = 50
		closeItem2->getContentSize().width / 2,
		//60 / 2 = 30
		closeItem2->getContentSize().height / 2);

	kkk = MenuItemImage::create(
		"close/kkk1.png",
		"close/kkk2.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback2, this));
	kkk->setPosition(
		//100 / 2 = 50
		kkk->getContentSize().width / 2,
		//60 / 2  + = 30
		kkk->getContentSize().height / 2 + closeItem2->getContentSize().height);

	//通过已有的图像菜单项创建一个菜单，下面的菜单的静态
	//函数create是一个不定参函数，前面应该依次放入图像菜
	//单项，最后以NULL作为结束，本函数的本质就是把图像菜
	//单项通过addChild函数设置为菜单的子节点，下面的代码
	//执行完毕之后menu就有了三个子节点分别是closeItem、
	//closeItem2、kkk
	auto menu = Menu::create(closeItem, closeItem2, kkk, NULL);

	//设置菜单位置
	menu->setPosition(Vec2::ZERO); //Vec2::ZERO就是Vec2(0.0f, 0.0f)
	
	//将菜单设置为本层的子节点，第二个参数是优先级，优先级
	//越大那么就越后绘制，那么优先级高的就会挡住优先级低的
	this->addChild(menu, 1);

	//TTF是指的ture type fonts，是一种可以拉伸而不发生形变的字体，一
	//般来说字体有两大类
	//1）点阵字体，最早的字体存储方案，一般来说一定的字节就可以存储
	//   点阵字体了，但是点阵字体在缩放的时候可能有形变，最基本的存
	//   储在主板Bios中的字节就是点阵字体，相当于是一副黑白位图
	//   □□□□□□□■□□□□□□□□
	//   □□□□□□□■□□□□□□□□
	//   □■■■■■■■■■■■■■■□
	//   □□□□□□□■□□□□□□□□
	//   □□□□□□■□■□□□□□□□
	//   □□□□□■□□□■■□□□□□
	//   □□■■■□□□□□■■■■□□
	//   ■■■□□□□□□□□□□■■■
	//2）truetype字体，后期在图形界面下面流行的一种字体，这种字体不是
	//   用字节存储文字的点信息，而是存储这个文字的笔画，也就是说存储
	//   的信息类似：从(x1,y1)到(x2,y2)是直线，从(x3,y3)到(x4,y4)是曲
	//   线等，这样的存储可以使得在任何尺寸下面进行文字的绘制都不失真

	//创建标签，标签就是显示一段文字的，相当于是MFC中的静态文本，其本质
	//是根据文字创建出来的一张图片
	auto label = Label::createWithTTF(
		"Hello World", //文字内容
		"fonts/Marker Felt.ttf", //字体文件
		32); //字体大小
	//字体大小为32的时候，整个标签尺寸为139*34
	//字体大小为64的时候，整个标签尺寸为276*68
	Size label_size = label->getContentSize();

	//设置标签位置
	label->setPosition(
		Vec2(
		//0 + 960 / 2 = 480
		origin.x + visibleSize.width/2,
		//0 + 640 - 34 = 606
		origin.y + visibleSize.height - label->getContentSize().height
		));

	//设置标签为本层的子节点
	this->addChild(label, 1);

	//创建一个精灵，精灵是cocos2d中的核心类，几乎所有的游戏画面
	//元素都可以用精灵来表现，精灵的本质是一张图像，配合“变换”
	//和“动作”精灵可以有很丰富的表现
	auto sprite = Sprite::create("HelloWorld.png");

	//设置精灵位置
	sprite->setPosition(
		Vec2(
		//960 / 2 + 0
		visibleSize.width/2 + origin.x,
		//640 / 2 + 0
		visibleSize.height/2 + origin.y)
		);

	//设置精灵为本层的子节点
	this->addChild(sprite, 3);

	//第二个精灵
	auto sprite2 = Sprite::create("s.png");
	sprite2->setPosition(Vec2(200.0f, 200.0f));
	this->addChild(sprite2, 0);

	//addChild的第二参数决定了绘制顺序，越大的优
	//先级就越后绘制，所以上面的代码是第一个精灵
	//遮挡了第二个精灵

	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	//传入的pSender就是当前被点击菜单项的地址，使用
	//分支选择语句可以非常方便地区分到底是那个菜单被
	//点击了

	if (pSender == closeItem)
		Director::getInstance()->end();
	else if (pSender == closeItem2)
		closeItem2->setVisible(false);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuCloseCallback2(cocos2d::Ref* pSender)
{
	//kkk的响应函数
}