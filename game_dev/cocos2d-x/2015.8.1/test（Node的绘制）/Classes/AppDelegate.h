#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

#define _DESIGN_W 640.0f
#define _DESIGN_H 480.0f

class AppDelegate : private cocos2d::Application
{
public:
	//构造
    AppDelegate();

	//析构
    virtual ~AppDelegate();

	//初始化OpenGL的像素格式
    virtual void initGLContextAttrs();

    //初始化的时候调用本函数
    virtual bool applicationDidFinishLaunching();

	//游戏从前台转入后台的时候调用本函数
    virtual void applicationDidEnterBackground();

	//游戏从后台转入前台的时候调用本函数
    virtual void applicationWillEnterForeground();
};

#endif

//AppDelegate：代表应用程序
//Director（单件）：代表导演，导演主要负责场景调度

