#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();

	Sprite* s[3];
	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif