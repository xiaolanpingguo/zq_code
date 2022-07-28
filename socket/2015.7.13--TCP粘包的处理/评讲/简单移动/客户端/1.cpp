#include <iostream>
#include <Winsock2.h>
#include "NetWork.h"
#pragma comment(lib, "Ws2_32.lib")

char buf[1024 * 1024 * 32];

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	u_long no_blocking = TRUE;
	ioctlsocket(s, FIONBIO, &no_blocking);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	
	//因为connect一定返回失败所以此处不检查
	connect(s, (sockaddr*)&si, sizeof(si));

	//在一定时间之内检查套接字可写性如果可写
	//就连接成功，下面为了方便处理就一直等待
	//直到变为可写
	fd_set fs;
	FD_ZERO(&fs);
	FD_SET(s, &fs);
	select(0, 0, &fs, 0, 0);

	std::cout<<"连接服务器成功！"<<std::endl;

	CNetWork nw(s);

	//业务循环
	while (1)
	{
		//运作
		if (!nw.Run())
			break;

		system("cls");
		std::cout<<"请输入要发送的MB：";
		int send_mb;
		std::cin>>send_mb;
		send_mb *= 1024 * 1024;

		nw.SendData(buf, send_mb);

		Sleep(20);
	}

	closesocket(s);
	WSACleanup();

	system("pause");
}