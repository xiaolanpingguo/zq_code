#include "Game.h"
#include "AppDelegate.h"

Game::Game()
{
	//创建菜单
	MenuItemImage* c = MenuItemImage::create(
		"h0.png",
		"h1.png",
		CC_CALLBACK_1(Game::menuCloseCallback, this));
	c->ignoreAnchorPointForPosition(true);
	Menu* m = Menu::create(c, NULL);
	m->setPosition(Vec2::ZERO);
	this->addChild(m, 2);

	//创建精灵
	s = Sprite::create("3.png");
	s->setPosition(Vec2(320, 240));

	this->addChild(s);
}

void Game::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	//切换场景
	Scene* s = Scene::create();
	s->addChild(AppDelegate::h);
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, s)); //设置当前场景

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}