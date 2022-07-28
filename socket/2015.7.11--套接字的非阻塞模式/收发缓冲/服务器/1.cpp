#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(s_listen, (sockaddr*)&si, sizeof(si));
	listen(s_listen, 8);

	//等待连接
	sockaddr_in ci;
	int ci_len = sizeof(ci);
	SOCKET c = accept(s_listen, (sockaddr*)&ci, &ci_len);

	std::cout<<"客户端连接成功！"<<std::endl;

	//业务循环
	int all_bytes = 0;
	while (1)
	{
		char buf[256];
		int r = recv(c, buf, 256, 0);
		all_bytes += r;
		std::cout<<"当前总共收到"<<all_bytes<<"字节"<<std::endl;
	}

	closesocket(s_listen);
	WSACleanup();

	system("pause");
}