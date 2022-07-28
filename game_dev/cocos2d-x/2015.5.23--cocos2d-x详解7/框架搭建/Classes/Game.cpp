#include "Game.h"
#include "AppDelegate.h"
#include "Button.h"

CGame::CGame()
{
	t0 = CCTextureCache::sharedTextureCache()->addImage("Game/00.PNG");
	t1 = CCTextureCache::sharedTextureCache()->addImage("Game/01.PNG");

	LoadUI(1, new CButton(CCRect(0, 0, 100, 80), "Game/return_i.PNG", "Game/return_n.PNG", "Game/return_d.PNG"));
}

void CGame::InputUp(CCPoint* p)
{
}

void CGame::Logic(float dt)
{
	static float a = 0.0f;
	DrawImage2(
		t1,
		a += 1.0f,
		100, 100, 200, 100);
}

void CGame::Output()
{
	DrawImage1(
		t0,
		0, 0, 512, 308,
		0, 0, AppDelegate::m_DebugSize.width, AppDelegate::m_DebugSize.height);
}

void CGame::OnUIMessage(int id, int msg)
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
					AppDelegate::SetCurLayer(0);
					break;
				}
			}
			break;
		}
	}
}