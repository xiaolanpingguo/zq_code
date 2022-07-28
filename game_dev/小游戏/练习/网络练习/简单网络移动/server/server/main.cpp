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
	int err = ::WSAStartup(wVer, &wd);
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
	//监听套接字
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//设置套接字为非阻塞模式
	unsigned long nonblocking = 1;
	ioctlsocket(sListen, FIONBIO, &nonblocking);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = ADDR_ANY;

	if (-1 == bind(sListen, (sockaddr*)&si, sizeof(si)))
	{
		cout << "套接字与地址绑定失败！" << endl;
		system("pause");
		closesocket(sListen);
		WSACleanup();
		return;
	}

	if (-1 == listen(sListen, 8))
	{
		cout << "监听失败！" << endl;
		system("pause");
		closesocket(sListen);
		WSACleanup();
		return;
	}

	cout << "服务器已经启动！" << endl;

	SOCKET sClient;
	sockaddr_in ci;
	int ci_len = sizeof(ci);

	//服务器与客户端位置
	POS ser_pos;
	POS cli_pos;
	ser_pos.x = 0;
	ser_pos.y = 0;

	//初始化地图
	char map[MAP_S] = {};

	while (1)
	{
		sClient = accept(sListen, (sockaddr*)&ci, &ci_len);
		if (INVALID_SOCKET == sClient)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				;
			else
			{
				cout << "accept出错";
				system("pause");
				closesocket(sListen);
				WSACleanup();
				return;
			}
		}
		else
		{
			if (recv(sClient, (char*)&cli_pos, sizeof(POS), 0) > 0)
				break;
			else
			{
				cout << "未能初始化地图，即将退出游戏" << endl;
				closesocket(sListen);
				closesocket(sClient);
				WSACleanup();
				system("pause");
				return;
			}
		}
	}

	if (send(sClient, (char*)&ser_pos, sizeof(POS), 0) > 0)
		;
	else
	{
		cout << "初始化客户端数据错误，即将退出游戏" << endl;
		closesocket(sListen);
		closesocket(sClient);
		WSACleanup();
		system("pause");
		return;
	}

	system("cls");

	while (1)
	{
		system("cls");
		int r = recv(sClient, (char*)&cli_pos, sizeof(POS), 0);
		if (r == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				;
			else
			{
				cout << "客户端掉线，即将退出游戏" << endl;
				break;
			}
		}
		else if (r == 0)
		{
			cout << "客户端退出了游戏，即将退出游戏" << endl;
			break;
		}

		r = send(sClient, (char*)&ser_pos, sizeof(POS), 0);
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

		if ((GetAsyncKeyState('W') & 1) && ser_pos.y > 0)
			--ser_pos.y;
		if ((GetAsyncKeyState('S') & 1) && ser_pos.y < MAP_H - 1)
			++ser_pos.y;
		if ((GetAsyncKeyState('A') & 1) && ser_pos.x > 0)
			--ser_pos.x;
		if ((GetAsyncKeyState('D') & 1) && ser_pos.x < MAP_W - 1)
			++ser_pos.x;
	}
	closesocket(sListen);
	closesocket(sClient);
	WSACleanup();
	system("pause");
}