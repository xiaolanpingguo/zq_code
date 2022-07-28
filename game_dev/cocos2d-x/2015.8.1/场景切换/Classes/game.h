#ifndef __GAME_H__
#define __GAME_H__

#include "cocos2d.h"
USING_NS_CC;

class Game : public cocos2d::Layer
{
public:
	Game();
	Sprite* s;
	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif