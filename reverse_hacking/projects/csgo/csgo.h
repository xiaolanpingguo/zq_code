#include <iostream>
#include <Windows.h>
#include <array>
#include <map>
#include "r3/utils.h"



class RenderManager;

struct Player
{
	float pos[3]{};				// 位置
	float skeletonHead[3]{};	// 头骨位置
	int team = 0;				// 阵营
	int hp = 0;					// 血量
	int mirror = 0;				// 是否开镜
	int cmd = 0;				// 动作类型，32位，每一位代表一个动作，第一位是攻击
	float pitch = -1.f;			// 俯仰角
	float yaw = -1.f;			// 偏航角
};

struct ESPData
{
	static constexpr std::uint32_t s_redRectangle = RGB(255, 0, 0);
	static constexpr std::uint32_t s_blueRectangle = RGB(0, 0, 255);
	struct RenderData
	{
		RECT rect;
		std::uint32_t color;
		std::string textHP;
	};
	std::vector<RenderData> data;

	void clear()
	{
		data.clear();
	}
};


class CSGO
{
public:
	CSGO();
	~CSGO();

    bool init();
    void run();
    void stop();
	bool isRunning();

	bool& getAimboot() { return m_aimbot; }
	bool& getEsp() { return m_esp; }

private:

	bool initGameModule();
	bool getGameProcess();
	void adjustWindow();

	// render
	void gameDraw();
	void drawESP();

	// game
	bool updateGameSignature();
	bool readGameGlobalData();
	void updateGame();
	void updateESP(const std::vector<Player*>& allPlayers);
	void updateAimBot(const std::vector<Player*>& allPlayers);

private:

	static std::atomic<bool> m_stop;
	HWND m_mainWnd;
	HINSTANCE m_appInstance;
	RenderManager* m_renderManager;

	int m_gameWindowWidth;
	int m_gameWindowHeight;
	HWND m_gameWnd;
	DWORD m_gamePid;
	HANDLE m_gameHandle;

	// game module
	ModuleData m_clientModule;
	ModuleData m_serverModule;
	ModuleData m_engineModule;

	// gloable address
	std::uintptr_t m_teamAddress;
	std::uintptr_t m_matrixAddress;
	std::uintptr_t m_viewAngleAddress;
	std::uintptr_t m_localPlayerAddress;

	// matrix
	float m_viewProMatrix[16]{};

	// player
	Player* m_localPlayer;
	std::array<Player, 32> m_allPlayers;

	// esp
	ESPData m_espData;
	bool m_esp;

	// aimbot
	bool m_aimbot;
};


