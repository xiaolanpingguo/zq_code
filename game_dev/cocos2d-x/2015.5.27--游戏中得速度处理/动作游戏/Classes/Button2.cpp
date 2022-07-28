#include "Button2.h"
#include "GameLayer.h"

CButton2::CButton2(const CCRect& r,
				   const char* inactive_image,
				   const char* normal_image,
				   const char* down_image)
				   :
CButton(r, inactive_image, normal_image, down_image)
{}

void CButton2::Logic()
{
	if (click_down)
		m_Layer->OnUIMessage(m_ID, _BUTTON2_DOWN);
}

void CButton2::OnMessage(int e, int x, int y)
{
	switch (e)
	{
	case _UE_IN_DOWN:
		{
			click_down = true;
			break;
		}
	case _UE_IN_UP:
	case _UE_OUT_UP:
		{
			if (click_down)
				click_down = false;
			break;
		}
	}
}