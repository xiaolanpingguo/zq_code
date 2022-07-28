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

//CCNode是cocos2d-x中的核心类，它是用来组织场景树的，它
//里面有位置、尺寸、锚点等核心成员数据，这些东西关系到
//整个画面的绘制，CCNode中有一个draw函数，这个函数是虚
//函数，所有具体的CCNode子类可以根据自己的情况来重写该
//函数，比如场景中没有重写该函数，精灵中就重写了该函数
//让这个函数绘制一张图像，对整个场景的绘制就是先根遍历
//这棵CCNode树并依次调用每个节点的draw函数

//getContentSize：得到尺寸
//setContentSize：设置尺寸
//CCNode大家可以将其想象为一个屏幕矩形，矩形
//的宽高就由它的尺寸决定

//getPosition：得到位置
//setPosition：设置位置
//CCNode的位置是需要配合父节点（当然也是一个
//CCNode）的原点以及当前节点的锚点共同作用的
//，也就是说这个位置是相对于父节点的原点而言
//的，具体在绘制的时候，当前CCNode会用描点去
//对端当前算出来的位置

//getAnchorPoint：得到锚点
//setAnchorPoint：设置锚点
//ignoreAnchorPointForPosition：是否忽略锚点
//isIgnoreAnchorPointForPosition：得到是否忽略锚点
//锚点是每个CCNode中的一个点（这个点往往设置为
//0~1之间的比例值，比如0.5、0.5就表示位置是在
//这个CCNode的正中间），锚点的作用就是配合位置
//进行绘制，如果忽略锚点，那么锚点就是(0,0)