#include "ButtonUI.h"
#include "Scene.h"
#include "GameEngine.h"

CButtonUI::CButtonUI(const char* t, int x, int y, int w, int h, bool v, bool a)
:
m_In(false),
CUI(x, y, w, h, v, a),
m_Text(t)
{}

void CButtonUI::ActRender()
{
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();

	pGO->DrawRectangle2(
		m_X, m_Y, m_X + m_W, m_Y + m_H,
		RGB(0, 0, 0),
		m_In ? RGB(255, 255, 255) : RGB(127, 127, 127));

	pGO->DrawString3(
		0,
		m_X, m_Y, m_W, m_H,
		m_Text.c_str(),
		RGB(0, 0, 0));
}

void CButtonUI::UnactRender()
{
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();

	pGO->DrawRectangle2(
		m_X, m_Y, m_X + m_W, m_Y + m_H,
		RGB(0, 0, 0),
		RGB(127, 127, 127));

	pGO->DrawString3(
		0,
		m_X, m_Y, m_W, m_H,
		m_Text.c_str(),
		RGB(75, 75, 75));
}

void CButtonUI::OnMsg(int Msg, int p1, int p2)
{
	switch (Msg)
	{
	case _UIM_C_ENTER: m_In = true; break;
	case _UIM_C_QUIT: m_In = false; break;
	case _UIM_C_LBD_IN:
		{
			m_Scene->OnUIMsg(m_Name.c_str(), _BUTTON_CLICK);
			break;
		}
	}
}

void CButtonUI::SetText(const char* t)
{
	m_Text = t;
}

const char* CButtonUI::GetText()
{
	return m_Text.c_str();
}