#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
	//定义的场景指针
	CCScene* scene = NULL;
	do 
	{
		//创建场景
		scene = CCScene::create();
		CC_BREAK_IF(!scene); //if(!scene) break;

		//创建本层
		HelloWorld* layer = HelloWorld::create();
		CC_BREAK_IF(!layer); //if(!layer) break;

		//将本层对象装载入刚才创建的场景，即将
		//本层对象设置为刚才创建的场景对象的子
		//节点
		scene->addChild(layer);

		//scene->setPosition(ccp(0, 160));

		//实现一个简单的分支处理，其目的在于如果
		//上面的语句没有任何问题那么此次的do-while
		//就不起任何作用，如果上面两次创建中有一
		//次创建的东西为0，那么后面的操作都不会再
		//进行下去了，因为直接会被break出本do-while
	} while (0);

	//返回场景
	return scene;
}

bool HelloWorld::init()
{
	//实现本层中的元素的初始化
	bool bRet = false;

	do 
	{
		//调用父类的init
		CC_BREAK_IF(!CCLayer::init());

		//场景和层的数据默认如下
		//位置（0，0）
		//尺寸（窗口宽，窗口高）
		//锚点（0，0）

		//精灵的数据默认如下
		//位置（0，0）
		//尺寸（图像宽，图像高
		//锚点（0.5，0.5）

		CCSprite* s1 = CCSprite::create("1.PNG");
		s1->ignoreAnchorPointForPosition(true); //s1忽略锚点相当于设置锚点为（0,0）

		CCSprite* s2 = CCSprite::create("2.PNG");
		s2->setPosition(ccp(100, 50));
		s2->setAnchorPoint(ccp(0.5f, 0.0f));

		CCSprite* s3 = CCSprite::create("3.PNG");
		s3->setPosition(ccp(50, 100));
		s3->setAnchorPoint(ccp(0.5f, 0.5f));

		CCSprite* s4 = CCSprite::create("4.PNG");
		s4->setPosition(ccp(100, 200));
		s4->setAnchorPoint(ccp(0.0f, 0.5f));

		addChild(s1);
		s1->addChild(s2);
		s2->addChild(s3);
		s2->addChild(s4);

		//this->setPosition(ccp(240, 0));

		//设置返回值
		bRet = true;

	} while (0);

	return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	//结束游戏
	CCDirector::sharedDirector()->end();
}

