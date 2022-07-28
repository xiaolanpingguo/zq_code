#include <iostream>
#include <Winsock2.h>
#include <string>
#include <process.h>

#pragma comment(lib, "Ws2_32.lib")

#define _PORT 12345

char buf[1024 * 1024];

void main()
{
	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);
	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	char server_ip[256];
	std::cout<<"请输入服务器的IP地址：";
	std::cin>>server_ip;
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip);
	if (SOCKET_ERROR == connect(sServer, (sockaddr*)&si, sizeof(si)))
	{
		std::cout<<"无法连接服务器，";
		system("pause");
		closesocket(sServer);
		WSACleanup();
		return;
	};

	while (1)
	{
		int len;
		std::cout<<"请输入要发送的数据长度";
		std::cin>>len;

		send(sServer, buf, len, 0);
	}

	closesocket(sServer);
	WSACleanup();

	system("pause");
}