#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::CCLayer
{
public:

	//返回一个包含本层的场景
	static cocos2d::CCScene* scene();

	//生成create函数的宏
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

	//初始化
	virtual bool init();

	//上面三个函数的调用关系
	//scene()
	//{
	//	create()
	//	{
	//		init();
	//	}
	//}

	//菜单响应函数
	void menuCloseCallback(CCObject* pSender);
};

#endif