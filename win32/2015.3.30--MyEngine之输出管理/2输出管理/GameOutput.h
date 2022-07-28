#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_
#include <windows.h>
#include <string>
#include <map>

class CGameOutput
{
	HWND m_hWnd;//窗口
	int  m_iClientW;//客户区宽
	int  m_iClientH;//客户区高
	HDC  m_MainDC;//主设备
	HDC  m_BackDC;//后备设备
	std::map<std::string,HDC> m_Bmp;//位图映射表
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

	bool DrawBmp(//绘制位图
		const char* fn,
		int dx,int dy,int dw,int dh,int sx,int sy);
};

#endif