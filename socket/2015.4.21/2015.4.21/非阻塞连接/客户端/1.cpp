#include <iostream>
#define _WIN32_WINNT 0x0500
#include <Winsock2.h>
#include <windows.h>
#include <string>
#include <process.h>
#include <time.h>

#pragma comment(lib, "Ws2_32.lib")

#define _PORT 12345

char buf[1024 * 1024];

void main()
{
	HWND hwnd = GetConsoleWindow();

	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);
	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//设置套接字为非阻塞
	unsigned long nonblocking = 1;
	ioctlsocket(sServer, FIONBIO, &nonblocking);

	char server_ip[256];
	std::cout<<"请输入服务器的IP地址：";
	std::cin>>server_ip;
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip);
	if (SOCKET_ERROR == connect(sServer, (sockaddr*)&si, sizeof(si)))
	{
		int bt = time(0);
		while (1)
		{
			fd_set fs;
			FD_ZERO(&fs);
			FD_SET(sServer, &fs);
			timeval t = {0, 1};
			select(0, 0, &fs, 0, &t);
			if (fs.fd_count == 1)
				break;
			else
			{
				if (time(0) - bt > 5)
				{
					std::cout<<"无法连接服务器，";
					system("pause");
					closesocket(sServer);
					WSACleanup();
					return;
				}
			}
		}
	};

	system("cls");

	while (1)
	{
		if (GetForegroundWindow() == hwnd)
		{
			for (char i = 'A'; i <= 'Z'; ++i)
			{
				if (GetAsyncKeyState(i) & 0x8000)
					send(sServer, &i, 1, 0);
			}
		}

		char buf[256];
		int r = recv(sServer, buf, 256, 0);
		if (r > 0)
		{
			for (int i = 0; i < r; ++i)
				std::cout<<buf[i];
		}
		else if (r == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				;
			else
			{
				std::cout<<"真的出错了，";
				system("pause");
				closesocket(sServer);
				WSACleanup();
				return;
			}
		}
		else if (r == 0)
			break;

		Sleep(20);
	}

	closesocket(sServer);
	WSACleanup();

	system("pause");
}