#include "HelloWorldScene.h"
#include "AppDelegate.h"

HelloWorld::HelloWorld()
{
	//得到窗口的尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//得到窗口的左下角位置
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建菜单
	MenuItemImage* c = MenuItemImage::create(
		"c0.png",
		"c1.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	c->ignoreAnchorPointForPosition(true);
	c->setPosition(Vec2(320, 240));
	Menu* m = Menu::create(c, NULL);
	m->setPosition(Vec2::ZERO);
	this->addChild(m, 2);

	//创建精灵
	s[0] = Sprite::create("0.png");
	s[1] = Sprite::create("1.png");
	s[2] = Sprite::create("2.png");
	
	//设置
	//sprite->setPosition(, );

	this->addChild(s[0]);
	s[0]->addChild(s[1]);
	this->addChild(s[2]);
	s[1]->setPosition(200, 200);
	s[2]->ignoreAnchorPointForPosition(true);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	//切换场景
	Scene* s = Scene::create();
	s->addChild(AppDelegate::g);
	Director::getInstance()->replaceScene(TransitionFlipY::create(2.0f, s));

	//TransitionFade：淡入淡出
	//TransitionRotoZoom
	//TransitionJumpZoom
	//TransitionFlipY

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}