#include "UI.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define _INIT_SPRITE_NUM 4

//对cocos2d本身的CCTexture2D进行扩充
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

CGameLayer::CGameLayer()
{
	//得到读写文件的目录路径
	std::string s = CCFileUtils::sharedFileUtils()->getWriteablePath();
	strcpy(m_RWDirectory, s.c_str());

	//设置边缘颜色为黑色
	m_BorderColor = 0x000000ff;

	//创建用于绘制的精灵
	for (int i = 0; i < _INIT_SPRITE_NUM; ++i)
	{
		//通过默认的图像创建精灵
		CCSprite* sprite = CCSprite::create("Default/S_DEFAULT.PNG");

		//设置精灵作为本层的子节点
		addChild(sprite);

		//将精灵放入表中
		m_Sprites.push_back(sprite);
	}
}

CGameLayer::~CGameLayer()
{
	for (int i = 0; i < (int)m_UI.size(); ++i)
		delete m_UI[i];
}

void CGameLayer::onEnter()
{
	//调用父类的onEnter
	CCLayer::onEnter();

	//设置本层开启触屏
	setTouchEnabled(true);

	//开启本层的更新
	scheduleUpdate();

	//设置逻辑执行标志为假
	m_Logic = false;

	//初始化当前精灵下标为0
	m_CurSpriteIndex = 0;

	Enter();

	//所有UI调用入函数
	for (int i = 0; i < (int)m_UI.size(); ++i)
		m_UI[i]->Enter();
}

void CGameLayer::onExit()
{
	//所有UI调用出函数
	for (int i = 0; i < (int)m_UI.size(); ++i)
		m_UI[i]->Exit();

	Exit();

	//调用父类的onEnter
	CCLayer::onExit();
}

void CGameLayer::onEnterTransitionDidFinish()
{
	m_Logic = true;
}

void CGameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent)
{
	m_TouchesNum = 0;
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCPoint point = ((CCTouch*)(*it))->getLocationInView();
		if (point.x > AppDelegate::m_OffsetX && point.x < (AppDelegate::m_ReleaseSize.width - AppDelegate::m_OffsetX))
		{
			point.x -= AppDelegate::m_OffsetX;
			point.x /= AppDelegate::m_Scale;
			point.y /= AppDelegate::m_Scale;
			m_Touches[m_TouchesNum++] = point;
		}
	}
	if (m_TouchesNum > 0)
	{
		//UI响应
		bool ui_click = false;
		for (int i = 0; i < (int)m_UI.size(); ++i)
		{
			if (m_UI[i]->m_Visible && m_UI[i]->m_Active)
			{
				//判断是否在内部
				if (m_Touches[0].x >= m_UI[i]->m_Rect.origin.x &&
					m_Touches[0].x < m_UI[i]->m_Rect.origin.x + m_UI[i]->m_Rect.size.width &&
					m_Touches[0].y >= m_UI[i]->m_Rect.origin.y &&
					m_Touches[0].y < m_UI[i]->m_Rect.origin.y + m_UI[i]->m_Rect.size.height)
				{
					m_UI[i]->OnMessage(_UE_IN_DOWN, m_Touches[0].x - m_UI[i]->m_Rect.origin.x, m_Touches[0].y - m_UI[i]->m_Rect.origin.y);
					ui_click = true;
				}
				else
					m_UI[i]->OnMessage(_UE_OUT_DOWN, m_Touches[0].x - m_UI[i]->m_Rect.origin.x, m_Touches[0].y - m_UI[i]->m_Rect.origin.y);
			}
		}

		if (!ui_click)
			InputDown(m_Touches);
	}
}

void CGameLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent)
{
	m_TouchesNum = 0;
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCPoint point = ((CCTouch*)(*it))->getLocationInView();
		if (point.x > AppDelegate::m_OffsetX && point.x < (AppDelegate::m_ReleaseSize.width - AppDelegate::m_OffsetX))
		{
			point.x -= AppDelegate::m_OffsetX;
			point.x /= AppDelegate::m_Scale;
			point.y /= AppDelegate::m_Scale;
			m_Touches[m_TouchesNum++] = point;
		}
	}
	if (m_TouchesNum > 0)
		InputMove(m_Touches, m_TouchesNum);
}

void CGameLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* Event)
{
	m_TouchesNum = 0;
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCPoint point = ((CCTouch*)(*it))->getLocationInView();
		if (point.x > AppDelegate::m_OffsetX && point.x < (AppDelegate::m_ReleaseSize.width - AppDelegate::m_OffsetX))
		{
			point.x -= AppDelegate::m_OffsetX;
			point.x /= AppDelegate::m_Scale;
			point.y /= AppDelegate::m_Scale;
			m_Touches[m_TouchesNum++] = point;
		}
	}
	if (m_TouchesNum > 0)
	{
		//UI响应
		bool ui_click = false;
		for (int i = 0; i < (int)m_UI.size(); ++i)
		{
			if (m_UI[i]->m_Visible && m_UI[i]->m_Active)
			{
				//判断是否在内部
				if (m_Touches[0].x >= m_UI[i]->m_Rect.origin.x &&
					m_Touches[0].x < m_UI[i]->m_Rect.origin.x + m_UI[i]->m_Rect.size.width &&
					m_Touches[0].y >= m_UI[i]->m_Rect.origin.y &&
					m_Touches[0].y < m_UI[i]->m_Rect.origin.y + m_UI[i]->m_Rect.size.height)
				{
					m_UI[i]->OnMessage(_UE_IN_UP, m_Touches[0].x - m_UI[i]->m_Rect.origin.x, m_Touches[0].y - m_UI[i]->m_Rect.origin.y);
					ui_click = true;
				}
				else
					m_UI[i]->OnMessage(_UE_OUT_UP, m_Touches[0].x - m_UI[i]->m_Rect.origin.x, m_Touches[0].y - m_UI[i]->m_Rect.origin.y);
			}
		}

		if (!ui_click)
			InputUp(m_Touches);
	}
}

void CGameLayer::ccTouchesCancelled(CCSet* pTouches, CCEvent* pEvent)
{}

void CGameLayer::draw()
{
	Output();

	//绘制UI
	for (int i = 0; i < (int)m_UI.size(); ++i)
	{
		if (m_UI[i]->m_Visible)
			m_UI[i]->Render();
	}

	//得到边界颜色的浮点数表示
	ccColor4F color
		=
	{
		(m_BorderColor >> 24 & 0xff) / 255.0f,
		(m_BorderColor >> 16 & 0xff) / 255.0f,
		(m_BorderColor >> 8 & 0xff) / 255.0f,
		(m_BorderColor & 0xff) / 255.0f
	};

	//得到游戏画面宽度、边界矩形宽度
	float game_w = AppDelegate::m_DebugSize.width * AppDelegate::m_ReleaseSize.height / AppDelegate::m_DebugSize.height;
	float border_w = (AppDelegate::m_ReleaseSize.width - game_w) / 2.0f;

	//绘制边界
	ccDrawSolidRect(
		ccp(0, 0),
		ccp(border_w, AppDelegate::m_ReleaseSize.height),
		color);
	ccDrawSolidRect(
		ccp(AppDelegate::m_ReleaseSize.width - border_w, 0),
		ccp(AppDelegate::m_ReleaseSize.width, AppDelegate::m_ReleaseSize.height),
		color);
}

void CGameLayer::update(float dt)
{
	//设置所有精灵为不可见
	for (int i = 0; i < (int)m_Sprites.size(); ++i)
		m_Sprites[i]->setVisible(false);

	//设置当前精灵下标为0
	m_CurSpriteIndex = 0;

	if (m_Logic)
		Logic(dt);
}

void CGameLayer::Enter(){}
void CGameLayer::InputDown(CCPoint* p){}
void CGameLayer::InputMove(CCPoint* p, int n){}
void CGameLayer::InputUp(CCPoint* p){}
void CGameLayer::Output(){}
void CGameLayer::Logic(float dt){}
void CGameLayer::Exit(){}
void CGameLayer::Quit()
{
	CCDirector::sharedDirector()->end();
}

void CGameLayer::SetBorderColor(int BorderColor)
{
	m_BorderColor = BorderColor;
}
void CGameLayer::DrawLine(const CCPoint& p1, const CCPoint& p2, int c)
{
	//根据传入的UI坐标系的y坐标得到GL坐标系的y坐标
	float p1y = AppDelegate::m_DebugSize.height - p1.y;
	float p2y = AppDelegate::m_DebugSize.height - p2.y;

	//得到绘制的线段的GL坐标系的坐标
	CCPoint p3 = ccp(p1.x * AppDelegate::m_Scale + AppDelegate::m_OffsetX, p1y * AppDelegate::m_Scale);
	CCPoint p4 = ccp(p2.x * AppDelegate::m_Scale + AppDelegate::m_OffsetX, p2y * AppDelegate::m_Scale);
	
	//设置当前绘制颜色
	ccDrawColor4B((c >> 24 & 0xff), (c >> 16 & 0xff), (c >> 8 & 0xff), c & 0xff);
	
	//绘制线段
	ccDrawLine(p3, p4);

	//恢复颜色
	ccDrawColor4B(0xff, 0xff, 0xff, 0xff);
}
void CGameLayer::DrawRect1(const CCPoint& p1, const CCPoint& p2, int c)
{
	float p1y = AppDelegate::m_DebugSize.height - p1.y;
	float p2y = AppDelegate::m_DebugSize.height - p2.y;
	CCPoint p3 = ccp(p1.x * AppDelegate::m_Scale + AppDelegate::m_OffsetX, p1y * AppDelegate::m_Scale);
	CCPoint p4 = ccp(p2.x * AppDelegate::m_Scale + AppDelegate::m_OffsetX, p2y * AppDelegate::m_Scale);
	ccDrawColor4B((c >> 24 & 0xff), (c >> 16 & 0xff), (c >> 8 & 0xff), c & 0xff);
	ccDrawRect(p3, p4);
	ccDrawColor4B(0xff, 0xff, 0xff, 0xff);
}
void CGameLayer::DrawRect2(const CCPoint& p1, const CCPoint& p2, int c)
{
	float p1y = AppDelegate::m_DebugSize.height - p1.y;
	float p2y = AppDelegate::m_DebugSize.height - p2.y;
	CCPoint p3 = ccp(p1.x * AppDelegate::m_Scale + AppDelegate::m_OffsetX, p1y * AppDelegate::m_Scale);
	CCPoint p4 = ccp(p2.x * AppDelegate::m_Scale + AppDelegate::m_OffsetX, p2y * AppDelegate::m_Scale);
	ccColor4F cf
		=
	{
		(float)(c >> 24 & 0xff) / 255.0f,
		(float)(c >> 16 & 0xff) / 255.0f,
		(float)(c >> 8 & 0xff) / 255.0f,
		(float)(c & 0xff) / 255.0f
	};
	ccDrawSolidRect(p3, p4, cf);
}
void CGameLayer::DrawImage1(CCTexture2D* t,
							int sx, int sy, int sw, int sh,
							int dx, int dy, int dw, int dh)
{
	MyTexture* mt = (MyTexture*)t;
	mt->Draw(
		sx, sy, sw, sh,
		dx, dy, dw, dh);
}
void CGameLayer::DrawImage2(CCTexture2D* t,
							float angle,
							int dx, int dy, int dw, int dh)
{
	//如果没有精灵了就创建一些精灵
	if (m_CurSpriteIndex == m_Sprites.size())
	{
		for (int i = m_Sprites.size() * 2; i > 0; --i)
		{
			//通过默认的图像创建精灵
			CCSprite* sprite = CCSprite::create("Default/S_DEFAULT.PNG");

			//设置精灵作为本层的子节点
			addChild(sprite);

			//设置精灵不可见
			sprite->setVisible(false);

			//装入表中
			m_Sprites.push_back(sprite);
		}
	}

	//得到一个精灵
	CCSprite* s = m_Sprites[m_CurSpriteIndex++];

	//设置精灵的纹理
	s->setTexture(t);

	//得到精灵的缩放
	s->setScaleX((dw * AppDelegate::m_Scale) / 128.0f);
	s->setScaleY((dh * AppDelegate::m_Scale) / 128.0f);

	//得到精灵的旋转
	s->setRotation(angle);

	//得到精灵的位移
	s->setPosition(
		ccp(
		dx * AppDelegate::m_Scale + AppDelegate::m_OffsetX + dw * AppDelegate::m_Scale / 2.0f,
		AppDelegate::m_ReleaseSize.height - (dy * AppDelegate::m_Scale + dh * AppDelegate::m_Scale / 2.0f)
		));

	//设置精灵可见
	s->setVisible(true);
}
void CGameLayer::DrawString(int x, int y,
							int w, int h,
							int xn, int yn,
							const char* str)
{
	//初次加载稍慢
	MyTexture* ascii = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("Default/ASCII.PNG");

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

CGameLayer::_FILE_DATA CGameLayer::GetResourceFileData(const char* fn)
{
	_FILE_DATA fd = {};

	//得到文件的完整名称
	const char* afn = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(fn);
	if (!afn)
		return fd;

	//得到文件内容
	unsigned long file_size;
	unsigned char* file_data = CCFileUtils::sharedFileUtils()->getFileData(afn, "rb", &file_size);

	fd.fd = (char*)file_data;
	fd.fs = file_size;

	return fd;
}
const char* CGameLayer::GetRWDirectory()
{
	return m_RWDirectory;
}

void CGameLayer::PlayMusic(const char* fn)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(fn, true);
}
void CGameLayer::StopMusic()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
}
float CGameLayer::GetMusicVolume()
{
	return SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
}
void CGameLayer::SetMusicVolume(float v)
{
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(v);
}
void CGameLayer::PlayEffect(const char* fn)
{
	SimpleAudioEngine::sharedEngine()->playEffect(fn, false);
}
float CGameLayer::GetEffectVolume()
{
	return SimpleAudioEngine::sharedEngine()->getEffectsVolume();
}
void CGameLayer::SetEffectVolume(float v)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(v);
}

bool CGameLayer::LoadUI(int id, CUI* pUI)
{
	//检查id是否有重复
	for (int i = 0; i < (int)m_UI.size(); ++i)
	{
		if (m_UI[i]->m_ID == id)
			return false;
	}

	//设置id号
	pUI->m_ID = id;

	//设置层
	pUI->m_Layer = this;

	//装载入表
	m_UI.push_back(pUI);

	return true;
}

bool CGameLayer::ReleaseUI(int id)
{
	//得到指定id的UI
	int i = 0;
	for (; i < (int)m_UI.size(); ++i)
	{
		if (m_UI[i]->m_ID == id)
			break;
	}

	//释放
	if (i < (int)m_UI.size())
	{
		delete m_UI[i];
		m_UI.erase(m_UI.begin() + i);
		return true;
	}
	else
		return false;
}

CUI* CGameLayer::GetUI(int id)
{
	int i = 0;
	for (; i < (int)m_UI.size(); ++i)
	{
		if (m_UI[i]->m_ID == id)
			return m_UI[i];
	}
	return 0;
}

void CGameLayer::OnUIMessage(int id, int msg){}