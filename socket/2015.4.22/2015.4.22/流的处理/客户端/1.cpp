#include <iostream>
#define _WIN32_WINNT 0x0500
#include <Winsock2.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "MySendRecv.h"

#pragma comment(lib, "Ws2_32.lib")

#define _PORT 12345

char buf[10 * 1024 * 1024] = {};

void main()
{
	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);
	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//设置套接字为非阻塞
	unsigned long nonblocking = 1;
	ioctlsocket(sServer, FIONBIO, &nonblocking);

	//char server_ip[256];
	//std::cout<<"请输入服务器的IP地址：";
	//std::cin>>server_ip;
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
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

	//_getch的作用是从系统的输入缓冲中得到一个输入的字符，如果
	//输入缓冲有输入的字符就返回，没有就等待，而_kbhit可以得到
	//当前输入缓冲有没有输入的字符
	//while (_kbhit())
	//	_getch();

	CMySendRecv msr(sServer);

	while (1)
	{
		msr.Run();

		_NET_EVENT ne;
		while (msr.GetNetEvent(&ne))
		{
			switch (ne.type)
			{
			case 0: msr.Close(); break;
			case 1:
				{
					std::cout<<"收到了"<<ne.size<<"个字节的数据"<<std::endl;
					free(ne.data);
					break;
				}
			}
		}

		for (int i = VK_NUMPAD1; i <= VK_NUMPAD9; ++i)
		{
			if (GetAsyncKeyState(i) & 1)
				msr.SendData(buf, (i - VK_NUMPAD0) * 1024 * 1024);
		}

		Sleep(20);
	}

	closesocket(sServer);
	WSACleanup();

	system("pause");
}