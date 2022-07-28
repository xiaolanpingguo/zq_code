#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_

#include <windows.h>
#include <string>
#include "Map.h"

#define _MIRROR_NONE 0 //不镜像
#define _MIRROR_LR 1 //左右镜像
#define _MIRROR_TB 2 //上下镜像
#define _MIRROR_TBLR 3 //上下左右镜像

class CGameOutput
{
	HWND m_hWnd;
	int m_ClientW;
	int m_ClientH;
	HDC m_MainDC;
	HDC m_BackDC;
	HDC m_MirrorDC;
	CMap<std::string, HDC> m_Bitmaps;
	CMap<std::string, HFONT> m_Fonts;

public:
	CGameOutput(HWND hWnd);
	~CGameOutput();

	void Begin();
	void End();

	//图元绘制
	void DrawDot(int x, int y, int c = RGB(0, 0, 0));
	void DrawLine(int x1, int y1, int x2, int y2, int c = RGB(0, 0, 0));
	void DrawRectangle1(int x1, int y1, int x2, int y2, int c = RGB(0, 0, 0));
	void DrawRectangle2(int x1, int y1, int x2, int y2, int pc = RGB(0, 0, 0), int bc = RGB(0xff, 0xff, 0xff));
	void DrawEllipse1(int x1, int y1, int x2, int y2, int c = RGB(0, 0, 0));
	void DrawEllipse2(int x1, int y1, int x2, int y2, int pc = RGB(0, 0, 0), int bc = RGB(0xff, 0xff, 0xff));

	//位图绘制
	bool LoadBmp(const char* fn);
	int LoadDirectory(const char* dn);
	bool ReleaseBmp(const char* fn);
	bool GetBmpWH(const char* fn, int* w, int* h);
	bool DrawBmp1(
		const char* fn,
		int sx, int sy, int sw, int sh, //源矩形
		int dx, int dy, int dw, int dh, //目标矩形
		int m = _MIRROR_NONE); //镜像
	bool DrawBmp2(
		const char* fn,
		int sx, int sy, int sw, int sh, //源矩形
		int dx, int dy, int dw, int dh, //目标矩形
		int tc = RGB(0, 255, 0), //透明色
		int m = _MIRROR_NONE); //镜像

	//文字绘制
	bool LoadFont(
		int w, //宽
		int h, //高
		int we, //粗细
		bool i, //是否为斜体
		bool u, //是否带下划线
		bool s, //是否带穿越线
		const char* f, //外观名称
		const char* id); //id号
	bool ReleaseFont(const char* id);
	bool DrawText1(
		const char* id, //文字id号
		int x, int y, //文字区域左上角坐标
		const char* t, //字符串
		int c = RGB(0, 0, 0)); //颜色
	bool DrawText2( //左上角绘制
		const char* id, //文字id号
		int x, int y, int w, int h, //文字矩形
		const char* t, //字符串
		int c = RGB(0, 0, 0)); //颜色
	bool DrawText3( //居中绘制
		const char* id, //文字id号
		int x, int y, int w, int h, //文字矩形
		const char* t, //字符串
		int c = RGB(0, 0, 0)); //颜色
};

#endif