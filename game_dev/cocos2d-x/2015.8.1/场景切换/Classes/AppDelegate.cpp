#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld* AppDelegate::h;
Game* AppDelegate::g;

AppDelegate::AppDelegate()
{}

AppDelegate::~AppDelegate() 
{
	delete g;
	delete h;
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	//得到导演类对象
    auto director = Director::getInstance();

	//通过导演类对象得到OpenGL对象
    auto glview = director->getOpenGLView();

	//如果没有得到OpenGL对象
    if(!glview)
	{
		//创建一个名字叫My Game的OpenGL对象
        glview = GLViewImpl::create("My Game");

		//将OpenGL对象设置到导演中，导演会用
		//OpenGL对象来进行绘制
        director->setOpenGLView(glview);
    }

	//告知引擎本程序设计时候的尺寸
	glview->setDesignResolutionSize(_DESIGN_W, _DESIGN_H, ResolutionPolicy::EXACT_FIT);

	//设置窗口大小为设计时候的尺寸
	glview->setFrameSize(_DESIGN_W, _DESIGN_H);

	//设置是否显示帧状态
    //director->setDisplayStats(true);

    //设置帧率，游戏中所谓帧率就是值得每秒的
	//游戏循环次数，一般来说二维游戏从25帧/秒
	//到40帧/秒都可以，三维游戏一般需要60帧/秒
    director->setAnimationInterval(1.0 / 30);

	//创建层
	h = new HelloWorld;
	g = new Game;

	//用场景装载层并用导演运行
	Scene* s = Scene::create();
	s->addChild(h);

	//不使用切换动画
    //director->runWithScene(s); //设置初始的场景

	//cocos2d中提供了很多的动画切换类，它们可以帮助我们在
	//多个场景中进行场景切换之间绘制动画，这些动画类基本上
	//都是TransitionScene的子类，使用方式就是在导演设置初始
	//场景或者设置当前场景的函数中调用这些类的create函数，用
	//法大致如下create(动画秒数，目标场景)
	director->runWithScene(TransitionFade::create(2.0f, s));

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	//停止绘制游戏画面
    Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	//开始绘制游戏画面
    Director::getInstance()->startAnimation();
}
