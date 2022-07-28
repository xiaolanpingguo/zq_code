#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <vector>
#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

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
    
	//多点触碰
	CCPoint touch[32];
	int touch_num;
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	std::vector<CCPoint> began, move, end;

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
	MyTexture* t3;

	//文字绘制
	void DrawString(
		int x, int y, //文字绘制区域的左上角x、y坐标
		int w, int h, //每个文字的宽、高
		int xn, int yn,  //文字绘制区域的x、y方向的文字数量
		const char* str)
	{
		//初次加载稍慢
		MyTexture* ascii = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("ASCII.PNG");

		//循环绘制文字
		for (int i = 0; str[i] && i < xn * yn; ++i)
		{
			//得到源文字矩形
			int sx = (str[i] % 32) * 25;
			int sy = (str[i] / 32) * 48;

			//得到目标文字矩形
			int dx = (i % xn) * w;
			int dy = (i / xn) * h;

			ascii->Draw(
				sx, sy, 25, 48,
				dx + x, dy + y, w, h);
		}
	}

	unsigned long file_size;
	unsigned char* file_data;

	CCPoint hero;

	std::string res_d, wr_d;
};

#endif

//SimpleAudioEngine是一个单件类，负责音频的播放，背景音乐
//一次只能播放一个，音效同一时间可以有多个存在

//播放背景音乐，第二参数判断是否循环
//void playBackgroundMusic(const char* pszFilePath, bool bLoop);

//停止背景音乐播放，参数判断是否释放数据
//void stopBackgroundMusic(bool bReleaseData);

//暂停背景音乐
//void pauseBackgroundMusic();

//恢复背景音乐
//void resumeBackgroundMusic();

//获取设置背景音乐音量
//float getBackgroundMusicVolume();
//void setBackgroundMusicVolume(float volume);

//获取设置音效音量
//float getEffectsVolume();
//void setEffectsVolume(float volume);

//播放音效，返回代表该音效的id
//unsigned int playEffect(const char* pszFilePath, bool bLoop);

//暂停指定音效和所有音效
//void pauseEffect(unsigned int nSoundId);
//void pauseAllEffects();

//恢复指定音效和所有音效
//void resumeEffect(unsigned int nSoundId);
//void resumeAllEffects();

//停止指定音效和所有音效
//void stopEffect(unsigned int nSoundId);
//void stopAllEffects();