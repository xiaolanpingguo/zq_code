#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	
	//创建自己（HelloWorld），再创建一个
	//场景，然后把自己设置为这个场景的子
	//节点，然后返回场景
	static cocos2d::Scene* createScene();

	//下面的宏会被替换为函数
	CREATE_FUNC(HelloWorld);
	//static HelloWorld* create()
	//{
	//	HelloWorld *pRet = new HelloWorld();
	//	if (pRet && pRet->init())
	//	{
	//		pRet->autorelease();
	//		return pRet;
	//	}
	//	else
	//	{
	//		delete pRet;
	//		pRet = NULL;
	//		return NULL;
	//	}
	//}

	//初始化，装载了菜单、标签、精灵
	virtual bool init();

	//createScene()
	//{
	//	create()
	//	{
	//		init();
	//	}
	//}

	//菜单响应函数，一旦点中菜单那么引擎会自动调用本函数
	void menuCloseCallback(cocos2d::Ref* pSender);

	//图像菜单项
	MenuItemImage* closeItem, * closeItem2;

	void menuCloseCallback2(cocos2d::Ref* pSender);
	MenuItemImage* kkk;
};

#endif

//Scene：代表场景，cocos2d中的场景可以包含很多的层，导演
//       可以设置当前运行的场景
//Layer：代表层（层这个概念类似我们简单引擎中的场景）
//Size：代表尺寸，其中主要数据就是width和height
//Vec2：代表向量，其中主要数据就是x和y
//MenuItemImage：代表图像菜单项
//Ref：引用计数类，几乎所有的cocos2d-x中类的根类都是它
//Node：树节点类，场景、层、精灵等可以组织为树型结构的类的父类都是它