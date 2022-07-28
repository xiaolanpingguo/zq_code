#include "Button.h"
#include "GameLayer.h"

CButton::CButton(const CCRect& r,
				 const char* inactive_image,
				 const char* normal_image,
				 const char* down_image)
				 :
CUI(r),
inactive(CCTextureCache::sharedTextureCache()->addImage(inactive_image)),
normal(CCTextureCache::sharedTextureCache()->addImage(normal_image)),
down(CCTextureCache::sharedTextureCache()->addImage(down_image)),
click_down(false)
{}

void CButton::Enter()
{
	click_down = false;
}

void CButton::Render()
{
	if (m_Active)
	{
		if (click_down)
		{
			m_Layer->DrawImage1(
				down,
				0, 0, down->getContentSize().width, down->getContentSize().height,
				m_Rect.origin.x, m_Rect.origin.y, m_Rect.size.width, m_Rect.size.height);
		}
		else
		{
			m_Layer->DrawImage1(
				normal,
				0, 0, normal->getContentSize().width, normal->getContentSize().height,
				m_Rect.origin.x, m_Rect.origin.y, m_Rect.size.width, m_Rect.size.height);
		}
	}
	else
	{
		m_Layer->DrawImage1(
			inactive,
			0, 0, inactive->getContentSize().width, inactive->getContentSize().height,
			m_Rect.origin.x, m_Rect.origin.y, m_Rect.size.width, m_Rect.size.height);
	}
}

void CButton::OnMessage(int e, int x, int y)
{
	switch (e)
	{
	case _UE_IN_DOWN:
		{
			click_down = true;
			break;
		}
	case _UE_IN_UP:
		{
			if (click_down)
				m_Layer->OnUIMessage(m_ID, _BUTTON_CLICK);
			click_down = false;

			break;
		}
	case _UE_OUT_UP:
		{
			click_down = false;
			break;
		}
	}
}