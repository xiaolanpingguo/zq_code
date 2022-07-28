#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "cocos2d.h"

class AppDelegate : private cocos2d::CCApplication
{
public:
	//构造
	AppDelegate();

	//析构
	virtual ~AppDelegate();

	//游戏初始化的时候被调用
	virtual bool applicationDidFinishLaunching();

	//游戏从前台转入到后台的时候被调用
	virtual void applicationDidEnterBackground();

	//游戏从后台转入到前台的时候被调用
	virtual void applicationWillEnterForeground();
};

#endif

//cocos2d-x中，凡是某个类有sharedXXX的
//静态成员函数的话，这个类都是单件类

//AppDelegate：代表应用程序，类似我们自己的
//             CGameEngine，它里面的函数在程
//             序运行期间的执行顺序如下：
//1)applicationWillEnterForeground
//2)applicationDidFinishLaunching
//3)如果从前台转入后台那么调用applicationDidEnterBackground
//  如果从后台转入前台那么调用applicationWillEnterForeground

//CCDirector：导演类，是管理当前场景运行的类，还可以
//            对当前的显示、帧率等内容进行控制，游戏
//            的运作就是通过导演来运行或者切换场景来
//            办到的，类似我们自己CGameEngine中的场景
//            管理部分，是一个单件类
//sharedDirector（static）：得到整个游戏中的唯一的一个导演类对象
//stopAnimation：停止整个游戏的绘制
//startAnimation：开始整个游戏的绘制
//setOpenGLView：设置OpenGL类对象用于绘图
//setDisplayStats：设置显示帧率与否
//setAnimationInterval：设置游戏帧率
//runWithScene：设置初始运行的场景
//end：结束游戏

//SimpleAudioEngine：简单音频引擎类
//end（static）：结束简单音频引擎的所有工作
//sharedEngine（static）：得到整个游戏中的唯一的一个简单音频引擎类对象
//pauseBackgroundMusic：暂停整个游戏的背景音乐播放
//resumeBackgroundMusic：恢复整个游戏的背景音乐播放

//CCEGLView：OpenGL类
//sharedOpenGLView（static）：得到整个游戏中的唯一的一个OpenGL类对象

//CCLayer：层类，是cocos2d-x中具体完成游戏代
//         码的地方，一个场景中可以装载多个层
//         实现多套不同的输入、输出、逻辑，层
//         必须装入场景中才可以被导演运行

//CCScene：场景类，是cocos2d-x中直接可以被导演
//         装载的类，它本身并不实现什么东西，而
//         仅仅是作为装载层的容器
//create（static）：创建一个场景

//CCNode：树节点类，场景、层都是CCNode的子类，这些
//        子类对象都可以按照树形结构进行组织，一个
//        场景树就是通过CCNode提供的addChild来组织
//        的，一次游戏循环中导演会把场景树进行一个
//        先根遍历将所有的层的输入、输出、逻辑都执
//        行一遍
//addChild：插入子节点