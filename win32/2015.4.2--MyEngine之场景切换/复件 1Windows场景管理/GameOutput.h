#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_
#include <windows.h>
#include <string>
#include <map>

#define _MIRROR_NONE 0 //不镜像
#define _MIRROR_LR   1 //左右镜像
#define _MIRROR_TB   2 //上下镜像
#define _MIRROR_LRTB 3 //左右上下镜像

class CGameOutput
{
	HWND m_hWnd;//窗口
	int  m_iClientW;//客户区宽
	int  m_iClientH;//客户区高
	HDC  m_MainDC;//主设备
	HDC  m_BackDC;//后备设备
	HDC  m_MirrorDC;//镜像设备
	std::map<std::string,HDC> m_Bmp;//位图映射表
	std::map<std::string,HFONT> m_Font;//字体映射
public:
	CGameOutput(HWND hWnd);
	~CGameOutput();

	//开始绘制,结束绘制
	void Begin();
	void End();

	//图元相关函数
	void DrawLine(//画线
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int c = RGB(0,0,0),
		int w = 1);

	void DrawRectangle1(//画空心矩形
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int c = RGB(0,0,0));

	void DrawRectangle2(//画实心矩形
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int pc = RGB(0,0,0),
		unsigned int bc = RGB(255,255,255));

	void DrawEllipse1(//画空心椭圆
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int c = RGB(0,0,0));

	void DrawEllipse2(//画实心椭圆
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int pc = RGB(0,0,0),
		unsigned int bc = RGB(255,255,255));

	//位图相关
	int LoadDirectory(const char* dn);//加载文件夹下面的所有位图(包括子目录)

	bool LoadBmp(const char* fn);//加载位图

	bool ReleaseBmp(const char* fn);//释放位图

	bool DrawBmp1(//绘制透明位图
		const char* fn,
		int dx,int dy,int dw,int dh,int sx,int sy,
		char m = _MIRROR_NONE,
		unsigned int tc = RGB(0,255,0));

	bool  DrawBmp2(//绘制位图
		const char* fn,
		int dx,int dy,int dw,int dh,int sx,int sy,
		char m = _MIRROR_NONE);

	bool LoadFont(
		const char* id,//字体ID
		int w = 0,//字体宽
		int h = 0,//字体高
		int we = 400,//字体粗细
		bool i = false,//是否为斜体
		bool u = false,//是否有下划线
		bool s = false,//是否有穿越线
		const char* fn = "宋体");//字体外观名称

	bool ReleaseFont(const char* id);

	bool DrawString1(//绘制单行文字
		const char* id,//字体,可以为0
		int x,
		int y,
		const char* t,//文字
		unsigned int c);//颜色

	bool DrawString2(//绘制多行文字
		const char* id,
		int x,
		int y,
		int w,
		int h,
		const char* t,
		unsigned int c);
};

#endif