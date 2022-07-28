#include "Begin.h"
#include "GameEngine.h"
#include "TextButton.h"
#include "ImageButton.h"
#include "EditBox.h"
#include <iostream>

void CBegin::Init()
{
	LoadUI(new CEditBox("黑体", RGB(255, 0, 0), 32, "127.0.0.1", 0, 0, 320, 30), "ip");
	LoadUI(new CEditBox("隶书", RGB(255, 0, 255), 16, 0, 0, 50, 160, 20), "nc");
	LoadUI(new CTextButton("登陆", 300, 300, 50, 30), "dl");
}

void CBegin::Enter()
{

}

void CBegin::OutputRun()
{
}

void CBegin::InputRun()
{
}

void CBegin::LogicRun()
{
}

void CBegin::Quit()
{
}

void CBegin::OnUIMessage(int message, const char* id)
{
	if (message == _TBM_CLICKED)
	{
		if (strcmp(id, "dl") == 0)
		{
			CEditBox* eb1 = (CEditBox*)GetUI("ip");
			CEditBox* eb2 = (CEditBox*)GetUI("nc");
			if (strlen(eb1->GetText()) > 0 && strlen(eb2->GetText()) > 0)
			{
				//得到昵称
				m_Nick_Name = eb2->GetText();

				//连接
				CGameEngine::GetGE()->GetTcpClient()->ConnectByIP(
					eb1->GetText(),
					12345,
					10, 10, 10);
			}
		}
	}
}

void CBegin::OnNetEvent(_TC_NET_EVENT* ptne)
{
	switch (ptne->type)
	{
	case _TCNE_CONNECT_FAIL:
		{
			Beep(256, 100);
			break;
		}
	case _TCNE_CONNECT_OK:
		{
			//发送1号协议
			_C_S_GP1 csgp1;
			strcpy_s(csgp1.nick_name, 32, m_Nick_Name.c_str());
			CGameEngine::GetGE()->GetTcpClient()->SendData((char*)&csgp1, sizeof(csgp1));
			break;
		}
	case _TCNE_S_DISCONNECT:
	case _TCNE_C_DISCONNECT:
	case _TCNE_E_DISCONNECT:
		{
			all_player.clear();
			break;
		}
	case _TCNE_DATA:
		{
			_GAME_PROTOCOL* pgp = (_GAME_PROTOCOL*)ptne->data;
			switch (pgp->id)
			{
			case _NICK_NAME_LAWLESS:
				{
					Beep(512, 100);
					CGameEngine::GetGE()->GetTcpClient()->Disconnect();
					break;
				}
			case _NICK_NAME_LEGALITY:
				{
					_S_C_GP3* p = (_S_C_GP3*)ptne->data;

					//初始化游戏地图
					for (int i = 0; i < _GAME_MAP_S; ++i)
						map[i] = p->map[i];

					//得到所有玩家的信息
					for (int i = 0; i < p->player_num; ++i)
					{
						std::string str = p->player[i].nick_name;
						POINT pos = {p->player[i].x, p->player[i].y};
						all_player.insert(std::pair<std::string, POINT>(str, pos));
					}

					CGameEngine::GetGE()->SetCurScene("游戏场景");

					break;
				}
			}
			break;
		}
	}
}