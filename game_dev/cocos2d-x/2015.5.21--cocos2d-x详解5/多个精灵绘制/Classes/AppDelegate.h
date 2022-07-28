#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "cocos2d.h"
using namespace cocos2d;

#define _DEBUG_W 800
#define _DEBUG_H 600

class AppDelegate : private cocos2d::CCApplication
{
public:
	AppDelegate();
	virtual ~AppDelegate();
	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();

	static CCSize m_DebugSize; //调试时候的游戏窗口尺寸，即Windows窗口尺寸
	static CCSize m_ReleaseSize; //发布时候的游戏窗口尺寸，即手机尺寸
	static float m_Scale; //比例值，即发布尺寸/调试尺寸
	static float m_OffsetX; //x方向的偏移量

	//线段绘制
	static void DrawLine(
		const CCPoint& p1,
		const CCPoint& p2,
		ccColor4B c);

	//空心矩形绘制
	static void DrawRect1(
		const CCPoint& p1,
		const CCPoint& p2,
		ccColor4B c);

	//实心矩形绘制
	static void DrawRect2(
		const CCPoint& p1,
		const CCPoint& p2,
		ccColor4B c);
};

#endif
