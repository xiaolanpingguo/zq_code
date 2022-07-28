#include "UI.h"

CUI::CUI(int X, int Y, int W, int H, bool Visible, bool Enable)
:
m_X(X),
m_Y(Y),
m_W(W),
m_H(H),
m_Visible(Visible),
m_Enable(Enable),
m_Scene(0)
{}

CUI::~CUI()
{}

void CUI::SetRect(int X, int Y, int W, int H)
{
	m_X = X;
	m_Y = Y;
	m_W = W;
	m_H = H;
}

void CUI::GetRect(int* X, int* Y, int* W, int* H)
{
	*X = m_X;
	*Y = m_Y;
	*W = m_W;
	*H = m_H;
}

void CUI::SetVisible(bool Visible)
{
	m_Visible = Visible;
}

bool CUI::GetVisible()
{
	return m_Visible;
}

void CUI::SetEnable(bool Enable)
{
	m_Enable = Enable;
}

bool CUI::GetEnable()
{
	return m_Enable;
}

void CUI::Init(){}
void CUI::Enter(){}
void CUI::Quit(){}
void CUI::End(){}
void CUI::OnEvent(int Event, int X, int Y){}
void CUI::Render(bool Enable){}