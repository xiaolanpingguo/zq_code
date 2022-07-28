#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(sListen, (sockaddr*)&si, sizeof(si));
	listen(sListen, 8);
	sockaddr_in ci;
	int ci_len = sizeof(ci);
	SOCKET c = accept(sListen, (sockaddr*)&ci, &ci_len);

	while (1)
	{
		char buf[256];
		int r = recv(c, buf, 256, 0);
		std::cout<<"收到了"<<r<<"个字节"<<std::endl;
	}

	closesocket(c);
	closesocket(sListen);
	WSACleanup();

	system("pause");
}