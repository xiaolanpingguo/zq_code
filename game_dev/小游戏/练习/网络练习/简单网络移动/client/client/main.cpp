#include <iostream>
#include <WinSock2.h>
#include <vector>

#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888

#define MAP_W 8
#define MAP_H 8
#define MAP_S (MAP_W * MAP_H)

struct POS
{
	short x : 8, y : 8;
};

void main()
{
	WORD wVer = MAKEWORD(SOCK_VERH, SOCK_VERL);
	WSADATA wd;
	int err = WSAStartup(wVer, &wd);
	if (0 != err)
	{
		cout << "无法初始化Socket2系统环境!" << endl;
		system("pause");
		return;
	}
	if (LOBYTE(wd.wVersion) != SOCK_VERL ||
		HIBYTE(wd.wVersion) != SOCK_VERH)
	{
		cout << "无法初始化" << SOCK_VERH << "." << SOCK_VERL << "版本的Socket环境!" << endl;
		system("pause");
		WSACleanup();
		return;
	}

	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); 

	if (SOCKET_ERROR == connect(sServer, (sockaddr*)&si, sizeof(si)))
	{
		std::cout << "无法连接服务器，";
		system("pause");
		closesocket(sServer);
		WSACleanup();
		return;
	};

	POS ser_pos;
	POS cli_pos;
	cli_pos.x = MAP_W - 1;
	cli_pos.y = MAP_H - 1;
	char map[MAP_S] = {};

	if (send(sServer, (char*)&cli_pos, sizeof(POS), 0) == 0)
	{
		cout << "未知原因，即将退出游戏" << endl;
		closesocket(sServer);
		closesocket(sServer);
		WSACleanup();
		system("pause");
		return;
	}
	
	if (recv(sServer, (char*)&ser_pos, sizeof(POS), 0) == 0)
	{
		cout << "未知原因，即将退出游戏" << endl;
		closesocket(sServer);
		closesocket(sServer);
		WSACleanup();
		system("pause");
		return;
	}

	while (1)
	{
		system("cls");
		int r = recv(sServer, (char*)&ser_pos, sizeof(POS), 0);
		if (r == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				;
			else
			{
				cout << "服务器蹦了，即将退出游戏" << endl;
				break;
			}
		}
		else if (r == 0)
		{
			cout << "服务器退出了游戏，即将退出游戏" << endl;
			break;
		}

		r = send(sServer, (char*)&cli_pos, sizeof(POS), 0);
		if (r == 0)
			cout << "发送数据失败，请重试" << endl;

		for (int i = 0; i < MAP_S; ++i)
		{
			//□△☆
			if (i == ser_pos.x + ser_pos.y * MAP_W)
				cout << "☆";
			else if (i == cli_pos.x + cli_pos.y * MAP_W)
				cout << "△";
			else if (map[i] == 0)
				cout << "□";
			if (i % MAP_W == MAP_W - 1)
				cout << endl;
		}

		if ((GetAsyncKeyState(VK_UP) & 1) && cli_pos.y > 0)
			--cli_pos.y;
		if ((GetAsyncKeyState(VK_DOWN) & 1) && cli_pos.y < MAP_H - 1)
			++cli_pos.y;
		if ((GetAsyncKeyState(VK_LEFT) & 1) && cli_pos.x > 0)
			--cli_pos.x;
		if ((GetAsyncKeyState(VK_RIGHT) & 1) && cli_pos.x < MAP_W - 1)
			++cli_pos	.x;
	}

	closesocket(sServer);
	WSACleanup();

	system("pause");
}