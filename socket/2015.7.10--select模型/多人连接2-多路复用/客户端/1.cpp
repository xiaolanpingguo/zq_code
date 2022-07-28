#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	WSADATA wd;
	WSAStartup(0x0101, &wd);
	SOCKET s_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	char server_ip[256];
	std::cout<<"请输入服务器ip地址：";
	std::cin>>server_ip;
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip);
	if (SOCKET_ERROR == connect(s_server, (sockaddr*)&si, sizeof(si)))
	{
		std::cout<<"无法连接服务器，";
		system("pause");
		closesocket(s_server);
		WSACleanup();
		return;
	}
	std::cout<<"成功连接服务器！"<<std::endl;

	//业务循环
	while (1)
	{
		std::cout<<"请输入要说的话:";
		char buf[256];
		std::cin>>buf;
		send(s_server, buf, strlen(buf) + 1, 0);
	}

	closesocket(s_server);
	WSACleanup();

	system("pause");
}