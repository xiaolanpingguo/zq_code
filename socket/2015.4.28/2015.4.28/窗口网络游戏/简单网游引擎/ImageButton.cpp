#include "ImageButton.h"
#include "GameEngine.h"
#include "Scene.h"

CImageButton::CImageButton(const char* no_enable,
						   const char* cursor_out,
						   const char* cursor_in_up,
						   const char* cursor_in_down,
						   int X, int Y, int W, int H, bool Visible, bool Enable)
						   :
CTextButton("", X, Y, W, H, Visible, Enable),
m_NoEnable(no_enable),
m_CursorOut(cursor_out),
m_CursorInUp(cursor_in_up),
m_CursorInDown(cursor_in_down)
{
	CGameEngine::GetGE()->GetOutput()->LoadBmp(no_enable);
	CGameEngine::GetGE()->GetOutput()->LoadBmp(cursor_out);
	CGameEngine::GetGE()->GetOutput()->LoadBmp(cursor_in_up);
	CGameEngine::GetGE()->GetOutput()->LoadBmp(cursor_in_down);

	CGameEngine::GetGE()->GetOutput()->GetBmpWH(no_enable, &m_NoEnable_W, &m_NoEnable_H);
	CGameEngine::GetGE()->GetOutput()->GetBmpWH(cursor_out, &m_CursorOut_W, &m_CursorOut_H);
	CGameEngine::GetGE()->GetOutput()->GetBmpWH(cursor_in_up, &m_CursorInUp_W, &m_CursorInUp_H);
	CGameEngine::GetGE()->GetOutput()->GetBmpWH(cursor_in_down, &m_CursorInDown_W, &m_CursorInDown_H);
}

void CImageButton::Render(bool Enable)
{
	const char* str = 0;

	int w, h;
	if (Enable)
	{
		switch (m_State)
		{
		case _CURSOR_OUT:
			{
				str = m_CursorOut.c_str();
				w = m_CursorOut_W;
				h = m_CursorOut_H;
				break;
			}
		case _CURSOR_IN_UP:
			{
				str = m_CursorInUp.c_str();
				w = m_CursorInUp_W;
				h = m_CursorInUp_H;
				break;
			}
		case _CURSOR_IN_DOWN:
			{
				str = m_CursorInDown.c_str();
				w = m_CursorInDown_W;
				h = m_CursorInDown_H;
				break;
			}
		}
	}
	else
	{
		str = m_NoEnable.c_str();
		w = m_NoEnable_W;
		h = m_NoEnable_H;
	}

	CGameEngine::GetGE()->GetOutput()->DrawBmp1(
		str,
		0, 0, w, h,
		m_X, m_Y, m_W, m_H);
}