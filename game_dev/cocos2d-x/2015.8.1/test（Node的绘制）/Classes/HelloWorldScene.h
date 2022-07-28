#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(HelloWorld);
	virtual bool init();

	Sprite* s[3];

	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif

//Node是树节点类，凡是派生自它的类都可以被组织为树形
//结构，它的派生类非常多，最常用的是场景（Scene）、层
//（Layer）、精灵（Sprite），这些东西使用addChild函数
//可以组织为一棵渲染树，最常见的场景组合如下：
//                 [场景0]
//                 ...
//导演 ---运行---> [场景i]---┐
//                 ...       ├[层0]
//                 [场景n]   ├...
//                           └[层n]---┐
//                                     ├[精灵0]
//                                     ├...
//                                     └[精灵n]
//Node中有三个和绘制情况有关系的重要数据，分别是位置、
//尺寸、锚点，对它们进行读写的函数分别如下：
//getPosition：得到位置
//setPosition：设置位置
//getContentSize：得到尺寸
//setContentSize：设置尺寸
//getAnchorPoint：得到锚点
//setAnchorPoint：设置锚点
//isIgnoreAnchorPointForPosition：得到是否忽略锚点
//ignoreAnchorPointForPosition：设置是否忽略锚点
//位置：一个节点相对于其父节点的原点（父节点矩形的左
//      下角）而言的一个坐标，如果不手动设置那么所有
//      Node子类对象的位置都默认设置为(0,0)
//尺寸：节点都包含了一个矩形（就是绘制的区域大小），
//      尺寸值的就是这个矩形的宽高，不同的Node子类的
//      尺寸会被设置为不同的大小，比如场景、层的尺寸
//      会被设置为屏幕大小，而精灵的大小一般就是图片
//      的大小
//锚点：指的是节点包含的矩形上面的一个点，这个点的设
//      置是(0,0)~(1,1)，也就是一个比例，如果忽略了锚
//      点那么锚点相当于就是(0,0)，当绘制的时候，锚点
//      会被对端位置进行绘制，不同的Node的子类的锚点
//      初始化的时候会被设置为不同的数据，比如精灵的话
//      默认锚点设置为(0.5,0.5)，而场景、层默认设置为(0,0)
//除了上述数据，还可以用isVisible、setVisible来读写节
//点的可见性，还可以setZOrder、getZOrder来读写节点绘制
//的顺序，ZOrder越大那么越后面绘制
//场景绘制的伪代码如下
//节点绘制（节点* n, 父节点原点绝对坐标 p）
//{
//	绘制绝对坐标 q;
//	q.x = n->getPosition().x + p.x;
//	q.y = n->getPosition().y + p.y;
//
//	用n的锚点对端q进行绘制
//
//	n原点绝对坐标 r;
//	r.x = q.x - n->getAnchorPoint().x * n->getContentSize().width;
//	r.y = q.y - n->getAnchorPoint().y * n->getContentSize().height;
//
//	循环n的所有子节点c
//		节点绘制(c, r);
//}
//导演调用该函数来绘制整个节点树
//节点绘制(当前场景，Vec(0,0));
//使用Node来组织游戏元素的好处在于可以通过处理父节点来
//间接控制子节点，比如设置父节点为不可见，那么父节点及
//其所有子节点都不可见，比如设置父节点在旋转，那么父节
//点及其相关子节点都要进行旋转