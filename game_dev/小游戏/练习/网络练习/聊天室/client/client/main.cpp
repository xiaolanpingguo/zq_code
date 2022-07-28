#include <iostream>
#include <WinSock2.h>
#include <vector>
#include <process.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888

SOCKET sServer;

unsigned int __stdcall recv_server(void*)
{
	while (1)
	{
		char buf[256];
		recv(sServer, buf, 256, 0);
		cout << buf << endl;
	}
}

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

	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	char server_ip[256];
	cout << "请输入服务器的IP地址：";
	cin >> server_ip;
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip); 

	if (SOCKET_ERROR == connect(sServer, (sockaddr*)&si, sizeof(si)))
	{
		std::cout << "无法连接服务器，";
		system("pause");
		closesocket(sServer);
		WSACleanup();
		return;
	};

	_beginthreadex(0, 0, recv_server, 0, 0, 0);

	while (1)
	{
		char buf[256];
		cout << "请输入要发送的字符串：";
		cin >> buf;

		send(sServer, buf, strlen(buf) + 1, 0);

		if (strcmp(buf, "quit") == 0)
			break;
	}

	closesocket(sServer);
	WSACleanup();

	system("pause");
}