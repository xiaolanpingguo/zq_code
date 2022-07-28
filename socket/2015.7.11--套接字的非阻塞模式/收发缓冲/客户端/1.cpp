#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

char buf[1024 * 1024 * 32];

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (0 != connect(s, (sockaddr*)&si, sizeof(si)))
	{
		std::cout<<"无法连接服务器，";
		system("pause");
		return;
	}

	std::cout<<"连接服务器成功！"<<std::endl;

	//业务循环
	while (1)
	{
		std::cout<<"请输入要发送的KB：";
		int num;
		std::cin>>num;
		send(s, buf, num * 1024, 0);
	}

	closesocket(s);
	WSACleanup();

	system("pause");
}