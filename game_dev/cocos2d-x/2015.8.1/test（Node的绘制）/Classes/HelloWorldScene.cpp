#include "HelloWorldScene.h"

void PrintNode(Node* n, int level)
{
	if (n)
	{
		for (int i = 0; i < level; ++i)
			OutputDebugStringA("■");

		Vec2 a(0.0f, 0.0f);
		if (!n->isIgnoreAnchorPointForPosition())
			a = n->getAnchorPoint();

		char buf[256];
		sprintf_s(
			buf,
			256,
			"p(%d,%d)s(%d,%d)a(%f,%f)\n",
			(int)n->getPosition().x,
			(int)n->getPosition().y,
			(int)n->getContentSize().width,
			(int)n->getContentSize().height,
			a.x,
			a.y);
		OutputDebugStringA(buf);

		//递归子节点
		for (int i = 0; i < n->getChildrenCount(); ++i)
		{
			Vector<Node*>& v = n->getChildren();
			PrintNode(v.at(i), level + 1);
		}
	}
}

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);

	//打印所有节点的信息
	PrintNode(scene, 0);

	return scene;
}

bool HelloWorld::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	//得到窗口的尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//得到窗口的左下角位置
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建精灵
	s[0] = Sprite::create("0.png");
	s[1] = Sprite::create("1.png");
	s[2] = Sprite::create("2.png");
	
	//设置
	//sprite->setPosition(, );

	s[0]->();
	this->addChild(s[0]);
	s[0]->addChild(s[1]);
	this->addChild(s[2]);
	s[1]->setPosition(200, 200);
	//s[2]->setPosition(450, 450);
	s[2]->ignoreAnchorPointForPosition(true);

	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}