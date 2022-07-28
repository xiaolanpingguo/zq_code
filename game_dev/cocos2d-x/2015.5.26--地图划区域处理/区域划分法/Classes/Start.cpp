#include "Start.h"

CStart::CStart()
{
	t0 = CCTextureCache::sharedTextureCache()->addImage("Start/00.PNG");

	LoadUI(1, new CButton(CCRect(0, 0, 100, 80), "Start/start_i.PNG", "Start/start_n.PNG", "Start/start_d.PNG"));
	LoadUI(2, new CButton(CCRect(0, 100, 100, 80), "Start/quit_i.PNG", "Start/quit_n.PNG", "Start/quit_d.PNG"));

	//GetUI(1)->m_Visible = false;
	//GetUI(2)->m_Active = false;
}

void CStart::InputUp(CCPoint* p)
{
	
}

void CStart::Output()
{
	DrawImage1(
		t0,
		0, 0, 576, 360,
		0, 0, AppDelegate::m_DebugSize.width, AppDelegate::m_DebugSize.height);
}

void CStart::OnUIMessage(int id, int msg)
{
	switch (msg)
	{
		//当前层中有按钮被按下
	case _BUTTON_CLICK:
		{
			switch (id)
			{
			case 1:
				{
					AppDelegate::SetCurLayer(1);
					break;
				}
			case 2:
				{
					Quit();
					break;
				}
			}
			break;
		}
	}
}