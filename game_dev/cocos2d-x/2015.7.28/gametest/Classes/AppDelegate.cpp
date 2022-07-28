#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;
//注意cocos2d的所有类都放在名字空间cocos2d中的，所以
//使用上面那句宏（展开为using namespace cocos2d;）将
//cocos2d的名字空间打开

AppDelegate::AppDelegate()
{}

AppDelegate::~AppDelegate() 
{}

void AppDelegate::initGLContextAttrs()
{
	//OpenGL是一个底层图形库（同Direct3D类似），提供了
	//很多的图形渲染功能，cocos2d-x的底层绘制就是使用的
	//OpenGL（严格来说是OpenGL的嵌入式版本OpenGLES，现
	//在的智能手机显卡厂商基本上都在手机中实现了OpenGLES
	//），所以此处允许用户自行设置OpenGL使用的像素格式（
	//其实一般都不做修改）
   
	//像素格式即存储一个像素所用到的数据格式，下面的代码
	//GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
	//的解释如下：
	//8位红色分量
	//8位绿色分量
	//8位蓝色分量
	//8位Alpha混合通道
	//24位深度缓冲
	//8位模板缓冲
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	//auto
	//c99标准中，表示定义栈内存中的变量，一般
	//我们都省略了，比如下面的代码
	//int a = 1; //编译器会认为是auto int a = 1;
	//auto的本意是自动，定义的变量是自动释放
	//内存的，也即告知编译器它修饰的变量放在
	//栈中
	//c11标准中，表示推断的意思，即自动识别定
	//义的变量类型，比如下面的代码
	//auto a = 1.0; //编译器可以从后面的初始化表达式的结果类型推断出来a是double类型
	//注意c11中的auto和c99中的功能完全不同了
	//c11中用auto定义变量必须要初始化，如果
	//不初始化，那么是无法推断类型的
	//auto a = 1.0; //可以推断出来为double
	//auto a; //报错，没有初始化语句

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

	//可以在此处通过OpenGL设置编写游戏时候的
	//窗口大小，注意cocos2d-x 3.x默认的编写
	//游戏时候的窗口大小为960*640
	//glview->setFrameSize(640, 480);

	//设置是否显示帧状态
    director->setDisplayStats(true);

    //设置帧率，游戏中所谓帧率就是值得每秒的
	//游戏循环次数，一般来说二维游戏从25帧/秒
	//到40帧/秒都可以，三维游戏一般需要60帧/秒
    director->setAnimationInterval(1.0 / 30);

	//上面的代码基本不用修改

    //用HelloWorld类的静态成员函数createScene
	//创建一个包含HelloWorld层对象的场景
    auto scene = HelloWorld::createScene();

    //设置初始的场景
    director->runWithScene(scene);

	OutputDebugStringA("applicationDidFinishLaunching\n");

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	//停止绘制游戏画面
    Director::getInstance()->stopAnimation();

    //如果使用了音频引擎，那么应该加上下面的代码

	//暂停背景音乐的播放
    //SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	OutputDebugStringA("applicationDidEnterBackground\n");
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	//开始绘制游戏画面
    Director::getInstance()->startAnimation();

    //如果使用了音频引擎，那么应该加上下面的代码

	//恢复背景音乐的播放
    //SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

	OutputDebugStringA("applicationWillEnterForeground\n");
}
