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

		//实现一个简单的分支处理，其目的在于如果
		//上面的语句没有任何问题那么此次的do-while
		//就不起任何作用，如果上面两次创建中有一
		//次创建的东西为0，那么后面的操作都不会再
		//进行下去了，因为直接会被break出本do-while
	} while (0);

	//场景
	//┗层
	//  ┣菜单
	//  ┃┗菜单项图像
	//  ┣标签
	//  ┗精灵

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

		//一：添加一个菜单
		//创建一个菜单项图像对象
		CCMenuItemImage* pCloseItem = CCMenuItemImage::create(
			"Close/CloseNormal.png", //未点击状态的图像
			"Close/CloseSelected.png", //点击中状态的图像
			this, //响应这个菜单的函数所属的类对象
			menu_selector(HelloWorld::menuCloseCallback)); //响应这个菜单的函数
		CC_BREAK_IF(!pCloseItem); //if(!pCloseItem) break;

		//设置菜单项图像的位置
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

		//创建一个菜单
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);

		//设置菜单位置
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(!pMenu); //if(!pMenu) break;

		//添加菜单为本层的子节点
		this->addChild(pMenu, 1);

		//二：添加一个标签

		//创建一个标签
		CCLabelTTF* pLabel = CCLabelTTF::create(
			"Hello World", //要显示的字符串
			"Arial", //文字外观名词
			24); //文字大小
		CC_BREAK_IF(!pLabel); //if(!pLabel) break;

		//得到窗口尺寸
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		//设置标签的位置
		pLabel->setPosition(ccp(size.width / 2, size.height - 50));

		//添加标签为本层的子节点
		this->addChild(pLabel, 1);

		//三：添加一个精灵

		//创建一个精灵
		CCSprite* pSprite = CCSprite::create("HelloWorld.png");
		CC_BREAK_IF(!pSprite); //if(!pSprite) break;

		//设置精灵位置
		pSprite->setPosition(ccp(size.width / 2, size.height / 2));

		//添加精灵为本层的子节点
		this->addChild(pSprite, 0);

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

