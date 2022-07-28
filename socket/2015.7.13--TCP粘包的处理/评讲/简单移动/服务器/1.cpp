#include <iostream>
#include <Winsock2.h>
#include "NetWork.h"
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//设置非阻塞（服务器中只要监听套接字设置为非阻塞
	//了，那么这个监听套接字得到的所有数据套接字都是
	//非阻塞了）
	u_long no_blocking = TRUE;
	ioctlsocket(s_listen, FIONBIO, &no_blocking);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(s_listen, (sockaddr*)&si, sizeof(si));
	listen(s_listen, 8);

	SOCKET c;

	//等待连接
	while (1)
	{
		sockaddr_in ci;
		int ci_len = sizeof(ci);
		c = accept(s_listen, (sockaddr*)&ci, &ci_len);
		if (c == INVALID_SOCKET)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				std::cout<<"真的出错，";
				system("pause");
				closesocket(s_listen);
				WSACleanup();
				return;
			}
			else
			{
				std::cout<<"当前无人连接！"<<std::endl;
				Sleep(1);
			}
		}
		else
			break;
	}

	std::cout<<"客户端连接成功！"<<std::endl;

	CNetWork nw(c);

	//业务循环
	while (1)
	{
		//运作
		if (!nw.Run())
			break;

		_RECV_DATA rd;
		while (nw.GetRecvDate(&rd))
		{
			std::cout<<"收到"<<rd.len<<"个字节"<<std::endl;
			nw.ReleaseRecvData(&rd);
		}

		Sleep(20);
	}

	closesocket(s_listen);
	WSACleanup();

	system("pause");
}