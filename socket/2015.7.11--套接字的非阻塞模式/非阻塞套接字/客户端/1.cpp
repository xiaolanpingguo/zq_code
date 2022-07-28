#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
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

	POINT p1 = {0, 0}, p2 = {9, 9};

	//业务循环
	while (1)
	{
		system("cls");
		for (int i = 0; i < 100; ++i)
		{
			if (i == p1.x + p1.y * 10)
				std::cout<<"●";
			else if (i == p2.x + p2.y * 10)
				std::cout<<"◆";
			else
				std::cout<<"□";
			if (i % 10 == 9)
				std::cout<<std::endl;
		}

		int r = recv(s, (char*)&p1, sizeof(p1), 0);

		int x = p2.x;
		int y = p2.y;
		if ((::GetAsyncKeyState(VK_UP) & 1) && p2.y > 0)
			p2.y -= 1;
		if ((::GetAsyncKeyState(VK_DOWN) & 1) && p2.y < 9)
			p2.y += 1;
		if ((::GetAsyncKeyState(VK_LEFT) & 1) && p2.x > 0)
			p2.x -= 1;
		if ((::GetAsyncKeyState(VK_RIGHT) & 1) && p2.x < 9)
			p2.x += 1;
		if (p2.x != x || p2.y != y)
			send(s, (const char*)&p2, sizeof(p2), 0);

		Sleep(20);
	}

	closesocket(s);
	WSACleanup();

	system("pause");
}