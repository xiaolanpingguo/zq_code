#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class MyTexture : public CCTexture2D
{
public:

	//坐标都是UI坐标系
	void Draw(
		int sx, int sy, int sw, int sh, //源矩形
		int dx, int dy, int dw, int dh) //目标矩形
	{
		//得到纹理宽高
		float tw = getContentSize().width;
		float th = getContentSize().height;

		//根据源矩形设置4个顶点的比例
		//sx / tw, (sy + sh) / th
		//(sx + sw) / tw, (sy + sh) / th
		//sx / tw, sy / th
		//(sx + sw) / tw, sy / th

		//设置源矩形比例
		GLfloat coordinates[]
		=
		{    
			sx / tw, (sy + sh) / th,
			(sx + sw) / tw, (sy + sh) / th,
			sx / tw, sy / th,
			(sx + sw) / tw, sy / th
		};

		//设置目标矩形位置
		GLfloat vertices[] =
		{
			dx * AppDelegate::m_Scale + AppDelegate::m_OffsetX, (AppDelegate::m_DebugSize.height - (dy + dh)) * AppDelegate::m_Scale,
			(dx + dw) * AppDelegate::m_Scale + AppDelegate::m_OffsetX, (AppDelegate::m_DebugSize.height - (dy + dh)) * AppDelegate::m_Scale,
			dx * AppDelegate::m_Scale + AppDelegate::m_OffsetX, (AppDelegate::m_DebugSize.height - dy) * AppDelegate::m_Scale,
			(dx + dw) * AppDelegate::m_Scale + AppDelegate::m_OffsetX, (AppDelegate::m_DebugSize.height - dy) * AppDelegate::m_Scale
		};

		ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords);
		m_pShaderProgram->use();
		m_pShaderProgram->setUniformForModelViewProjectionMatrix();
		ccGLBindTexture2D(m_uName);
		glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, coordinates);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
};

class HelloWorld : public cocos2d::CCLayer
{
public:

	//初始化
	HelloWorld();

	//收尾
	~HelloWorld();

	//得到包含本层的场景
    CCScene* getScene();

	//当程序从其它场景转换到本层所属的场景时被调用
	virtual void onEnter();

	//当程序从本层所属的场景转换到其它场景时被调用
    virtual void onExit();

	//当程序从其它场景转换到本层所属的场景启用场
	//景过渡动画的情况下，过渡动画结束时被调用
    //virtual void onEnterTransitionDidFinish();

	//要想开启触屏，必须将本层设置为触屏消息的
	//分发目标，cocos2d中触屏消息都是由一个叫
	//触屏代理器的类对象首先得到，由它来决定往
	//当前场景中的哪些层里面发送这些触屏消息，
	//只有确定某个层是当前的分发目标，那么触屏
	//代理器才会把触屏消息发给这个层，下面的这
	//些虚函数才能被调用，一般都在onEnter中设置
	//本层为触屏消息的分发目标
    
    //触屏按下时被调用
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);

	//触屏移动时被调用
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);

	//触屏抬起时被调用
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);

	//触屏被系统取消时被调用
    virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);

	//重写draw函数可以完成本层的绘制，cocos2d引擎
	//会在每次游戏循环中来调用这个draw函数
	virtual void draw();

	//更新函数，只要在onEnter通过scheduleUpdate中设
	//置了本层要进行更新，那么cocos2d引擎会在每次游
	//戏循环中来调用这个update函数，并传入当前时间
	virtual void update(float dt);

	//纹理
	MyTexture* t1;
	MyTexture* t2;
	CCPoint pos;
};

#endif