#include <iostream>
#define _WIN32_WINNT 0x0500
#include <Winsock2.h>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")
#include "MySendRecv.h"

void main()
{
	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	unsigned long nonblocking = 1;
	ioctlsocket(sListen, FIONBIO, &nonblocking);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(sListen, (sockaddr*)&si, sizeof(si));
	listen(sListen, 8);
	sockaddr_in ci;
	int ci_len = sizeof(ci);

	SOCKET sClient;
	while (1)
	{
		sClient = accept(sListen, (sockaddr*)&ci, &ci_len);
		if (INVALID_SOCKET == sClient)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				std::cout<<"当前无人连接"<<std::endl;
			else
			{
				std::cout<<"真的出错了，";
				system("pause");
				closesocket(sListen);
				WSACleanup();
				return;
			}
		}
		else
			break;
	}

	CMySendRecv msr(sClient);

	system("cls");

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

		Sleep(20);
	}

	closesocket(sClient);
	closesocket(sListen);
	WSACleanup();

	system("pause");
}