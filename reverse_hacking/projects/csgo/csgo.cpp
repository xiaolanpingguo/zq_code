#include "csgo.h"
#include "csgo_def.h"
#include "r3/log.h"
#include "r3/utils.h"
#include "r3/render_manager.h"
#include "r3/process_mamager.h"
#include "r3/imgui/imgui_impl_win32.h"
#include "r3/imgui/imgui.h"
#include <Psapi.h>

static constexpr const std::wstring_view CSGO_CLIENT_DLL_NAME = L"client.dll";
static constexpr const std::wstring_view CSGO_SERVER_DLL_NAME = L"server.dll";
static constexpr const std::wstring_view CSGO_ENGINE_DLL_NAME = L"engine.dll";
static constexpr const std::wstring_view CSGO_WINDOW_TITLE_NAME1 = L"Counter-Strike: Global Offensive - Direct3D 9";
static constexpr const std::wstring_view CSGO_WINDOW_TITLE_NAME2 = L"Counter-Strike: Global Offensive";
static constexpr const std::wstring_view CSGO_PROCESS_NAME = L"csgo.exe";

std::atomic<bool> CSGO::m_stop = false;
CSGO::CSGO()
	: m_appInstance(nullptr)
	, m_gameWnd(nullptr)
	, m_mainWnd(nullptr)
	, m_gameHandle(nullptr)
	, m_gamePid(0)
	, m_esp(true)
	, m_aimbot(false)
	, m_renderManager(new RenderManager())
{
	m_localPlayer = nullptr;
}

CSGO::~CSGO()
{
	delete m_renderManager;
}

bool CSGO::init()
{
    /*if (!getGameProcess())
    {
        MessageBox(nullptr, TEXT("获取游戏窗口失败"), TEXT("提示"), MB_OK);
        return false;
    }

    if (!initGameModule())
    {
        MessageBox(nullptr, TEXT("初始化游戏模块失败"), TEXT("提示"), MB_OK);
        return false;
    }*/

    RenderConfig config
    {
        std::bind(&CSGO::gameDraw, this), 800, 600, true, L"csgo"
    };

	if (!m_renderManager->init(config))
	{
        MessageBox(nullptr, TEXT("render manager init failed"), TEXT("error"), MB_OK);
        return false;
	}

	return true;
}

bool CSGO::isRunning()
{
	return !m_stop;
}

bool CSGO::initGameModule()
{
	if (!Utils::getModule(m_gamePid, CSGO_CLIENT_DLL_NAME, &m_clientModule))
	{
		LOG_INFO(L"get module: {} faild!\n", CSGO_CLIENT_DLL_NAME);
		return false;
	}

	if (!Utils::getModule(m_gamePid, CSGO_SERVER_DLL_NAME, &m_serverModule))
	{
		LOG_INFO(L"get module: {} faild!\n", CSGO_SERVER_DLL_NAME);
		return false;
	}

	if (!Utils::getModule(m_gamePid, CSGO_ENGINE_DLL_NAME, &m_engineModule))
	{
		LOG_INFO(L"get module: {} faild!\n", CSGO_ENGINE_DLL_NAME);
		return false;
	}

	if (!updateGameSignature())
	{
		LOG_INFO("updateGameSignature faild!\n");
		return false;
	}

	if (!readGameGlobalData())
	{
		LOG_INFO("readGameGlobalData faild!\n");
		return false;
	}

	return true;
}

void CSGO::stop()
{
	m_stop = true;
}

void CSGO::run()
{
	MSG msg = { 0 };
	while (!m_stop)
	{
		// we use PeekMessage instead of GetMessage here
		// because we should not block the thread at anywhere
		// except the engine execution driver module
		//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		//{
		//	TranslateMessage(&msg);
		//	DispatchMessage(&msg);
		//	if (msg.message == WM_QUIT)
		//	{
		//		m_stop = true;
		//	}
		//}

		//adjustWindow();
		updateGame();
		m_renderManager->render();

		Sleep(1);
	}

	m_renderManager->shutdown();
}

void CSGO::updateGame()
{
	// get view projection matrix
	if (!Utils::readMemory(m_gameHandle, m_matrixAddress, m_viewProMatrix, sizeof(m_viewProMatrix)))
	{
		//LOG_INFO("matrix: %f, %f, %f, %f, \n"
		//	"%f, %f, %f, %f, \n"
		//	"%f, %f, %f, %f, \n"
		//	"%f, %f, %f, %f, \n",
		//	matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3],
		//	matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3],
		//	matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3],
		//	matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);
		return;
	}

	// get local player
	std::uintptr_t localPlayerAddress = 0;
	if (!Utils::readMemory(m_gameHandle, m_localPlayerAddress, &localPlayerAddress, sizeof(localPlayerAddress)) || localPlayerAddress == 0)
	{
		return;
	}

	std::vector<Player*> enemies;
	std::vector<Player*> allPlayers;
	for (size_t i = 0; i < m_allPlayers.size(); ++i)
	{
		Player& player = m_allPlayers[i];

		std::uintptr_t playerAddress;
		Utils::readMemory(m_gameHandle, m_teamAddress + i * PLAYERS_ARRAY_OFFSET, &playerAddress, sizeof(int));
		if (playerAddress == 0)
		{
			continue;
		}

		if (localPlayerAddress == playerAddress)
		{
			m_localPlayer = &player;
		}

		Utils::readMemory(m_gameHandle, playerAddress + PLAYER_TEAM_FLAG, &player.team, sizeof(player.team));
		Utils::readMemory(m_gameHandle, playerAddress + PLAYER_POS, &player.pos, sizeof(player.pos));
		Utils::readMemory(m_gameHandle, playerAddress + PLAYER_MIRRO, &player.mirror, sizeof(player.mirror));
		Utils::readMemory(m_gameHandle, playerAddress + PLAYER_COMMAND, &player.cmd, sizeof(player.cmd));
		Utils::readMemory(m_gameHandle, playerAddress + PLAYER_HP, &player.hp, sizeof(player.hp));
		Utils::readMemory(m_gameHandle, playerAddress + PLAYER_PITCH, &player.pitch, sizeof(player.pitch));
		Utils::readMemory(m_gameHandle, playerAddress + PLAYER_YAW, &player.yaw, sizeof(player.yaw));

		std::uintptr_t skeletonBase;
		if (Utils::readMemory(m_gameHandle, playerAddress + PLAYER_SKELETON_BASE, &skeletonBase, sizeof(skeletonBase)))
		{
			Utils::readMemory(m_gameHandle, skeletonBase + PLAYER_SKELETON_HEAD_X, &player.skeletonHead[0], sizeof(float));
			Utils::readMemory(m_gameHandle, skeletonBase + PLAYER_SKELETON_HEAD_Y, &player.skeletonHead[1], sizeof(float));
			Utils::readMemory(m_gameHandle, skeletonBase + PLAYER_SKELETON_HEAD_Z, &player.skeletonHead[2], sizeof(float));
		}

		allPlayers.emplace_back(&player);
	}

	if (m_localPlayer == nullptr)
	{
		return;
	}

	updateESP(allPlayers);
	updateAimBot(allPlayers);
}

bool CSGO::getGameProcess()
{
	HWND gameWnd = ::FindWindowW(NULL, CSGO_WINDOW_TITLE_NAME1.data());
	if (gameWnd == nullptr)
	{
		gameWnd = ::FindWindowW(NULL, CSGO_WINDOW_TITLE_NAME2.data());
		if (gameWnd == nullptr)
		{
			LOG_INFO("find game window faild!\n");
			return false;
		}
	}

	m_gamePid = ProcessManager::getPid(CSGO_PROCESS_NAME);
	if (m_gamePid == 0)
	{
		LOG_INFO("get process id faild!\n");
		return false;
	}

	m_gameHandle = ProcessManager::getProcessHandle(m_gamePid);
	if (m_gameHandle == nullptr)
	{
		LOG_INFO("get process handle faild!\n");
		return false;
	}

	m_gameWnd = gameWnd;
	return true;
}

void CSGO::adjustWindow()
{
	if (m_mainWnd == nullptr)
	{
		return;
	}

	// 保持本窗口在游戏窗口上
	RECT gameWindowRect = { 0 };
	::GetWindowRect(m_gameWnd, &gameWindowRect);

	int top = gameWindowRect.top;
	int left = gameWindowRect.left;
	int w = gameWindowRect.right - gameWindowRect.left;
	int h = gameWindowRect.bottom - gameWindowRect.top;

	m_gameWindowWidth = w;
	m_gameWindowHeight = h;

	DWORD dwStyle = ::GetWindowLong(m_gameWnd, GWL_STYLE);
	if (dwStyle & WS_BORDER)
	{
		top += 23;
		h -= 23;
	}

	MoveWindow(m_mainWnd, left, top, w, h, true);
}

void CSGO::gameDraw()
{
	drawESP();
}

void CSGO::drawESP()
{
	if (m_espData.data.empty() || !m_esp)
	{
		return;
	}

    m_renderManager->drawStrokeText(50, 50, IM_COL32(255, 0, 0, 255), "StrokeText");
	m_renderManager->drawNewText(80, 80, IM_COL32(255, 0, 0, 255), "NewText");
	m_renderManager->drawRect(200, 200, 100, 100, IM_COL32(255, 0, 0, 255));
	m_renderManager->drawLine(200, 200, 100, 100, IM_COL32(255, 0, 0, 255));

	//for (size_t i = 0; i < m_espData.data.size(); ++i)
	//{
	//	ESPData::RenderData& espData = m_espData.data[i];

	//	if (espData.color == ESPData::s_redRectangle)
	//	{
	//		//设置字体颜色
	//		SetTextColor(hdc, ESPData::s_redRectangle);
	//		FrameRect(hdc, &espData.rect, redb);
	//	}
	//	else if (espData.color == ESPData::s_blueRectangle)
	//	{
	//		//设置字体颜色
	//		SetTextColor(hdc, ESPData::s_blueRectangle);
	//		FrameRect(hdc, &espData.rect, blueb);
	//	}

	//	int fontx = (int)(espData.rect.left + (espData.rect.right - espData.rect.left) * 0.5);
	//	int fonty = espData.rect.top;
	//	if (fontx != 0 && fonty != 0)
	//	{
	//		TextOutA(hdc, fontx, fonty, espData.textHP.c_str(), espData.textHP.length());
	//	}
	//}

	m_espData.clear();
}

bool CSGO::updateGameSignature()
{
	{
		std::uintptr_t addr = Utils::findPatternInMemory(m_gameHandle, m_clientModule.address, m_clientModule.size, GameSignature::g_teamBaseSignature.signature);
		if (addr == 0)
		{
			LOG_INFO("can't find g_teamBaseSignature!\n");
			return false;
		}

		std::uintptr_t targetAddr;
		std::uintptr_t readAddr = GameSignature::g_teamBaseSignature.flag ? addr + GameSignature::g_teamBaseSignature.offset : addr - GameSignature::g_teamBaseSignature.offset;
		Utils::readMemory(m_gameHandle, readAddr, &targetAddr, sizeof(targetAddr));

		m_teamAddress = targetAddr + 0x10; // 找的这个特征码不太好，需要额外加上0x10
		LOG_INFO("found m_teamAddress:%x, offset:%x!\n", m_teamAddress, m_teamAddress - m_clientModule.address);
	}
	{
		m_matrixAddress = m_clientModule.address + ENGINE_CAMERA_MATRIX;
	}

	return true;
}

bool CSGO::readGameGlobalData()
{
	std::uintptr_t angleBase = 0;
	float viewhAngle[2]{ 0.f };
	if (!Utils::readMemory(m_gameHandle, m_engineModule.address + ENGINE_VISUAL_ANGLE_BASE, &angleBase, sizeof(std::uintptr_t)))
	{
		assert(false);
		return false;
	}

	if (!Utils::readMemory(m_gameHandle, angleBase + ENGINE_VISUAL_VIEW_ANGLE, viewhAngle, sizeof(viewhAngle)))
	{
		assert(false);
		return false;
	}

	m_viewAngleAddress = angleBase + ENGINE_VISUAL_VIEW_ANGLE;
	m_localPlayerAddress = m_clientModule.address + LOCAL_PLAYER;

	LOG_INFO("CSGOGameManager::init success!,client.dll base: %x!, server.dll base:%x, engine.dll base:%x, team address:%x, matrix address:%x, "
		"m_viewAddress:%x, pitch:%f, yaw:%f\n",
		m_clientModule.address, m_serverModule.address, m_engineModule.address, 
		m_teamAddress, m_matrixAddress, m_viewAngleAddress, viewhAngle[0], viewhAngle[1]);

	return true;
}

void CSGO::updateESP(const std::vector<Player*>& allPlayers)
{
	if (!m_esp)
	{
		return;
	}

	for (size_t i = 0; i < allPlayers.size(); ++i)
	{
		Player& player = *allPlayers[i];

		if (&player == m_localPlayer
			|| player.hp <= 0
			|| m_localPlayer->team == player.team
			)
		{
			continue;
		}

		int screenSkeletonHeadx = 0, screenSkeletonHeady = 0;
		Utils::worldToSceenDX(m_viewProMatrix, player.skeletonHead, m_gameWindowWidth, m_gameWindowHeight, screenSkeletonHeadx, screenSkeletonHeady);

		int screenx = 0, screeny = 0;
		Utils::worldToSceenDX(m_viewProMatrix, player.pos, m_gameWindowWidth, m_gameWindowHeight, screenx, screeny);

		int playerHeight = screeny - screenSkeletonHeady;
		int playerWidth = int(playerHeight / 2); // 假设人物的模型宽度是身高的一半
		int extra = playerHeight / 6;  // 目前位置大概是嘴唇位置，增加少许高度把矩阵上边画在超过头的位置
		ESPData::RenderData esp;
		esp.rect.left = screenx - playerWidth / 2;
		esp.rect.top = screenSkeletonHeady - extra; //(screenSkeletonHeady - extra) < 0 ? 0 : screenSkeletonHeady - extra;
		esp.rect.right = esp.rect.left + playerWidth;
		esp.rect.bottom = esp.rect.top + playerHeight + extra;
		esp.color = m_localPlayer->team == player.team ? ESPData::s_blueRectangle : ESPData::s_redRectangle;
		esp.textHP = std::to_string(player.hp);

		m_espData.data.push_back(esp);
	}
}

void CSGO::updateAimBot(const std::vector<Player*>& allPlayers)
{
	if (!m_aimbot)
	{
		return;
	}

	// 没有攻击或者没开镜的时候，不触发自瞄
	if ((m_localPlayer->cmd & 1) == 0 && (m_localPlayer->mirror >= 90 || m_localPlayer->mirror <= 0 || m_localPlayer->hp <= 0))
	{
		return;
	}

	static constexpr float r2d = 57.295779513082f;

	struct Angles { float pitch{}; float yaw{}; };
	std::map<float, Angles> sortEnemies;
	for (size_t i = 0; i < allPlayers.size(); ++i)
	{
		Player& player = *allPlayers[i];

		if (player.team == m_localPlayer->team || player.hp <= 0)
		{
			continue;
		}

		// 获取目标和我的向量
		float x = player.skeletonHead[0] - m_localPlayer->pos[0];
		float y = player.skeletonHead[1] - m_localPlayer->pos[1];
		float z = player.skeletonHead[2] - m_localPlayer->pos[2] - 70.f;// 63是个优化的值，目的是定位到人物的摄像机位置
		float length = (float)(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));


		Angles angle{ m_localPlayer->pitch, m_localPlayer->yaw };

		// 计算Yaw和Pitch角
		// 与目标保持在一个水平线，不需要计算yaw了，大于这个值才计算
		if (x > 0.01f || x < -0.01f)
		{
			// csgo的yaw是0-180度到-180度到0度为一个周期
			// 因此当向量0于第一和第四象限时，我们不做处理
			// 当处于第二象限(quadrant)时，得到的角度是负的，因此加上180度转换到第二象限
			// 同理第三象限亦是
			float yaw = atan(y / x) * r2d;
			if (x < 0.0f && y >= 0.0f)
			{
				yaw = yaw + 180.f;
			}
			else if (x < 0.0f && y < 0.0f)
			{
				yaw = yaw - 180.f;
			}
			angle.yaw = yaw;
		}

		// lenth太小，说明敌人就在面前，因此大于这个值才需要计算pitch
		if (length > 0.1f)
		{
			// csgo往上是0到-89度，因此要取反
			float pitch = asin(z / length) * r2d; // 180.0f / pi(3.1415926f)
			pitch = -pitch;
			angle.pitch = pitch;
		}

		sortEnemies.insert({ length ,angle });
	}

	if (sortEnemies.empty())
	{
		return;
	}

	for (const auto& pair : sortEnemies)
	{
		const Angles& angle = pair.second;

		float viewhAngle[2] = { angle.pitch, angle.yaw };
		if (viewhAngle[0] == m_localPlayer->pitch && viewhAngle[1] == m_localPlayer->yaw)
		{
			continue;
		}

		// 限制的自瞄角度是30度
		if (abs(viewhAngle[0] - m_localPlayer->pitch) > 30 || abs(viewhAngle[1] - m_localPlayer->yaw) > 30)
		{
			continue;
		}

		Utils::writeMemory(m_gameHandle, m_viewAngleAddress, &viewhAngle, sizeof(viewhAngle));
		return;
	}
}





