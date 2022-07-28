#include "GameOutput.h"
#include <io.h>

#pragma comment(lib, "msimg32.lib")

CGameOutput::CGameOutput(HWND hWnd)
{
	//得到窗口
	m_hWnd = hWnd;

	//得到客户区尺寸
	RECT r;
	GetClientRect(m_hWnd, &r);
	m_ClientW = r.right - r.left;
	m_ClientH = r.bottom - r.top;

	//得到主绘图设备
	m_MainDC = GetDC(m_hWnd);

	HBITMAP hbmp = 0;

	//创建后备绘图设备
	m_BackDC = CreateCompatibleDC(m_MainDC);
	hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientW, m_ClientH);
	DeleteObject(SelectObject(m_BackDC, hbmp));
	DeleteObject(hbmp);
	SetStretchBltMode(m_BackDC, HALFTONE);

	//设置文字背景色透明
	SetBkMode(m_BackDC, TRANSPARENT);

	//创建镜像绘图设备
	m_MirrorDC = CreateCompatibleDC(m_MainDC);
	hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientW, m_ClientH);
	DeleteObject(SelectObject(m_MirrorDC, hbmp));
	DeleteObject(hbmp);
}

CGameOutput::~CGameOutput()
{
	//释放字体
	for (int i = 0; i < m_Fonts.Length(); ++i)
		DeleteObject(m_Fonts.At(i)->data);

	//释放位图
	for (int i = 0; i < m_Bitmaps.Length(); ++i)
		DeleteDC(m_Bitmaps.At(i)->data);

	//删除镜像绘图设备
	DeleteDC(m_MirrorDC);

	//删除后备绘图设备
	DeleteDC(m_BackDC);

	//释放主绘图设备
	ReleaseDC(m_hWnd, m_MainDC);
}

void CGameOutput::Begin()
{
	BitBlt(m_BackDC, 0, 0, m_ClientW, m_ClientH, 0, 0, 0, WHITENESS);
}

void CGameOutput::End()
{
	BitBlt(m_MainDC, 0, 0, m_ClientW, m_ClientH, m_BackDC, 0, 0, SRCCOPY);
}

void CGameOutput::DrawDot(int x, int y, int c)
{
	SetPixel(m_BackDC, x, y, c);
}

void CGameOutput::DrawLine(int x1, int y1, int x2, int y2, int c)
{
	HPEN newpen = 0, oldpen = 0;

	if (c != RGB(0, 0, 0))
	{
		newpen = CreatePen(PS_SOLID, 1, c);
		oldpen = (HPEN)SelectObject(m_BackDC, newpen);
	}

	MoveToEx(m_BackDC, x1, y1, 0);
	LineTo(m_BackDC, x2, y2);

	if (c != RGB(0, 0, 0))
	{
		SelectObject(m_BackDC, oldpen);
		DeleteObject(newpen);
	}
}

void CGameOutput::DrawRectangle1(int x1, int y1, int x2, int y2, int c)
{
	HPEN newpen = 0, oldpen = 0;

	if (c != RGB(0, 0, 0))
	{
		newpen = CreatePen(PS_SOLID, 1, c);
		oldpen = (HPEN)SelectObject(m_BackDC, newpen);
	}

	POINT p[]
	=
	{
		{x1, y1},
		{x2, y1},
		{x2, y2},
		{x1, y2},
		{x1, y1}
	};
	for (int i = 0; i < 4; ++i)
	{
		MoveToEx(m_BackDC, p[i].x,  p[i].y, 0);
		LineTo(m_BackDC, p[i + 1].x,  p[i + 1].y);
	}

	if (c != RGB(0, 0, 0))
	{
		SelectObject(m_BackDC, oldpen);
		DeleteObject(newpen);
	}
}

void CGameOutput::DrawRectangle2(int x1, int y1, int x2, int y2, int pc, int bc)
{
	HPEN newpen = 0, oldpen = 0;
	HBRUSH newbrush = 0, oldbrush = 0;

	if (pc != RGB(0, 0, 0))
	{
		newpen = CreatePen(PS_SOLID, 1, pc);
		oldpen = (HPEN)SelectObject(m_BackDC, newpen);
	}

	if (bc != RGB(0xff, 0xff, 0xff))
	{
		newbrush = CreateSolidBrush(bc);
		oldbrush = (HBRUSH)SelectObject(m_BackDC, newbrush);
	}

	Rectangle(m_BackDC, x1, y1, x2, y2);

	if (pc != RGB(0, 0, 0))
	{
		SelectObject(m_BackDC, oldpen);
		DeleteObject(newpen);
	}

	if (bc != RGB(0xff, 0xff, 0xff))
	{
		SelectObject(m_BackDC, oldbrush);
		DeleteObject(newbrush);
	}
}

void CGameOutput::DrawEllipse1(int x1, int y1, int x2, int y2, int c)
{
	HPEN newpen = 0, oldpen = 0;
	HBRUSH newbrush = 0, oldbrush = 0;

	if (c != RGB(0, 0, 0))
	{
		newpen = CreatePen(PS_SOLID, 1, c);
		oldpen = (HPEN)SelectObject(m_BackDC, newpen);
	}

	//得到操作系统预定义好的一些GDI对象，里面就有空画
	//刷，从本函数得到的GDI对象不用删除
	newbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oldbrush = (HBRUSH)SelectObject(m_BackDC, newbrush);

	Ellipse(m_BackDC, x1, y1, x2, y2);

	SelectObject(m_BackDC, oldbrush);

	if (c != RGB(0, 0, 0))
	{
		SelectObject(m_BackDC, oldpen);
		DeleteObject(newpen);
	}
}

void CGameOutput::DrawEllipse2(int x1, int y1, int x2, int y2, int pc, int bc)
{
	HPEN newpen = 0, oldpen = 0;
	HBRUSH newbrush = 0, oldbrush = 0;

	if (pc != RGB(0, 0, 0))
	{
		newpen = CreatePen(PS_SOLID, 1, pc);
		oldpen = (HPEN)SelectObject(m_BackDC, newpen);
	}

	if (bc != RGB(0xff, 0xff, 0xff))
	{
		newbrush = CreateSolidBrush(bc);
		oldbrush = (HBRUSH)SelectObject(m_BackDC, newbrush);
	}

	Ellipse(m_BackDC, x1, y1, x2, y2);

	if (pc != RGB(0, 0, 0))
	{
		SelectObject(m_BackDC, oldpen);
		DeleteObject(newpen);
	}

	if (bc != RGB(0xff, 0xff, 0xff))
	{
		SelectObject(m_BackDC, oldbrush);
		DeleteObject(newbrush);
	}
}

bool CGameOutput::LoadBmp(const char* fn)
{
	//如果位图映射中已经有fn这个名字了那么
	//表示该名字已经被使用那么我们就不能用
	//这个名字了返回失败
	std::string str = fn;
	if (m_Bitmaps.Find(str))
		return false;

	//加载位图文件
	HBITMAP hbmp = (HBITMAP)LoadImageA(
		0,
		str.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE);
	if (!hbmp)
		return false;

	//创建兼容设备并选入位图文件
	HDC hdc = CreateCompatibleDC(m_MainDC);
	DeleteObject(SelectObject(hdc, hbmp));
	DeleteObject(hbmp);

	return m_Bitmaps.Insert(str, hdc);
}

int CGameOutput::LoadDirectory(const char* dn)
{
	//得到当前要遍历的目录字符串
	std::string dir = dn;

	//目录字符串添加*.*，这样才表
	//示要在这个目录中去查找所有的
	//文件、子目录
	dir += "\\*.*";

	//设置返回值
	int r = 0;
	
	_finddata_t fd;
	intptr_t i = _findfirst(dir.c_str(), &fd);
	if (i != -1)
	{
		do
		{
			//找到了目录
			if (fd.attrib & _A_SUBDIR)
			{
				//找到了子目录
				if (strcmp(fd.name, ".") != 0 && strcmp(fd.name, "..") != 0)
				{
					std::string dirname = dn;
					dirname += "\\";
					dirname += fd.name;
					r += LoadDirectory(dirname.c_str());
				}
			}
			//找到了文件
			else
			{
				//strrchr(char* s,char c)得到c在
				//s中最后一次出现的地址
				char* p = strrchr(fd.name, '.');
				if (p)
				{
					if ((p[1] == 'b' || p[1] == 'B') && (p[2] == 'm' || p[2] == 'M') && (p[3] == 'p' || p[3] == 'P'))
					{
						std::string filename = dn;
						filename += "\\";
						filename += fd.name;
						if (LoadBmp(filename.c_str()))
							r += 1;
					}
				}
			}

		} while (0 == _findnext(i, &fd));
	}

	return r;
}

bool CGameOutput::ReleaseBmp(const char* fn)
{
	std::string str = fn;
	CMap<std::string, HDC>::PAIR* p = m_Bitmaps.Find(str);
	if (!p)
		return false;

	DeleteDC(p->data);
	m_Bitmaps.Erase(str);

	return true;
}

bool CGameOutput::GetBmpWH(const char* fn, int* w, int* h)
{
	std::string str = fn;
	CMap<std::string, HDC>::PAIR* p = m_Bitmaps.Find(str);
	if (!p)
		return false;

	HBITMAP hbmp = (HBITMAP)GetCurrentObject(p->data, OBJ_BITMAP);
	BITMAP bmp;
	GetObject(hbmp, sizeof(bmp), &bmp);
	*w = bmp.bmWidth;
	*h = bmp.bmHeight;

	return true;
}

bool CGameOutput::DrawBmp1(const char* fn,
						   int sx, int sy, int sw, int sh,
						   int dx, int dy, int dw, int dh,
						   int m)
{
	if (m < _MIRROR_NONE || m > _MIRROR_TBLR)
		return false;

	std::string str = fn;
	CMap<std::string, HDC>::PAIR* p = m_Bitmaps.Find(str);
	if (!p)
		return false;

	switch (m)
	{
	case _MIRROR_NONE:
		{
			StretchBlt(m_BackDC, dx, dy, dw, dh, p->data, sx, sy, sw, sh, SRCCOPY);
			break;
		}
	case _MIRROR_LR:
		{
			StretchBlt(m_BackDC, dx + dw - 1, dy, -dw, dh, p->data, sx, sy, sw, sh, SRCCOPY);
			break;
		}
	case _MIRROR_TB:
		{
			StretchBlt(m_BackDC, dx, dy + dh - 1, dw, -dh, p->data, sx, sy, sw, sh, SRCCOPY);
			break;
		}
	case _MIRROR_TBLR:
		{
			StretchBlt(m_BackDC, dx + dw - 1, dy + dh - 1, -dw, -dh, p->data, sx, sy, sw, sh, SRCCOPY);
			break;
		}
	}

	return true;
}

bool CGameOutput::DrawBmp2(const char* fn,
						   int sx, int sy, int sw, int sh,
						   int dx, int dy, int dw, int dh,
						   int tc,
						   int m)
{
	if (m < _MIRROR_NONE || m > _MIRROR_TBLR)
		return false;

	std::string str = fn;
	CMap<std::string, HDC>::PAIR* p = m_Bitmaps.Find(str);
	if (!p)
		return false;

	switch (m)
	{
	case _MIRROR_NONE:
		{
			TransparentBlt(m_BackDC, dx, dy, dw, dh, p->data, sx, sy, sw, sh, tc);
			return true;
		}
	case _MIRROR_LR:
		{
			StretchBlt(m_MirrorDC, 0 + dw - 1, 0, -dw, dh, p->data, sx, sy, sw, sh, SRCCOPY);
			break;
		}
	case _MIRROR_TB:
		{
			StretchBlt(m_MirrorDC, 0, 0 + dh - 1, dw, -dh, p->data, sx, sy, sw, sh, SRCCOPY);
			break;
		}
	case _MIRROR_TBLR:
		{
			StretchBlt(m_MirrorDC, 0 + dw - 1, 0 + dh - 1, -dw, -dh, p->data, sx, sy, sw, sh, SRCCOPY);
			break;
		}
	}

	TransparentBlt(m_BackDC, dx, dy, dw, dh, m_MirrorDC, 0, 0, dw, dh, tc);

	return true;
}

bool CGameOutput::LoadFont(int w,
						   int h,
						   int we,
						   bool i,
						   bool u,
						   bool s,
						   const char* f,
						   const char* id)
{
	std::string str = id;
	if (m_Fonts.Find(str))
		return false;

	HFONT font = CreateFontA(
		h,
		w,
		0,
		0,
		we,
		i,
		u,
		s,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		f);
	if (!font)
		return false;

	return m_Fonts.Insert(str, font);
}

bool CGameOutput::ReleaseFont(const char* id)
{
	std::string str = id;
	CMap<std::string, HFONT>::PAIR* p = m_Fonts.Find(str);
	if (!p)
		return false;

	DeleteObject(p->data);
	m_Fonts.Erase(str);

	return true;
}

bool CGameOutput::DrawText1(const char* id,
							int x, int y,
							const char* t,
							int c)
{
	if (id == 0)
	{
		int old_color = 0;
		if (c != RGB(0, 0, 0))
			old_color = SetTextColor(m_BackDC, c); //本函数返回之前的文字颜色

		TextOutA(m_BackDC, x, y, t, (int)strlen(t));

		if (c != RGB(0, 0, 0))
			SetTextColor(m_BackDC, old_color);
	}
	else
	{
		std::string str = id;
		CMap<std::string, HFONT>::PAIR* p = m_Fonts.Find(str);
		if (!p)
			return false;

		HFONT old_font = (HFONT)SelectObject(m_BackDC, p->data);

		int old_color = 0;
		if (c != RGB(0, 0, 0))
			old_color = SetTextColor(m_BackDC, c); //本函数返回之前的文字颜色

		TextOutA(m_BackDC, x, y, t, (int)strlen(t));

		if (c != RGB(0, 0, 0))
			SetTextColor(m_BackDC, old_color);

		SelectObject(m_BackDC, old_font);
	}

	return true;
}

bool CGameOutput::DrawText2(const char* id,
							int x, int y, int w, int h,
							const char* t,
							int c)
{
	if (id == 0)
	{
		int old_color = 0;
		if (c != RGB(0, 0, 0))
			old_color = SetTextColor(m_BackDC, c); //本函数返回之前的文字颜色

		RECT r = {x, y, x + w, y + h};
		DrawTextA(m_BackDC, t, (int)strlen(t), &r, DT_WORDBREAK);

		if (c != RGB(0, 0, 0))
			SetTextColor(m_BackDC, old_color);
	}
	else
	{
		std::string str = id;
		CMap<std::string, HFONT>::PAIR* p = m_Fonts.Find(str);
		if (!p)
			return false;

		HFONT old_font = (HFONT)SelectObject(m_BackDC, p->data);

		int old_color = 0;
		if (c != RGB(0, 0, 0))
			old_color = SetTextColor(m_BackDC, c); //本函数返回之前的文字颜色

		RECT r = {x, y, x + w, y + h};
		DrawTextA(m_BackDC, t, (int)strlen(t), &r, DT_WORDBREAK);

		if (c != RGB(0, 0, 0))
			SetTextColor(m_BackDC, old_color);

		SelectObject(m_BackDC, old_font);
	}

	return true;
}

bool CGameOutput::DrawText3(const char* id,
							int x, int y, int w, int h,
							const char* t,
							int c)
{
	if (id == 0)
	{
		int old_color = 0;
		if (c != RGB(0, 0, 0))
			old_color = SetTextColor(m_BackDC, c); //本函数返回之前的文字颜色

		RECT r = {x, y, x + w, y + h};
		DrawTextA(m_BackDC, t, (int)strlen(t), &r, DT_WORDBREAK | DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		if (c != RGB(0, 0, 0))
			SetTextColor(m_BackDC, old_color);
	}
	else
	{
		std::string str = id;
		CMap<std::string, HFONT>::PAIR* p = m_Fonts.Find(str);
		if (!p)
			return false;

		HFONT old_font = (HFONT)SelectObject(m_BackDC, p->data);

		int old_color = 0;
		if (c != RGB(0, 0, 0))
			old_color = SetTextColor(m_BackDC, c); //本函数返回之前的文字颜色

		RECT r = {x, y, x + w, y + h};
		DrawTextA(m_BackDC, t, (int)strlen(t), &r, DT_WORDBREAK | DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		if (c != RGB(0, 0, 0))
			SetTextColor(m_BackDC, old_color);

		SelectObject(m_BackDC, old_font);
	}

	return true;
}